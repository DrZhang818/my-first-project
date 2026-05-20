#ifndef __UTILS_MQH__
#define __UTILS_MQH__

// Utils.mqh
// Utility functions for logging, error handling, and data retrieval

#include "InputsHelper.mqh"

// Function to log messages to the Experts log
void LogMessage(const string message) {
    // bool logging = GlobalVariableGet("logging");
    if(logging) Print("ℹ️ > [EMA-Trading-Strategy] ", message);
}

// Function to retrieve OHLC data for specified candles
bool GetOHLCData(const string symbol, ENUM_TIMEFRAMES timeframe, int shift, double &open, double &high, double &low, double &close) {
    MqlRates rates[];
    if (CopyRates(symbol, timeframe, shift, 1, rates) > 0) {
        open = rates[0].open;
        high = rates[0].high;
        low = rates[0].low;
        close = rates[0].close;
        return true;
    }
    return false;
}

//+------------------------------------------------------------------+
//| Helper: get the end of the current day in server time            |
//+------------------------------------------------------------------+
datetime GetEndOfDayExpiration()
{
    datetime now = TimeCurrent();
    MqlDateTime dt;
    TimeToStruct(now, dt);
    dt.hour = 23;
    dt.min = 59;
    dt.sec = 59;
    return StructToTime(dt);
}

// Function to calculate lot size based on SL (in points) and risk percentage for EURUSD
double CalculateDynamicLotSize(double slPoints, double riskPercent)
{
    // Get the account balance
    double accountBalance = AccountInfoDouble(ACCOUNT_BALANCE);
    
    double lotSize = 0;
    double pointValue = 0;
    double riskAmount;
    
    // Get the tick value and tick size for the current symbol
    double tickValue = SymbolInfoDouble(_Symbol, SYMBOL_TRADE_TICK_VALUE);
    double tickSize = SymbolInfoDouble(_Symbol, SYMBOL_TRADE_TICK_SIZE);

    // Ensure tick value and tick size are valid
    if (tickValue <= 0 || tickSize <= 0)
    {
        Print("Error: Invalid tick value or tick size for symbol ", _Symbol);
        return 0.0;
    }
    
    if(_Digits >= 4) {
        // Calculate the risk amount in the account currency
        riskPercent = NormalizeDouble(riskPercent, 2);
        riskAmount = (riskPercent / 100.0) * accountBalance;
        riskAmount = NormalizeDouble(riskAmount, _Digits);
        slPoints = NormalizeDouble(slPoints, _Digits);

        // Calculate the value of 1 point in the account currency
        double current_ask = SymbolInfoDouble(_Symbol, SYMBOL_ASK);
        pointValue = NormalizeDouble((_Point / current_ask) * MathPow(10, _Digits), _Digits);

        // Calculate the lot size
        lotSize = riskAmount / (slPoints * pointValue);
    }
    else {
        // Calculate the risk amount in the account currency
        riskPercent = NormalizeDouble(riskPercent, 2);
        riskAmount = (riskPercent / 100.0) * accountBalance;
        riskAmount = NormalizeDouble(riskAmount, _Digits);

        // Calculate the value of 1 point in the account currency
        pointValue = SymbolInfoDouble(_Symbol, SYMBOL_TRADE_TICK_VALUE) / SymbolInfoDouble(_Symbol, SYMBOL_TRADE_TICK_SIZE);

        // Calculate the lot size
        lotSize = riskAmount / (slPoints * pointValue);
    }
    // Ensure the lot size meets the broker's minimum and step requirements
    double minLot = SymbolInfoDouble(_Symbol, SYMBOL_VOLUME_MIN);
    double lotStep = SymbolInfoDouble(_Symbol, SYMBOL_VOLUME_STEP);
    double maxLot = SymbolInfoDouble(_Symbol, SYMBOL_VOLUME_MAX);

    if (lotSize < minLot)
    {
        LogMessage("Warning: Calculated lot size is below the minimum lot size. Adjusting to minimum.");
        lotSize = minLot;
    }
    else if (lotSize > maxLot)
    {
        LogMessage("Warning: Calculated lot size exceeds the maximum lot size. Adjusting to maximum.");
        lotSize = maxLot;
    }

    // Round the lot size to the nearest valid step
    lotSize = MathFloor(lotSize / lotStep) * lotStep;
    LogMessage("Final lot size: " + DoubleToString(lotSize) + " for SL in points: " + DoubleToString(slPoints) + " (pointValue: " + DoubleToString(pointValue) + ") and risk percentage: " + DoubleToString(riskPercent)); // debugging
    LogMessage(" with account balance: " + DoubleToString(accountBalance) + " and risk amount: " + DoubleToString(riskAmount) + ", _Point: " + DoubleToString(_Point) + ", _Digits: " + DoubleToString(_Digits)); // debugging
    return lotSize;
}

// Helper Function to get points value for adding/subtracting to/from SL/TP
double GetPointsValue(double pointsValue)
{
    return NormalizeDouble(MathAbs(pointsValue / MathPow(10, _Digits)), _Digits);
}

//--- Helper: Convert enum to int hour/minute
int EnumHourToInt(HourEnum h)   { return (int)h; }
int EnumMinuteToInt(MinuteEnum m) { return (int)m * 5; }

//--- Helper: Check if time is within active window
bool IsActiveTime()
{
    MqlDateTime tm;
    TimeToStruct(TimeCurrent(), tm);
    int now = tm.hour*60 + tm.min;
    int start = EnumHourToInt(ActiveHourStart) * 60 + EnumMinuteToInt(ActiveMinuteStart);
    //int end   = EnumHourToInt(ActiveHourEnd) * 60 + EnumMinuteToInt(ActiveMinuteEnd);
   
   return (now >= start );  // && now <= end
}

#endif // __UTILS_MQH__
