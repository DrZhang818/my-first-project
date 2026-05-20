//+------------------------------------------------------------------+
//|                                              RectangleHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Draw a colored rectangle with background fill over a range of    |
//| candles in rates[].                                              |
//| leftIdx: index of the first candle in rates[]                    |
//| rightIdx: index of the last candle in rates[]                    |
//| color: fill color                                                |
//+------------------------------------------------------------------+
void DrawCandleRectangle(const string name, const MqlRates &rates[], int leftIdx, int rightIdx, color fillColor)
{
   string time_id = name + GenerateBatchID(rates[0].time);
   // uchar alpha = 0x55;  // 0x55 means 55/255=21.6 % of transparency 
   if(leftIdx < 0 || rightIdx < 0 || rightIdx < leftIdx)
      return;

   // Find highest high and lowest low in the range
   double highest = rates[leftIdx].high;
   double lowest = rates[leftIdx].low;
   for(int i = leftIdx; i <= rightIdx; i++)
   {
      if(rates[i].high > highest)
         highest = rates[i].high;
      if(rates[i].low < lowest)
         lowest = rates[i].low;
   }

   // Remove any existing rectangle with the same name
   ObjectDelete(0, time_id);

   // Draw the rectangle
   if(!ObjectCreate(0, time_id, OBJ_RECTANGLE, 0, rates[leftIdx].time, highest, rates[rightIdx].time, lowest))
   {
      Print("❌ Failed to create rectangle: ", GetLastError());
      return;
   }
   ObjectSetInteger(0, time_id, OBJPROP_COLOR, fillColor);
   ObjectSetInteger(0, time_id, OBJPROP_FILL, 1);          // 0=not filled, 1=filled
   ObjectSetInteger(0, time_id, OBJPROP_BACK, true);        // Draw in background
   // ObjectSetInteger(0, name, OBJPROP_TRANSPARENCY, 70);  // 0=opaque, 255=fully transparent
   ObjectSetInteger(0, time_id, OBJPROP_WIDTH, 1);          // Border width
}  

void CreateRectangleLabel(string name = "RectLabel", int x = 200, int y = 5) {
   string objName = name;
   if(ObjectFind(0, objName) >= 0)
      ObjectDelete(0, objName);

   if(!ObjectCreate(0, objName, OBJ_RECTANGLE_LABEL, 0, 0, 0))
      return;

   ObjectSetInteger(0, objName, OBJPROP_CORNER, CORNER_RIGHT_UPPER);
   ObjectSetInteger(0, objName, OBJPROP_XDISTANCE, x);
   ObjectSetInteger(0, objName, OBJPROP_YDISTANCE, y);
   ObjectSetInteger(0, objName, OBJPROP_XSIZE, x - y);
   ObjectSetInteger(0, objName, OBJPROP_YSIZE, x - y);
   ObjectSetInteger(0, objName, OBJPROP_BGCOLOR, clrLavender);     // Background color
   ObjectSetInteger(0, objName, OBJPROP_BORDER_TYPE, BORDER_RAISED);
   ObjectSetInteger(0, objName, OBJPROP_SELECTABLE, true);
   ObjectSetInteger(0, objName, OBJPROP_BACK, false);
   ChartRedraw(0);

}

int AddToRect( string labelName, string labelText, int y, int x = 185, int rang = clrBlueViolet)
{
   int nextyDist = y; // Next Y distance for the next label
   int xDist = x;     // Distance from right edge
   
   nextyDist = CreateOrUpdateLabel(labelName, labelText, xDist, nextyDist, rang);

   return nextyDist; // Return the next Y distance for the next label
}
