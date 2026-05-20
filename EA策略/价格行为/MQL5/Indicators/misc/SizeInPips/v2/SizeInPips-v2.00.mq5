//--- displays the size of each candle in Points in a separate window. 
//--- It uses MQL5's inbuilt features and classes for better compatibility and performance.
#property copyright "bill"
#property link      "bill"
#property version   "2.00"
#property indicator_separate_window
#property indicator_buffers 7       // ?(plots remain 2, as Optimum is for Data Window only)
#property indicator_plots   7       // ?Two plots: one for the histogram and one for the SMA line

//--- plot settings for the histogram
#property indicator_label1  "Candle Size (Points)"
#property indicator_type1   DRAW_HISTOGRAM
#property indicator_color1  clrBlue
#property indicator_width1  2

//--- plot settings for the histogram
#property indicator_label2  "Candle Size (Points)"
#property indicator_type2   DRAW_HISTOGRAM
#property indicator_color2  DodgerBlue
#property indicator_width2  2

//--- plot settings for the SMA line
#property indicator_label3  "SMA H-L"
#property indicator_type3   DRAW_LINE
#property indicator_color3  clrRed
#property indicator_width3  2

//--- plot settings for the SMA line
#property indicator_label4  "SMA O-C"
#property indicator_type4   DRAW_LINE
#property indicator_color4  clrTomato
#property indicator_width4  2

#property indicator_label5  "Optimum"
#property indicator_type5   DRAW_NONE

#property indicator_label6  "Custom SL"
#property indicator_type6   DRAW_LINE
#property indicator_color6  clrDodgerBlue
#property indicator_type6   DRAW_LINE
#property indicator_width6  2

#property indicator_label7  "Custom SL ATR"
#property indicator_type7   DRAW_LINE
#property indicator_color7  clrOrangeRed
#property indicator_type7   DRAW_LINE
#property indicator_width7  2

enum CalcType { High_Low, Open_Close};
enum DDType { Prev_Close_To_Max, Prev_HighLow_To_Max, Open_To_Max};

input int period = 22;                      // SMA period
input double howMuchBig = 10;               // How much bigger from ATR? (in %)
input CalcType calcType = High_Low;         // ATR: High-Low or Open-Close
input DDType ddType = Prev_Close_To_Max;    // Custom ATR for SL:
//--- indicator buffers
double CandleSizeBuffer[];
double CandleSizeBuffer2[];
double SMABuffer[];
double SMABuffer2[];
double OptimumBuffer[];
double CustomSLBuffer[];
double CustomSLATRBuffer[];

//--- OnInit function
int OnInit()
{
    //--- Bind the buffers to the indicator
    SetIndexBuffer(0, CandleSizeBuffer, INDICATOR_DATA);
    SetIndexBuffer(1, CandleSizeBuffer2, INDICATOR_DATA);
    SetIndexBuffer(2, SMABuffer, INDICATOR_DATA);
    SetIndexBuffer(3, SMABuffer2, INDICATOR_DATA);
    SetIndexBuffer(4, OptimumBuffer, INDICATOR_DATA);
    SetIndexBuffer(5, CustomSLBuffer, INDICATOR_DATA);
    SetIndexBuffer(6, CustomSLATRBuffer, INDICATOR_DATA);

    // Set Short indicator name
    IndicatorSetString(INDICATOR_SHORTNAME, "Size-In-Points : ");
    // Set dynamic label for H-L SMA line
    PlotIndexSetString(2,PLOT_LABEL,"SMA H-L("+period+")");
    // Set dynamic label for O-C SMA line
    PlotIndexSetString(3,PLOT_LABEL,"SMA O-C("+period+")");
    // Set dynamic label for Optimum
    PlotIndexSetString(4,PLOT_LABEL,"Optimum ("+howMuchBig+"%)");
    // Set dynamic label for Custom SL ATR
    PlotIndexSetString(6,PLOT_LABEL,"Custom SL ATR("+period+")");
    //--- Set digits for the indicator
    IndicatorSetInteger(INDICATOR_DIGITS, 1);

    //--- Set dynamic label for Custom SL
    if(ddType == Prev_Close_To_Max) {
        PlotIndexSetString(5,PLOT_LABEL,"Custom SL(Prev_Close_To_Max)");
    }
    else if(ddType == Prev_HighLow_To_Max) {
        PlotIndexSetString(5,PLOT_LABEL,"Custom SL(Prev_HighLow_To_Max)");
    }
    else if(ddType == Open_To_Max) {
        PlotIndexSetString(5,PLOT_LABEL,"Custom SL(Open_To_Max)");
    }

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

    //--- Calculate the candle size in Points
    if(calcType == High_Low) {
        PlotIndexSetString(0,PLOT_LABEL,"Candle Size (Hi-Lo)");
        PlotIndexSetString(1,PLOT_LABEL,"Candle Size (Opn-Cls)");
        for (int i = start; i < rates_total; i++) {
            CandleSizeBuffer[i] = NormalizeDouble((MathAbs(high[i] - low[i])) / (_Point), 2);
            CandleSizeBuffer2[i] = NormalizeDouble((-1 * MathAbs(close[i] - open[i])) / (_Point), 2);
        }
    }
    else if (calcType == Open_Close) {
        PlotIndexSetString(0,PLOT_LABEL,"Candle Size (Opn-Cls)");
        PlotIndexSetString(1,PLOT_LABEL,"Candle Size (Hi-Lo)");
        for (int i = start; i < rates_total; i++) {
            CandleSizeBuffer[i] = NormalizeDouble((MathAbs(close[i] - open[i])) / (_Point), 2);
            CandleSizeBuffer2[i] = NormalizeDouble((-1 * MathAbs(high[i] - low[i])) / (_Point), 2);
        }
    }

    //--- Calculate the Custom SL buffer
    for (int i = start+1; i < rates_total; i++) {
        if(open[i-1] < close[i-1]) {    // Bullish Candle
            if(ddType == Prev_Close_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(close[i-1], low[i]);
            }
            else if(ddType == Prev_HighLow_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(high[i-1], low[i]);        
            }
            else if(ddType == Open_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(open[i], low[i]);        
            }
        }
        else if(open[i-1] > close[i-1]) {   // Bearish Candle
            if(ddType == Prev_Close_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(close[i-1], high[i]);
            }
            else if(ddType == Prev_HighLow_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(low[i-1], high[i]);        
            }
            else if(ddType == Open_To_Max) {
                CustomSLBuffer[i] = CalculateCustomSL(open[i], high[i]);
            }
        }
        else if(open[i-1] == close[i-1]) {  // Doji Candle
            CustomSLBuffer[i] = -1;    // Doji Candle, no Custom SL
        }
        else {
            CustomSLBuffer[i] = -1; // Not enough data for Custom SL
        }
    }

    //--- Calculate the SMA(period) on the CandleSizeBuffer
    for (int i = start; i < rates_total; i++)
    {
        if (i >= period - 1)
        {
            double sum = 0.0;
            double sum2 = 0.0;
            double slSum2 = 0.0;
            for (int j = 0; j < period; j++)
            {
                sum += CandleSizeBuffer[i - j];
                sum2 += CandleSizeBuffer2[i - j];
                slSum2 += CustomSLBuffer[i - j];
            }
            SMABuffer[i] = NormalizeDouble(sum / period, 2);
            SMABuffer2[i] = NormalizeDouble(sum2 / period, 2);
            CustomSLATRBuffer[i] = NormalizeDouble(slSum2 / period, 2);
        }
        else
        {
            SMABuffer[i] = 0.0; // Not enough data for SMA
            SMABuffer2[i] = 0.0; // Not enough data for SMA
            CustomSLATRBuffer[i] = 0.0; // Not enough data for SMA
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
    if (candleSize == 0.0)
        return 0;
    if (candleSize > smaValue * ( 1 + (howMuchBig / 100)))
        return 1;
    return 0;
}
//--- Function to calculate Custom SL value
double CalculateCustomSL(double candle, double prevCandle)
{
    return MathAbs(candle - prevCandle) / _Point;
}