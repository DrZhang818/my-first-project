//+------------------------------------------------------------------+
//|                                                  LabelHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Helper to create or update a label                               |
//+------------------------------------------------------------------+
int CreateOrUpdateLabel(const string name, const string text = "Label Text", int xDist = 10, int yDist = 10, color textColor = clrLavenderBlush)
{
   // Remove if already exists
   if(ObjectFind(0, name) >= 0)
      ObjectDelete(0, name);

   if(ObjectCreate(0, name, OBJ_LABEL, 0, 0, 0))
   {
      ObjectSetInteger(0, name, OBJPROP_CORNER, CORNER_RIGHT_UPPER);
      ObjectSetInteger(0, name, OBJPROP_XDISTANCE, xDist);
      ObjectSetInteger(0, name, OBJPROP_YDISTANCE, yDist);
      ObjectSetInteger(0, name, OBJPROP_FONTSIZE, RectTextSize);
      ObjectSetInteger(0, name, OBJPROP_COLOR, textColor);
      ObjectSetString(0, name, OBJPROP_TEXT, text);
   }
   return yDist + 20; // Return the next Y distance for the next label
}

//+------------------------------------------------------------------+
//| Display Bid, Ask, and Spread as separate labels                  |
//+------------------------------------------------------------------+
int DisplayBidAskSpreadLabels(int y = 20, int x = 185)
{
   double bid = SymbolInfoDouble(_Symbol, SYMBOL_BID);
   double ask = SymbolInfoDouble(_Symbol, SYMBOL_ASK);
   double spread = (ask - bid) / _Point;

   int xDist = x;     // Distance from right edge
   int yDist = y;      // Distance from top edge
   int yStep = 20;      // Vertical space between labels

   int nextyDist = yDist;       // Next Y distance for the next label

   nextyDist = CreateOrUpdateLabel("BidLabel", StringFormat("Bid: %.5f", bid), xDist, nextyDist, clrLimeGreen);
   nextyDist = CreateOrUpdateLabel("AskLabel", StringFormat("Ask: %.5f", ask), xDist, nextyDist, clrOrangeRed);
   nextyDist = CreateOrUpdateLabel("SpreadLabel", StringFormat("Spread: %.1f pts", spread), xDist, nextyDist, clrDodgerBlue);

   return nextyDist; // Return the next Y distance for the next label
}
