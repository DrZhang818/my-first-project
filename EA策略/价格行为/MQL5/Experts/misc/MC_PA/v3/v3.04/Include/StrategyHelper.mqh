// StrategyHelper.mqh
#ifndef __STRATEGY_HELPER_MQH__
#define __STRATEGY_HELPER_MQH__

#include <Trade\Trade.mqh>
#include "TradeHelper.mqh"
#include "Utils.mqh"
#include "InputsHelper.mqh"

class CStrategyHelper {
public:
    // Function to check for three consecutive candles
    static bool ThreeCandles(MqlRates &secondLastCandle, MqlRates &lastCandle, MqlRates &currentCandle, datetime &currBarTime, datetime &lastBuyTradeTime, datetime &lastSellTradeTime, double RiskPercent=0, double TakeProfit=1, double LotSize=0.01) {
        double slInPoints = 0;
        //--- Conditions for BUY & SELL for absolute 3 Bars in which middle one is highest/lowest among three
        // Check for BUY conditions
        if (secondLastCandle.high > lastCandle.high && secondLastCandle.low > lastCandle.low && lastCandle.high < currentCandle.high && lastCandle.low < currentCandle.low)
        {
            string comment = "3C-BUY";
            // Place a BUY order if the current price breaks the second-to-last candle's high
            if (currentCandle.close > secondLastCandle.high && CTradeHelper::CheckActiveTrades(_Symbol, POSITION_TYPE_BUY) < MaxTradePerSide)
            {
                if(currBarTime == lastBuyTradeTime) return false; // Not a new candle
                LogMessage("Placing BUY order at" + DoubleToString(currentCandle.close, _Digits));
                double entryPrice = secondLastCandle.high;
                double sl = lastCandle.low; // Stop loss at the lowest low of the two candles
                double tp = entryPrice + (entryPrice - sl) * TakeProfit; // Take profit = 2x risk
                slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
                if (RiskPercent > 0)
                    LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
                if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_BUY, LotSize, entryPrice, sl, tp, comment)){
                    LogMessage("BUY order placed.");
                    lastBuyTradeTime = currBarTime;
                    return true;
                }
            }
        }
        // Check for SELL conditions
        else if (secondLastCandle.low < lastCandle.low && secondLastCandle.high < lastCandle.high && lastCandle.low > currentCandle.low && lastCandle.high > currentCandle.high)
        {
            string comment = "3C-SELL";
            // Place a SELL order if the current price breaks the second-to-last candle's low
            if (currentCandle.close < secondLastCandle.low && CTradeHelper::CheckActiveTrades(_Symbol, POSITION_TYPE_SELL) < MaxTradePerSide)
            {
                if(currBarTime == lastSellTradeTime) return false; // Not a new candle
                LogMessage("Placing SELL order at" + DoubleToString(currentCandle.close, _Digits));
                double entryPrice = secondLastCandle.low;
                double sl = lastCandle.high; // Stop loss at the highest high of the two candles
                double tp = entryPrice - (sl - entryPrice) * TakeProfit; // Take profit = 2x risk
                slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
                if (RiskPercent > 0)
                    LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
                if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_SELL, LotSize, entryPrice, sl, tp, comment)) {
                    LogMessage("SELL order placed.");
                    lastSellTradeTime = currBarTime;
                    return true;
                }
            }
        }
        return false;
    }

    // Function to check for four consecutive candles
    static bool FourCandles(MqlRates &thirdLastCandle, MqlRates &secondLastCandle, MqlRates &lastCandle, MqlRates &currentCandle, datetime &currBarTime, datetime &lastBuyTradeTime, datetime &lastSellTradeTime, double RiskPercent=0, double TakeProfit=1, double LotSize=0.01) {
        double slInPoints = 0;
        //--- Conditions for BUY & SELL for absolute 4 Bars in which second one is highest/lowest among three
        // Check for BUY conditions
        if (thirdLastCandle.high > secondLastCandle.high && thirdLastCandle.low > secondLastCandle.low && secondLastCandle.high < lastCandle.high && secondLastCandle.low < lastCandle.low)
        {
            string comment = "4C-BUY";
            // Place a BUY order if the current price breaks the second-to-last candle's high
            if (lastCandle.high < thirdLastCandle.high && CTradeHelper::CheckActiveTrades(_Symbol, POSITION_TYPE_BUY) < MaxTradePerSide)
            {
                if(lastCandle.high < currentCandle.close) {
                    if(currBarTime == lastBuyTradeTime) return false; // Not a new candle
                    LogMessage("Placing BUY order at" + DoubleToString(lastCandle.close, _Digits));
                    double entryPrice = lastCandle.high;
                    double sl = lastCandle.low; // Stop loss at the lowest low of the two candles
                    double tp = entryPrice + (entryPrice - sl) * TakeProfit; // Take profit = 2x risk
                    slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
                    if (RiskPercent > 0)
                        LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
                    if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_BUY, LotSize, entryPrice, sl, tp, comment)) {
                        LogMessage("BUY order placed.");
                        lastBuyTradeTime = currBarTime;
                        return true;
                    }
                }
            }
        }
        // Check for SELL conditions
        else if (thirdLastCandle.low < secondLastCandle.low && thirdLastCandle.high < secondLastCandle.high && secondLastCandle.low > lastCandle.low && secondLastCandle.high > lastCandle.high)
        {
            string comment = "4C-SELL";
            // Place a SELL order if the current price breaks the second-to-last candle's low
            if (lastCandle.low > thirdLastCandle.low && CTradeHelper::CheckActiveTrades(_Symbol, POSITION_TYPE_SELL) < MaxTradePerSide)
            {
                if(lastCandle.low > currentCandle.close) {
                    if(currBarTime == lastSellTradeTime) return false; // Not a new candle
                    LogMessage("Placing SELL order at" + DoubleToString(lastCandle.close, _Digits));
                    double entryPrice = lastCandle.low;
                    double sl = lastCandle.high; // Stop loss at the highest high of the two candles
                    double tp = entryPrice - (sl - entryPrice) * TakeProfit; // Take profit = 2x risk
                    slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
                    if (RiskPercent > 0)
                        LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
                    if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_SELL, LotSize, entryPrice, sl, tp, comment)) {
                        LogMessage("SELL order placed.");
                        lastSellTradeTime = currBarTime;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    static bool The3rdStrategy(MqlRates &secondLastCandle, MqlRates &lastCandle, MqlRates &currentCandle, datetime &currBarTime, datetime &lastBuyTradeTime, datetime &lastSellTradeTime, double RiskPercent=0, double TakeProfit=1, double LotSize=0.01) {
        double slInPoints = 0;
        // Check for BUY conditions
        if(secondLastCandle.open > secondLastCandle.close && lastCandle.low < secondLastCandle.close && lastCandle.close > secondLastCandle.open && lastCandle.high < currentCandle.high) {
            string comment = "NC-BUY";
            if(currBarTime == lastBuyTradeTime) return false; // Not a new candle
            LogMessage("Placing BUY order at" + DoubleToString(lastCandle.close, _Digits));
            double entryPrice = currentCandle.high;
            double sl = lastCandle.low; // Stop loss at the lowest low of the two candles
            double tp = entryPrice + (entryPrice - sl) * TakeProfit; // Take profit = 2x risk
            slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
            if (RiskPercent > 0)
                LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
            if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_BUY, LotSize, entryPrice, sl, tp, comment)) {
                LogMessage("BUY order placed.");
                lastBuyTradeTime = currBarTime;
                return true;
            }
        }
        // Check for SELL conditions
        else if(secondLastCandle.open < secondLastCandle.close && lastCandle.high > secondLastCandle.open && lastCandle.close < secondLastCandle.open && lastCandle.low > currentCandle.low) {
            string comment = "NC-SELL";
            if(currBarTime == lastSellTradeTime) return false; // Not a new candle
            LogMessage("Placing SELL order at" + DoubleToString(lastCandle.close, _Digits));
            double entryPrice = currentCandle.low;
            double sl = lastCandle.high; // Stop loss at the highest high of the two candles
            double tp = entryPrice - (sl - entryPrice) * TakeProfit; // Take profit = 2x risk
            slInPoints = MathAbs(entryPrice - sl) / _Point; // Calculate stop loss in points
            if (RiskPercent > 0)
                LotSize = CalculateDynamicLotSize(slInPoints, RiskPercent);
            if(CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_SELL, LotSize, entryPrice, sl, tp, comment)) {
                LogMessage("SELL order placed.");
                lastSellTradeTime = currBarTime;
                return true;
            }
        }
        return false;
    }

    static void StrategyWithEma() {
/*
    // Check for BUY conditions
    //if (fastEMA > slowEMA && CTradeHelper::CheckActiveTrades(_Symbol) == 0) {
        //LogMessage("fastEMA > slowEMA. Checking Next Condition...B1");
        // Second-to-last candle is bearish with body > sum of wicks
        //if (secondLastCandle.open > secondLastCandle.close && secondLastBody > (secondLastUpperWick + secondLastLowerWick))
        //{
            // Last candle is bullish and its high is lower than the second-to-last candle's high
            if (secondLastCandle.high > lastCandle.high && secondLastCandle.low > lastCandle.low)
            {
                // Place a BUY order if the current price breaks the second-to-last candle's high
                if (currentCandle.close > secondLastCandle.high && CTradeHelper::CheckActiveTrades(_Symbol) == 0)
                {
                    if(currBarTime == lastBuyTradeTime) return; // Not a new candle
                    LogMessage("Placing BUY order at" + DoubleToString(currentCandle.close, _Digits));
                    double entryPrice = lastCandle.high;
                    double sl = lastCandle.low; // Stop loss at the lowest low of the two candles
                    double tp = entryPrice + (entryPrice - sl) * TakeProfit; // Take profit = 2x risk
                    CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_BUY, LotSize, entryPrice, sl, tp);
                    Print("BUY order placed.");
                    lastBuyTradeTime = currBarTime;
                }
            }
        //}
    //}

    // Check for SELL conditions
    //else if (fastEMA < slowEMA && CTradeHelper::CheckActiveTrades(_Symbol) == 0) {
        // Second-to-last candle is bullish with body > sum of wicks
        //if (secondLastCandle.close > secondLastCandle.open && secondLastBody > (secondLastUpperWick + secondLastLowerWick))
        //{
            // Last candle is bearish and its low is higher than the second-to-last candle's low
            if (secondLastCandle.low < lastCandle.low && secondLastCandle.high < lastCandle.high)
            {
                // Place a SELL order if the current price breaks the second-to-last candle's low
                if (currentCandle.close < secondLastCandle.low && CTradeHelper::CheckActiveTrades(_Symbol) == 0)
                {
                    if(currBarTime == lastSellTradeTime) return; // Not a new candle
                    LogMessage("Placing SELL order at" + DoubleToString(currentCandle.close, _Digits));
                    double entryPrice = lastCandle.low;
                    double sl = lastCandle.high; // Stop loss at the highest high of the two candles
                    double tp = entryPrice - (sl - entryPrice) * TakeProfit; // Take profit = 2x risk
                    CTradeHelper::PlaceOrder(_Symbol, ORDER_TYPE_SELL, LotSize, entryPrice, sl, tp);
                    Print("SELL order placed.");
                    lastSellTradeTime = currBarTime;
                }
            }
        //}
    //}
*/
    }
};

#endif // __STRATEGY_HELPER_MQH__