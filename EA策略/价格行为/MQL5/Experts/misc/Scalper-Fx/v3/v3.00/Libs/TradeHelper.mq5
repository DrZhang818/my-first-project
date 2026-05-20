//+------------------------------------------------------------------+
//|                                                  TradeHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

#include "Trades/PendingOrdersHelper.mq5"
#include "Trades/PositionsHelper.mq5"
#include "Trades/CombinedHelper.mq5"
#include "Trades/StopLossHelper.mq5"

//+------------------------------------------------------------------+
//| Funtion to set optimum SL level before placing a trade           |
//+------------------------------------------------------------------+
double SetOptimumSL(double entry, double sl, string type) {
   double diff = MathAbs(entry - sl);
   int slInPoints = Round5(diff * MathPow(10, _Digits));
   if(debugging) Print("🛡️(SetOptimumSL)|>>> TYPE: ", type, " | ENTRY: ", entry, " | SL: ", sl, " | DIFFERENCE (entry - sl): ", diff, " SL_IN_POINTS (diff * 10 ^ _Digits) : ", slInPoints, " BUT minSLPoints is: ", minSLPoints);
   if (slInPoints < minSLPoints){
      if(type == "buy")
         sl = entry - minSLPoints * _Point;
      else if(type == "sell")
         sl = entry + minSLPoints * _Point;
      else
         if(debugging) Print("🛡️(SetOptimumSL)|>>> Invalid type for SetOptimumSL: ", type);
   }
   if(debugging) Print("🛡️(SetOptimumSL)|>>> Optimum SL: ", sl);
   return sl;
}

//+------------------------------------------------------------------+
//| Final checks before OrderSend()                                  |
//+------------------------------------------------------------------+
bool finalCheckBeforeOrderSend() {
   // Check last 10 candles width (highest & lowest) should be greater than 80 points
   MqlRates rates[];
   if(CopyRates(_Symbol, PERIOD_CURRENT, 1, 10, rates) < 10)
    {
        Print("❌ Not enough candles to check highest/lowest.");
        return false;
    }

   double highest = rates[0].high;
   double lowest = rates[0].low;

   for(int i = 1; i < 10; i++)
   {
      if(rates[i].high > highest)
         highest = rates[i].high;
      if(rates[i].low < lowest)
         lowest = rates[i].low;
   }
   double diff = MathAbs(highest - lowest) / _Point;
   Print("📊 Previous 10 candles: 🔝 Highest = ", highest, " | 🔻 Lowest = ", lowest, " | Diff: ", diff);

   if ( diff < 80 ) {
      Print("📊 Width of last 10 candles is less than or equal to 8 pips, hence not placing any order.");
      DrawCandleRectangle("NoTrade_", rates, 0, 9, clrAqua);
      yPos = AddToRect("last10CLabel", StringFormat("10 Candles: %.1f < 8.0 pip", diff / 10), yPos);
      return false;
   }
   else {
      yPos = AddToRect("last10CLabel", StringFormat("10 Candles: %.1f > 8.0 pip", diff / 10), yPos);
   }
   return true;
}

