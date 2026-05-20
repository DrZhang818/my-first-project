//+------------------------------------------------------------------+
//|                                                   TextHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Spread at price line on the chart                                |
//+------------------------------------------------------------------+
void DisplaySpreadOnPriceLine()
{
   double bid = SymbolInfoDouble(_Symbol, SYMBOL_BID);
   double ask = SymbolInfoDouble(_Symbol, SYMBOL_ASK);
   double spread = (ask - bid) / _Point;

   string objName = "BidAskSpreadLabel";
   string text = StringFormat("Spread: %.1f pts", spread);
   //    string text = StringFormat("Bid: %.5f\nAsk: %.5f\nSpread: %.1f pts", bid, ask, spread);

   // Remove if already exists
   if(ObjectFind(0, objName) >= 0)
      ObjectDelete(0, objName);

   // Get the time of the last visible bar and a price above the current high
   datetime t = iTime(_Symbol, PERIOD_CURRENT, 0);
   double   y = iHigh(_Symbol, PERIOD_CURRENT, 0) + 10 * _Point; // 10 points above current high

   // Create OBJ_TEXT at this time/price
   if(!ObjectCreate(0, objName, OBJ_TEXT, 0, t, y))
      return;

   ObjectSetInteger(0, objName, OBJPROP_CORNER, CORNER_LEFT_UPPER);
   ObjectSetInteger(0, objName, OBJPROP_FONTSIZE, 10);
   ObjectSetInteger(0, objName, OBJPROP_COLOR, C'58,58,58');
   ObjectSetString(0, objName, OBJPROP_TEXT, text);
   ObjectSetInteger(0, objName, OBJPROP_BACK, false);
}
