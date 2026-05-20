//+------------------------------------------------------------------+
//|                                             IndicatorsHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Helper: Get EMA value                                            |
//+------------------------------------------------------------------+
double GetEMA(string symbol, ENUM_TIMEFRAMES tf, int period, int shift=0) {
   int handle = iMA(symbol, tf, period, 0, MODE_EMA, PRICE_CLOSE);
   if(handle == INVALID_HANDLE) return 0.0;
   double buffer[];
   double value = 0.0;
   if(CopyBuffer(handle, 0, shift, 1, buffer) == 1)
      value = buffer[0];
   IndicatorRelease(handle); // Release the handle after use
   return Round5(value);
}

//+------------------------------------------------------------------+
//| v2.00 : Helper: Get ATR value                                    |
//+------------------------------------------------------------------+
double GetATR(string symbol, ENUM_TIMEFRAMES tf, int period, int shift=0)
{
   int handle = iATR(symbol, tf, period);
   if(handle == INVALID_HANDLE) return 0.0;
   double buffer[];
   double value = 0.0;
   if(CopyBuffer(handle, 0, shift, 1, buffer) == 1)
      value = buffer[0];
   IndicatorRelease(handle);
   return Round5(value);
}

//+------------------------------------------------------------------+
//| Helper: Check if all EMAs are at least minPoints apart           |
//+------------------------------------------------------------------+
bool AreEMAsApart(double ema1, double ema2, double ema3, double minPoints)
{
   double minDiff = minPoints * _Point;
   return (MathAbs(ema1 - ema2) >= minDiff &&
           MathAbs(ema1 - ema3) >= minDiff * 2 &&
           MathAbs(ema2 - ema3) >= minDiff);
}

bool AreEMAsApart(double ema1, double ema2, double minPoints)
{
   double minDiff = minPoints * _Point;
   return (MathAbs(ema1 - ema2) >= minDiff);
}
