//+------------------------------------------------------------------+
//|                                                CandlesHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

enum CandleOrderType { NONE, ASC, DESC };

//+------------------------------------------------------------------+
//| Helper: Get Highest/Lowest in range                              |
//+------------------------------------------------------------------+
double GetHighest(string symbol, ENUM_TIMEFRAMES tf, int range, int shift=0) {
   double highest = iHigh(symbol, tf, shift);
   for(int i=shift+1; i<shift+range; i++)
      if(iHigh(symbol, tf, i) > highest) highest = iHigh(symbol, tf, i);
   return Round5(highest);
}

double GetLowest(string symbol, ENUM_TIMEFRAMES tf, int range, int shift=0) {
   double lowest = iLow(symbol, tf, shift);
   for(int i=shift+1; i<shift+range; i++)
      if(iLow(symbol, tf, i) < lowest) lowest = iLow(symbol, tf, i);
   return Round5(lowest);
}

int GetLowestCandleIndex(string symbol, ENUM_TIMEFRAMES tf, int range, int shift=0) {
   double lowest = iLow(symbol, tf, shift);
   int lowestIndex = 0;
   for(int i=shift+1; i<shift+range; i++)
      if(iLow(symbol, tf, i) < lowest) {
         lowest = iLow(symbol, tf, i);
         lowestIndex = i;
      }
   return lowestIndex;
}

int GetHighestCandleIndex(string symbol, ENUM_TIMEFRAMES tf, int range, int shift=0) {
   double highest = iHigh(symbol, tf, shift);
   int highestIndex = 0;
   for(int i=shift+1; i<shift+range; i++)
      if(iHigh(symbol, tf, i) > highest) {
         highest = iHigh(symbol, tf, i);
         highestIndex = i;
      }
   return highestIndex;
}

//+------------------------------------------------------------------+
//| Helper: heck for extra ordinaty conditions within a candle       |
//+------------------------------------------------------------------+
void CheckForExtraOrdinaryCandle(ulong ticket) {
   
   if(!PositionSelectByTicket(ticket)) return;

   MqlRates rates[];
   if(CopyRates(_Symbol, LowerTF, 0, 2, rates) < 2) return;

   double   old_sl         =  PositionGetDouble(POSITION_SL);
   double   price_open     =  PositionGetDouble(POSITION_PRICE_OPEN);
   double   price_current  =  PositionGetDouble(POSITION_PRICE_CURRENT);

   double high = rates[1].high;
   double low = rates[1].low;
   double diff = MathAbs(high - low);

   if (debugging) Print("🔄🖲️(CheckForExtraOrdinaryCandle)>>> MathAbs(old_sl - price_open):" , 
      Round5(MathAbs(old_sl - price_open)), " x extraOrdinaryFactor(",extraOrdinaryFactor,"): ", 
      Round5(MathAbs(old_sl - price_open)) * extraOrdinaryFactor, " MathAbs(price_current - price_open): ", 
      Round5(MathAbs(price_current - price_open)), " _Point * 40: ", _Point * 40);
   
   if(diff > MathAbs(price_current - price_open) * extraOrdinaryFactor)
      if((price_open > old_sl && price_current > price_open) || (price_open < old_sl && price_current < price_open)) {
         trade.PositionClose(ticket);
         if(debugging) Print("🔄 💥 🔝 ✨ 🪄 🧙‍♂️ (CheckForExtraOrdinaryCandle)>>> BUY POSITION CLOSED DUE TO EXTRAORDINARY FACTOR ");
         if(debugging) Print("📊 Previous 10 candles: 🔝 Highest = ", high, " | 🔻 Lowest = ", low, " | Diff: ", diff);
      }
}

//+------------------------------------------------------------------+
//| Helper: Check if last 4 closed candles are ascending or descending
//+------------------------------------------------------------------+

CandleOrderType  CheckLast4BarCloses(const MqlRates &rates[])
{
   // rates[]: index 0 = oldest, index 9 = most recent closed candle
   // Last 4 closed candles: rates[6], rates[7], rates[8], rates[9]
   double o_1 = rates[4].open;
   double c0 = rates[5].close;
   double c1 = rates[6].close;
   double c2 = rates[7].close;
   double c3 = rates[8].close;

   if(debugging) Print("📈(CheckLast4BarCloses)>>> Last 4 closes: o_1: ", o_1, ", c0: ", c0, ", c1: ", c1, ", c2: ", c2, ", c3: ", c3);

   if(o_1 < c0 && c0 < c1 && c1 < c2 && c2 < c3) {
      if(debugging) Print("🔼(CheckLast4BarCloses)>>> Last 4 closes: ASCENDING");
      return ASC;
   }
   if(o_1 > c0 && c0 > c1 && c1 > c2 && c2 > c3) {
      if(debugging) Print("🔽(CheckLast4BarCloses)>>> Last 4 closes: DESCENDING");
      return DESC;
   }
   if(debugging) Print("🚫(CheckLast4BarCloses)>>> Last 4 closes: NONE");
   return NONE;
}

CandleOrderType CheckLast4Closes_Ema(const MqlRates &rates[], double ema8_M5, double ema13_M5, double ema21_M5)
{
   // rates[]: index 0 = oldest, index 9 = most recent closed candle
   // Last 4 closed candles: rates[6], rates[7], rates[8], rates[9]
   double o_1 = rates[4].open;
   double c0 = rates[5].close;
   double c1 = rates[6].close;
   double c2 = rates[7].close;
   double c3 = rates[8].close;

   // ema8_M5 < ema13_M5 && ema13_M5 < ema21_M5

   if(debugging) Print("📈(CheckLast4Closes_Ema)>>> Last 4 closes: o_1: ", o_1, ", c0: ", c0, ", c1: ", c1, ", c2: ", c2, ", c3: ", c3);

   if(o_1 < c0 && c0 < c1 && c1 < c2 && c2 < c3 && ema8_M5 > ema13_M5 && ema13_M5 > ema21_M5) {
      if(debugging) Print("🔼(CheckLast4Closes_Ema)>>> Last 4 closes: ASCENDING");
      return ASC;
   }
   if(o_1 > c0 && c0 > c1 && c1 > c2 && c2 > c3 && ema8_M5 < ema13_M5 && ema13_M5 < ema21_M5) {
      if(debugging) Print("🔽(CheckLast4Closes_Ema)>>> Last 4 closes: DESCENDING");
      return DESC;
   }
   if(debugging) Print("🚫(CheckLast4Closes_Ema)>>> Last 4 closes: NONE");
   return NONE;
}

//+------------------------------------------------------------------+
//| Helper: Print MqlRates array in a single line                    |
//+------------------------------------------------------------------+
void PrintRates(const MqlRates &rates[], int count)
{
   string msg = "⁉️⁉️⁉️⁉️ rates[]: ";
   for(int i = 0; i < count; i++)
   {
      msg += "[" + IntegerToString(i) + ": t=" + TimeToString(rates[i].time, TIME_DATE|TIME_MINUTES) +
             ", o=" + DoubleToString(rates[i].open, _Digits) +
             ", h=" + DoubleToString(rates[i].high, _Digits) +
             ", l=" + DoubleToString(rates[i].low, _Digits) +
             ", c=" + DoubleToString(rates[i].close, _Digits) + "]";
      if(i < count - 1) msg += " | ";
   }
   Print(msg);
}
