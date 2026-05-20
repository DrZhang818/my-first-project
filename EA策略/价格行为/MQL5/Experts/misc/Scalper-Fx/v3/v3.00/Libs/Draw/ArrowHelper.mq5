//+------------------------------------------------------------------+
//|                                                  ArrowHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Draw arrow on chart at the trade level                           |
//+------------------------------------------------------------------+
void DrawPendingArrow(string name, MqlRates &rates[], int index, double price, bool isBuy)
{
   string arrowSymbol = isBuy ? "↑" : "↓";
   color arrowColor = isBuy ? clrGreen : clrRed;
   int arrowSize = 2.0; // Adjust size as needed

   // Remove any existing arrow with the same name
   ObjectDelete(0, name);

   // Draw the arrow on the chart
   if(!ObjectCreate(0, name, OBJ_ARROW, 0, rates[index].time, price))
   {
      Print("Failed to create arrow object: ", GetLastError());
      return;
   }
   ObjectSetInteger(0, name, OBJPROP_COLOR, arrowColor);
   ObjectSetInteger(0, name, OBJPROP_WIDTH, 2);
   ObjectSetInteger(0, name, OBJPROP_XSIZE, arrowSize);
   ObjectSetString(0, name, OBJPROP_TEXT, arrowSymbol);
}

//+------------------------------------------------------------------+
//| Draw arrow on chart at order placement                           |
//+------------------------------------------------------------------+
void DrawOrderArrow(string arrowName, const MqlRates &rates[], int index, double price, bool isBuy)
{
   color arrowColor = isBuy ? clrLime : clrRed;
   int arrowCode = isBuy ? 233 : 234; // 233: Up arrow, 234: Down arrow

   int buyArrowIndex = GetHighestCandleIndex(_Symbol, LowerTF, 5, 0); // Get the index of the high candle in the last 5 bars
   int sellArrowIndex = GetLowestCandleIndex(_Symbol, LowerTF, 5, 0); // Get the index of the low candle in the last 5 bars
   if(debugging) Print("🚦(DrawOrderArrow)>>> prev index: ", index);
   int arrIndex = (isBuy) ? buyArrowIndex : sellArrowIndex; // Use the index of the high/low candle for the arrow
   index = 9 - arrIndex; // Adjust the index
   if(debugging) Print("🚦(DrawOrderArrow)>>> buyArrowIndex: ", buyArrowIndex, " sellArrowIndex: ", sellArrowIndex, " index: ", index);

   // Remove any existing arrow with the same name
   ObjectDelete(0, arrowName);

   if(!ObjectCreate(0, arrowName, OBJ_ARROW, 0, rates[index].time, price))
   {
      Print("Failed to create arrow object: ", GetLastError());
      return;
   }
   ObjectSetInteger(0, arrowName, OBJPROP_COLOR, arrowColor);
   ObjectSetInteger(0, arrowName, OBJPROP_WIDTH, 1);
   ObjectSetInteger(0, arrowName, OBJPROP_ARROWCODE, arrowCode);
}

