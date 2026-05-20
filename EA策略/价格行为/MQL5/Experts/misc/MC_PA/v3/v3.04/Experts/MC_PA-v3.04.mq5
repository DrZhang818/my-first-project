//+------------------------------------------------------------------+
//|                                         EMA-Trading-Strategy.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.04"
//+------------------------------------------------------------------+
#include "../Include/InputsHelper.mqh"
#include "../Include/EMAHelper.mqh"
#include "../Include/Utils.mqh"
#include "../Include/TradeHelper.mqh"
#include "../Include/StrategyHelper.mqh"
//+------------------------------------------------------------------+

// Global variables
double fastEMA, slowEMA;
datetime lastSellTradeTime = 0;
datetime lastBuyTradeTime = 0;
bool ResetSLModifyCheck = false;
static datetime lastSlUpdateCheckCandleTime = 0;
static datetime lastSlTrailCheckCandleTime = 0;
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
{
    long supported = SymbolInfoInteger(_Symbol, SYMBOL_FILLING_MODE);
    string msg = "Supported filling modes for " + _Symbol + ": ";
    if(supported & ORDER_FILLING_FOK)   msg += "FOK ";
    if(supported & ORDER_FILLING_IOC)   msg += "IOC ";
    if(supported & ORDER_FILLING_RETURN)msg += "RETURN ";
    LogMessage(msg);

    // Optionally, warn if the selected mode is not supported
    if(!(supported & FillingMode)) {
        Print("WARNING: Selected filling mode is not supported for this symbol!");
        return INIT_FAILED;
    }
    // Attach the candle size average calculation indicator
    SizeInPipsHandle = iCustom(_Symbol, Timeframe, "misc/SizeInPips/v2/SizeInPips-v2.00", ci_period, ci_howMuchBig, ci_calcType, ci_ddType);
    if(SizeInPipsHandle == INVALID_HANDLE) {
        Print("Failed to create indicator handle for SizeInPips-v2.00");
        return INIT_FAILED;
    }
    // List of timeframes to skip (example: skip M1 and M5)
    ENUM_TIMEFRAMES skipFrames[] = { PERIOD_M1, PERIOD_M2, PERIOD_M3, PERIOD_M4, PERIOD_M5, PERIOD_M6, PERIOD_M10, PERIOD_M12, PERIOD_M15, PERIOD_M20, PERIOD_M30, PERIOD_H1, PERIOD_H2, PERIOD_H3, PERIOD_H6, PERIOD_H8};

    for(int i=0; i<ArraySize(skipFrames); i++)
    {
        if(Timeframe == skipFrames[i])
        {
            Print("This timeframe is skipped for testing: ", EnumToString(_Period));
            return INIT_FAILED; // EA will not run on this timeframe
        }
    }
    //--- create timer
    EventSetTimer(1);
    // Initialization code here
    Print("EMA Trading Strategy Initialized");
    return INIT_SUCCEEDED;
}

//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
{
    // Cleanup code here
    Print("EMA Trading Strategy Deinitialized");
}

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
{

}

//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer() {
    
    
    if(!IsActiveTime()) return;

    // Get current EMAs
    // fastEMA = GetEMA(_Symbol, Timeframe, FastEMAPeriod);
    // slowEMA = GetEMA(_Symbol, Timeframe, SlowEMAPeriod);

    // Get the OHLC data for the last two completed candles
    MqlRates rates[4];
    MqlRates m1Rates[2];
    if (CopyRates(_Symbol, Timeframe, 0, 4, rates) < 4)
    {
        Print("Error retrieving candle data.");
        return;
    }
    if (CopyRates(_Symbol, PERIOD_M1, 0, 2, m1Rates) < 2)
    {
        Print("Error retrieving M1 candle data.");
        return;
    }

    // Get last closed candle time
    datetime currBarTime = rates[3].time;   // Last closed candle

    // Candle references
    MqlRates currentCandle = rates[3];      // Currently forming candle
    MqlRates lastCandle = rates[2];         // Last completed candle
    MqlRates secondLastCandle = rates[1];   // Second-to-last completed candle
    MqlRates thirdLastCandle = rates[0];    // Third-to-last completed candle

    // Calculate the body and wicks of the second-to-last candle
    double secondLastBody = MathAbs(secondLastCandle.close - secondLastCandle.open);
    double secondLastUpperWick = secondLastCandle.high - MathMax(secondLastCandle.close, secondLastCandle.open);
    double secondLastLowerWick = MathMin(secondLastCandle.close, secondLastCandle.open) - secondLastCandle.low;

    bool is3CtradeTriggered = false;
    if(Activate3CStrategy == true && CStrategyHelper::ThreeCandles(secondLastCandle, lastCandle, currentCandle, currBarTime, lastBuyTradeTime, lastSellTradeTime, RiskPercentage, TakeProfit, LotSize)) {
        LogMessage("ThreeCandles Trade Placed");
        ResetSLModifyCheck = false;
        is3CtradeTriggered = true;
    }
    if(Activate4CStrategy == true && is3CtradeTriggered == false) {
        bool placedOrNot = false;
        placedOrNot = CStrategyHelper::FourCandles(thirdLastCandle, secondLastCandle, lastCandle, currentCandle, currBarTime, lastBuyTradeTime, lastSellTradeTime, RiskPercentage, TakeProfit, LotSize);
        if(placedOrNot) {
            LogMessage("FourCandles Trade Placed");
            ResetSLModifyCheck = false;
        }
    }
    if(Activate3rdStrategy == true) {
        bool placedOrNot = false;
        placedOrNot = CStrategyHelper::The3rdStrategy(secondLastCandle, lastCandle, currentCandle, currBarTime, lastBuyTradeTime, lastSellTradeTime, RiskPercentage, TakeProfit, LotSize);
        if(placedOrNot) {
            LogMessage("The3rdStrategy Trade Placed");
            ResetSLModifyCheck = false;
        }
    }
    if(currBarTime != lastSlUpdateCheckCandleTime && CutSLToHalf == true) {
        if(CTradeHelper::CheckActiveTrades(_Symbol) != 0 && !ResetSLModifyCheck) {
            ResetSLModifyCheck = CTradeHelper::UpdateStopLoss(_Symbol, Timeframe);
            if (ResetSLModifyCheck) {
                lastSlUpdateCheckCandleTime = currBarTime;
                LogMessage("<<<<<<<<<<<<<<<<<<<<<<<<<< Cutted SL to half for all open positions. ->->->->->->->->->->->->");
            }
        }
    }
    if(currBarTime != lastSlTrailCheckCandleTime && TrailSL == true) {
        if(CTradeHelper::CheckActiveTrades(_Symbol) != 0) {
            // LogMessage("->->->->->->->->->->->->->->->->->->->->->->->->->->->->->-> Trailing SL... <<<<<<<<<<<<<<<<<<<<<<<<<<");
            if (CTradeHelper::TrailStopLoss(_Symbol, Timeframe, m1Rates[0].close)) {
                lastSlTrailCheckCandleTime = currBarTime;
                LogMessage("->->->->->->->->->->->-> SL Trailed... <<<<<<<<<<<<<<<<<<<<<<<<<<");
            }
        }
    }
}
//+------------------------------------------------------------------+
//| Function to retrieve OHLC data                                   |
//+------------------------------------------------------------------+
void GetOHLCData(string symbol, ENUM_TIMEFRAMES timeframe, datetime time, double &open, double &high, double &low, double &close)
{
    // Logic to retrieve OHLC data
}

//+------------------------------------------------------------------+