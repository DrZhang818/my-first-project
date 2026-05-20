//--- displays the size of each candle in pips in a separate window. 
//--- It uses MQL5's inbuilt features and classes for better compatibility and performance.
#property copyright "bill"
#property link      "bill"
#property version   "1.01"
#property indicator_separate_window
#property indicator_buffers 3       // (plots remain 2, as Optimum is for Data Window only)
#property indicator_plots   3       // Two plots: one for the histogram and one for the SMA line

//--- plot settings for the histogram
#property indicator_label1  "Candle Size (Pips)"
#property indicator_type1   DRAW_HISTOGRAM
#property indicator_color1  clrBlue
#property indicator_width1  2

//--- plot settings for the SMA line
#property indicator_label2  "SMA"
#property indicator_type2   DRAW_LINE
#property indicator_color2  clrRed
#property indicator_width2  2

#property indicator_label3  "Optimum"
#property indicator_type3   DRAW_NONE

input int period = 22; // SMA period
input double howMuchBig = 10; // How much bigger from ARTR? (in %)
//--- indicator buffers
double CandleSizeBuffer[];
double SMABuffer[];
double OptimumBuffer[];

//--- OnInit function
int OnInit()
{
    //--- Bind the buffers to the indicator
    SetIndexBuffer(0, CandleSizeBuffer, INDICATOR_DATA);
    SetIndexBuffer(1, SMABuffer, INDICATOR_DATA);
    SetIndexBuffer(2, OptimumBuffer, INDICATOR_DATA);
   
    // Set Short indicator name
   IndicatorSetString(INDICATOR_SHORTNAME, "Size-In-Pips : ");
    // Set dynamic label for SMA line
   PlotIndexSetString(1,PLOT_LABEL,"SMA("+period+")");
    // Set dynamic label for Optimum
   PlotIndexSetString(2,PLOT_LABEL,"Optimum ("+howMuchBig+"%)");

    //--- Set digits for the indicator
    IndicatorSetInteger(INDICATOR_DIGITS, _Digits);

    return(INIT_SUCCEEDED);
}

//--- OnCalculate function
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
    //--- Ensure rates_total is valid
    if (rates_total <= 0)
        return(0);

    //--- Start calculation from the last calculated bar
    int start = prev_calculated > 0 ? prev_calculated - 1 : 0;

    //--- Calculate the candle size in pips
    for (int i = start; i < rates_total; i++)
    {
        CandleSizeBuffer[i] = NormalizeDouble((high[i] - low[i]) / (_Point), 2);
    }

    //--- Calculate the SMA(period) on the CandleSizeBuffer
    for (int i = start; i < rates_total; i++)
    {
        if (i >= period - 1)
        {
            double sum = 0.0;
            for (int j = 0; j < period; j++)
            {
                sum += CandleSizeBuffer[i - j];
            }
            SMABuffer[i] = NormalizeDouble(sum / period, 2);
        }
        else
        {
            SMABuffer[i] = 0.0; // Not enough data for SMA
        }
    }

    //--- Calculate the Optimum buffer
    for (int i = start; i < rates_total; i++)
    {
        OptimumBuffer[i] = CalculateOptimum(CandleSizeBuffer[i], SMABuffer[i]);
    }

    return(rates_total);
}

//--- Function to calculate Optimum value
int CalculateOptimum(double candleSize, double smaValue)
{
    if (smaValue == 0.0)
        return 0;
    if (candleSize > smaValue * ( 1 + (howMuchBig / 100)))
        return 1;
    return 0;
}