#property indicator_separate_window
#property indicator_buffers 1
#property indicator_plots   1

//--- plot tick count
#property indicator_label1  "TickCount"
#property indicator_type1   DRAW_HISTOGRAM
#property indicator_color1  clrBlue
#property indicator_width1  2

//--- indicator buffer
double tickCountBuffer[];

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
{
   // Set the buffer as a series
   SetIndexBuffer(0, tickCountBuffer, INDICATOR_DATA);
   return(INIT_SUCCEEDED);
}

//+------------------------------------------------------------------+
//| Custom indicator iteration function                              |
//+------------------------------------------------------------------+
int OnCalculate(const int rates_total,
                const int prev_calculated,
                const datetime &time[],
                const double &open[],
                const double &high[],
                const double &low[],
                const double &close[],
                const long &tick_volume[],
                const long &volume[],
                const int &spread[])
{
   long tickCount = GlobalVariableGet("TickCount");
   for(int i = prev_calculated; i < rates_total; i++)
   {
      if(i > 1) tickCountBuffer[i-1] = tickCount;
   }
   return(rates_total);
}