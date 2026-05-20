// TradeHelper.mqh
#ifndef __TRADE_HELPER_MQH__
#define __TRADE_HELPER_MQH__

#include <Trade\Trade.mqh>
#include "Utils.mqh"
#include "InputsHelper.mqh"

class CTradeHelper {
public:
    // Function to place an order
    static bool PlaceOrder(const string symbol, const ENUM_ORDER_TYPE orderType, double volume, double price, double sl, double tp, string cmnt = "[?]", int slippage = 10) {
        MqlTradeRequest request = {};
        MqlTradeResult result = {};
        double takeProfit = tp;
        datetime expiry = GetEndOfDayExpiration();

        MqlTick tick;
        double bid, ask, last;
        if(SymbolInfoTick(_Symbol, tick)) {
            bid = tick.bid;
            ask = tick.ask;
            last = tick.last;
        }

        // Indicator: SizeInPips -> Buffers: 0-CandleSize, 1-CandleSize2, 2-SMA_HL, 3-SMA_OC, 4-Optimum, 5-CustomSL, 6-CustomSLATR
        
        int shift = 0; // current bar
        double vals[7];
        for(int i=0; i<7; i++) {
            double buf[];
            if(CopyBuffer(SizeInPipsHandle, i, shift, 1, buf) == 1)
                vals[i] = MathAbs(buf[0]);
            else
                vals[i] = 0.0;
        }
        /*// Print values to chart using labels
        string texts[] = {
            "H-L Size: " + DoubleToString(vals[0], 2),
            "O-C Size: " + DoubleToString(vals[1], 2),
            "H-L SMA: " + DoubleToString(vals[2], 2),
            "O-C SMA: " + DoubleToString(vals[3], 2),
            "Optimum: " + (int)vals[4],
            "SL: " + DoubleToString(vals[5], 2),
            "SL ATR: " + DoubleToString(vals[6], 2)
        }; */

        bool tradePlaced = false;
        price = NormalizeDouble(ask, _Digits);
        for(int i = OneOrderAtATime; i < 2 ; i++) {
            LogMessage("Iteration: " + i);    // debugging
            takeProfit = tp;

            if(i == 0 && orderType == ORDER_TYPE_BUY) {
                takeProfit = price + GetPointsValue(vals[6]);
            } else if(i == 0 && orderType == ORDER_TYPE_SELL) {
                takeProfit = price - GetPointsValue(vals[6]);
            }
            
            if(DynamicTP == true && i != 0) {
                takeProfit = SetDynamicTp(orderType, last, takeProfit);
                LogMessage("> PlaceOrder() > Dynamic TP set to: " + DoubleToString(takeProfit, _Digits));
            }

            request.action = TRADE_ACTION_DEAL;
            request.symbol = symbol;
            request.volume = volume;
            request.type = orderType;
            // request.price = bid;
            request.sl = sl;
            request.tp = takeProfit;
            request.deviation = slippage;
            request.type_filling = ORDER_FILLING_IOC;
            //request.type_time = ORDER_TIME_DAY; // Set order type time to current day
            //request.expiration = expiry;
            request.comment = cmnt+","+i;
            request.magic = 0; // Set your magic number if needed

            // Print the request object before sending the order
            //PrintTradeRequest(request);
            if(CheckActiveTrades(symbol) < MaxOpenTrades) {
                if (OrderSend(request, result)) {
                    //PrintTradeResult(result);
                    PrintFormat("retcode=%u  deal=%I64u  order=%I64u",result.retcode,result.deal,result.order);
                    tradePlaced = true;
                } else {
                    //PrintTradeResult(result);            
                    Print("Error placing order: ", GetLastError());
                    PrintFormat("retcode=%u  deal=%I64u  order=%I64u",result.retcode,result.deal,result.order);
                    tradePlaced = false;
                }
            }
        }
        return tradePlaced;
    }

    // Function to check active trades
    static int CheckActiveTrades(const string symbol) {
        int total = 0;
        for (int i = 0; i < PositionsTotal(); i++) {
            if (PositionGetSymbol(i) == symbol) {
                total++;
            }
        }
        return total;
    }

    // Function to check active trades
    static int CheckActiveTrades(const string symbol, const ENUM_POSITION_TYPE positionType) {
        int total = 0;
        for (int i = 0; i < PositionsTotal(); i++) {
            if (PositionGetSymbol(i) == symbol) {
                ulong ticket = PositionGetTicket(i);
                if(PositionSelectByTicket(ticket)) {
                    if(PositionGetInteger(POSITION_TYPE) == positionType) {
                        total++;
                    }
                }
            }
        }
        return total;
    }

    // Function to update stop loss
    static bool UpdateStopLoss(const string symbol, ENUM_TIMEFRAMES timeframe = PERIOD_CURRENT) {
        bool updated = false;
        datetime now = TimeCurrent();

        for (int i = 0; i < PositionsTotal(); i++) {
            //Print("Checking position ", i);             // debugging
            if (PositionGetSymbol(i) == symbol) {
                ulong ticket = PositionGetTicket(i);
                if (PositionSelectByTicket(ticket)) {
                    datetime openTime = (datetime)PositionGetInteger(POSITION_TIME);
                    double sl = PositionGetDouble(POSITION_SL);
                    double theTP = PositionGetDouble(POSITION_TP);
                    double priceOpen = PositionGetDouble(POSITION_PRICE_OPEN);
                    long type = PositionGetInteger(POSITION_TYPE);
                    string comment = PositionGetString(POSITION_COMMENT);

                    // Get the candle time after the trade was opened
                    MqlRates rates[2];
                    if (CopyRates(symbol, timeframe, 0, 2, rates) == 2) {
                        datetime lastCandleOpen = rates[0].time; // previous closed candle
                        datetime currCandleOpen = rates[1].time; // currently forming candle

                        // Check if a new candle has formed after the trade was opened and SL hasn't been updated yet
                        // We'll use a global variable to mark that SL has been updated for this ticket
                        string gvName = "SLUpdated_" + IntegerToString((int)ticket);
                        
                        if (openTime < lastCandleOpen && GlobalVariableGet(gvName) == 0) {
                            double newSL = sl;
                            
                            if (type == POSITION_TYPE_BUY) {
                                // Move SL up to halfway between open price and current SL
                                newSL = priceOpen + (sl - priceOpen) / 2.0;
                                if (newSL < sl) newSL = sl; // Don't worsen SL
                            } else if (type == POSITION_TYPE_SELL) {
                                // Move SL down to halfway between open price and current SL
                                newSL = priceOpen - (priceOpen - sl) / 2.0;
                                if (newSL > sl) newSL = sl; // Don't worsen SL
                            }
                            // Check if dynamic TP is enabled and set it
                            if(DynamicTP == true) {
                                theTP = SetDynamicTp(type, priceOpen, theTP);
                                LogMessage("> UpdateStopLoss() > Dynamic TP set to: " + DoubleToString(theTP, _Digits));
                            }
                            // Only update if the new SL is closer to break-even
                            if ((type == POSITION_TYPE_BUY && newSL > sl) ||
                                (type == POSITION_TYPE_SELL && newSL < sl)) {
                                MqlTradeRequest req = {};
                                MqlTradeResult res = {};
                                req.action = TRADE_ACTION_SLTP;
                                req.symbol = symbol;
                                req.position = ticket;
                                req.sl = newSL;
                                req.tp = theTP;
                                req.magic = PositionGetInteger(POSITION_MAGIC);
                                req.deviation = 10;
                                req.type_filling = ORDER_FILLING_IOC;

                                if (OrderSend(req, res)) {
                                    LogMessage("SL updated for ticket " + ticket + " to " + DoubleToString(newSL, _Digits));
                                    GlobalVariableSet(gvName, 1); // Mark as updated
                                    updated = true;
                                } else {
                                    LogMessage("Failed to update SL for ticket " + ticket + ". Error: " + GetLastError() + " | priceOpen: " + priceOpen + " | newSL: " + newSL + " | currentAsk: " + SymbolInfoDouble(_Symbol, SYMBOL_ASK) + " | comment: " + comment);
                                }
                            }
                        }
                    }
                }
            }
        }
        return updated;
    }

    // Function to trail stop loss
    static bool TrailStopLoss(const string symbol, ENUM_TIMEFRAMES timeframe = PERIOD_CURRENT, double m1Close = 0.0) {
        bool trailed = false;
        datetime now = TimeCurrent();
        
        // Get the OHLC data for the last two completed candles
        MqlRates rates[4];
        if (CopyRates(_Symbol, Timeframe, 0, 4, rates) < 4)
        {
            Print("Error retrieving candle data.");
            return 0;
        }
        // Get last closed candle time
        // datetime currBarTime = rates[3].time;   // Last closed candle

        // Candle references
        MqlRates currentCandle = rates[3];      // Currently forming candle
        MqlRates lastCandle = rates[2];         // Last completed candle
        MqlRates secondLastCandle = rates[1];   // Second-to-last completed candle
        MqlRates thirdLastCandle = rates[0];    // Third-to-last completed candle
        // Calculate the body and wicks of the second-to-last candle
        double secondLastBody = MathAbs(secondLastCandle.close - secondLastCandle.open);
        double secondLastUpperWick = secondLastCandle.high - MathMax(secondLastCandle.close, secondLastCandle.open);
        double secondLastLowerWick = MathMin(secondLastCandle.close, secondLastCandle.open) - secondLastCandle.low;

        // Indicator: SizeInPips -> Buffers: 0-CandleSize, 1-CandleSize2, 2-SMA_HL, 3-SMA_OC, 4-Optimum, 5-CustomSL, 6-CustomSLATR
        
        int shift = 0; // current bar
        double vals[7];
        for(int i=0; i<7; i++) {
            double buf[];
            if(CopyBuffer(SizeInPipsHandle, i, shift, 1, buf) == 1)
                vals[i] = MathAbs(buf[0]);
            else
                vals[i] = 0.0;
        }

        for (int i = 0; i < PositionsTotal(); i++) {
            //Print("Checking position ", i);             // debugging
            if (PositionGetSymbol(i) == symbol) {
                ulong ticket = PositionGetTicket(i);
                if (PositionSelectByTicket(ticket)) {
                    datetime openTime = (datetime)PositionGetInteger(POSITION_TIME);
                    double sl = PositionGetDouble(POSITION_SL);
                    double priceOpen = PositionGetDouble(POSITION_PRICE_OPEN);
                    long type = PositionGetInteger(POSITION_TYPE);

                    // Get the candle time after the trade was opened
                    MqlRates rates[2];
                    if (CopyRates(symbol, timeframe, 0, 2, rates) == 2) {
                        datetime lastCandleOpen = rates[0].time; // previous closed candle
                        datetime currCandleOpen = rates[1].time; // currently forming candle
                        
                        // Check if a new candle has formed after the trade was opened and SL hasn't been trailed yet
                        // We'll use a global variable to mark that SL has been trailed for this ticket
                        //string gvName = "SLTrailed_" + IntegerToString((int)ticket);
                        
                        if (openTime < lastCandleOpen) {    //&& GlobalVariableGet(gvName) == 0
                            double newSL = sl;
                            
                            if (type == POSITION_TYPE_BUY) {
                                // Move SL up to halfway between open price and current SL
                                newSL =  m1Close - GetPointsValue(vals[2]);                                                        //= priceOpen + (sl - priceOpen) / 2.0;
                                if (newSL < sl) newSL = sl; // Don't worsen SL
                            } else if (type == POSITION_TYPE_SELL) {
                                // Move SL down to halfway between open price and current SL
                                newSL = m1Close + GetPointsValue(vals[2]);                                                         //= priceOpen - (priceOpen - sl) / 2.0;
                                if (newSL > sl) newSL = sl; // Don't worsen SL
                            }
                            
                            // Only update if the new SL is closer to break-even
                            if ((type == POSITION_TYPE_BUY && newSL > sl) ||
                                (type == POSITION_TYPE_SELL && newSL < sl)) {
                                MqlTradeRequest req = {};
                                MqlTradeResult res = {};
                                req.action = TRADE_ACTION_SLTP;
                                req.symbol = symbol;
                                req.position = ticket;
                                req.sl = newSL;
                                req.tp = PositionGetDouble(POSITION_TP);
                                req.magic = PositionGetInteger(POSITION_MAGIC);
                                req.deviation = 10;
                                req.type_filling = ORDER_FILLING_IOC;

                                if (OrderSend(req, res)) {
                                    // Print values to chart using labels
                                    string text = "H-L: " + DoubleToString(vals[0], 2) +
                                                  ", O-C: " + DoubleToString(vals[1], 2) +
                                                  ", H-L SMA: " + DoubleToString(vals[2], 2) +
                                                  ", O-C SMA: " + DoubleToString(vals[3], 2) +
                                                  ", SL: " + DoubleToString(vals[5], 2) +
                                                  ", SL ATR: " + DoubleToString(vals[6], 2);
                                    LogMessage(text);
                                    LogMessage("SL trailed for ticket " + ticket + " to " + DoubleToString(newSL, _Digits));
                                    // GlobalVariableSet(gvName, 1); // Mark as trailed
                                    trailed = true;
                                } else {
                                    LogMessage("Failed to trail SL for ticket " + ticket + ". Error: " + GetLastError());
                                }
                            }
                        }
                    }
                }
            }
        }
        return trailed;
    }
};

//--- Helper function to print the contents of the MqlTradeRequest object:
void PrintTradeRequest(const MqlTradeRequest &request)
{
    MqlTick tick;
    double bid, ask, last;
    if(SymbolInfoTick(_Symbol, tick)) {
        bid = tick.bid;
        ask = tick.ask;
        last = tick.last;
    }
    Print("Current Bid: ", bid, " | Current Ask: ", ask, " | Last: ", last);
    Print("Trade Request:");
    Print("  Action: ", request.action);
    Print("  Symbol: ", request.symbol);
    Print("  Volume: ", request.volume);
    Print("  Price: ", request.price);
    Print("  Stop Loss: ", request.sl);
    Print("  Take Profit: ", request.tp);
    Print("  Deviation: ", request.deviation);
    Print("  Type: ", request.type);
    Print("  Magic: ", request.magic);
    Print("  Comment: ", request.comment);
    Print("  Position: ", request.position);
    Print("  Type Fill: ", request.type_filling);
    Print("  Type Time: ", request.type_time);
    Print("  Expiration: ", request.expiration);
}

//--- Helper function to print the contents of the MqlTradeResult object:
void PrintTradeResult(const MqlTradeResult &result)
{
    MqlTick tick;
    double bid, ask, last;
    if(SymbolInfoTick(_Symbol, tick)) {
        bid = tick.bid;
        ask = tick.ask;
        last = tick.last;
    }
    Print("Current Bid: ", bid, " | Current Ask: ", ask, " | Last: ", last);
    Print("Trade Result:");
    Print("  Deal: ", result.deal);
    Print("  Order: ", result.order);
    Print("  Volume: ", result.volume);
    Print("  Price: ", result.price);
    Print("  Bid: ", result.bid);
    Print("  Ask: ", result.ask);
    Print("  Comment: ", result.comment);
    Print("  Request ID: ", result.request_id);
    Print("  Retcode: ", result.retcode);
}

//--- Helper function to set dynamic TP (Take Profit)
double SetDynamicTp(long type, double priceOpen, double theTP) {
    double tp = 0.0;

    // Indicator: SizeInPips -> Buffers: 0-CandleSize, 1-CandleSize2, 2-SMA_HL, 3-SMA_OC, 4-Optimum, 5-CustomSL, 6-CustomSLATR
    double vals[7];
    int shift = 0; // current bar

    for(int i=0; i<7; i++) {
        double buf[];
        if(CopyBuffer(SizeInPipsHandle, i, shift, 1, buf) == 1)
            vals[i] = MathAbs(buf[0]);
        else
            vals[i] = 0.0;
    }
    if (type == POSITION_TYPE_BUY) {
        if(DynTpType == SMA_HL) {
            tp = priceOpen + GetPointsValue(vals[2]);
        } else if(DynTpType == SMA_OC) {
            tp = priceOpen + GetPointsValue(vals[3]);
        } else if(DynTpType == CustomSL) {
            tp = priceOpen + GetPointsValue(vals[5]);
        } else if(DynTpType == CustomSLATR) {
            tp = priceOpen + GetPointsValue(vals[6]);
        } else {
            tp = theTP;
        }
    } else if (type == POSITION_TYPE_SELL) {
        if(DynTpType == SMA_HL) {
            tp = priceOpen - GetPointsValue(vals[2]);
        } else if(DynTpType == SMA_OC) {
            tp = priceOpen - GetPointsValue(vals[3]);
        } else if(DynTpType == CustomSL) {
            tp = priceOpen - GetPointsValue(vals[5]);
        } else if(DynTpType == CustomSLATR) {
            tp = priceOpen - GetPointsValue(vals[6]);
        } else {
            tp = theTP;
        }
    }
    return tp;
}

#endif // __TRADE_HELPER_MQH__
