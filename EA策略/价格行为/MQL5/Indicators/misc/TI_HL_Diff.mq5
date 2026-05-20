//+------------------------------------------------------------------+
//|                                      HL Diff Indicator |
//|                                    Copyright 2025, bill |
//|                                     bill |
//|                           Checks Higher High/Lower Low Formation |
//+------------------------------------------------------------------+

#property copyright "bill"
#property version   "1.03"
#property strict
#property indicator_separate_window
#property indicator_buffers 4
#property indicator_plots   4

//--- Plot settings for Higher High (HH) histogram
#property indicator_label1  "HH Diff (Pips)"
#property indicator_type1   DRAW_HISTOGRAM
#property indicator_color1  clrBlue
#property indicator_width1  2

//--- Plot settings for Lower Low (LL) histogram
#property indicator_label2  "LL Diff (Pips)"
#property indicator_type2   DRAW_HISTOGRAM
#property indicator_color2  clrRed
#property indicator_width2  2

#define ZERO_VALUE          (0)

//--- Indicator buffers
double HH_Buffer[];
double LL_Buffer[];
double EmptyPlaces_Buffer[]; // New buffer to store the value of 'empty places'
double CandleNum_Buffer[]; // New buffer to store the value of 'candle number'

//--- Plot settings for the Empty places buffer (hidden in the chart)
#property indicator_label3  "Empty Places"
#property indicator_type3   DRAW_NONE // Do not draw this buffer on the chart

//--- Plot settings for the Candle Number buffer (hidden in the chart)
#property indicator_label4  "Candle Number"
#property indicator_type4   DRAW_NONE // Do not draw this buffer on the chart

// Add input parameters for mode and date
enum CalculationMode { RecentCandlesMode, FromDateMode };
input CalculationMode Mode = RecentCandlesMode; // Mode: RecentCandles or FromDate
input datetime FromDate = D'2025.01.01 00:00'; // Start date for FromDate mode

// Add an input parameter to specify the number of recent candles
input int RecentCandles = 150; // Number of recent candles to display data for

 // Determine the starting point for calculation
 int start = 0;
 int countEmptyPlaces = 0; // Counter for empty places in the buffer
 int candleNum = 0; // Counter for empty places in the buffer

//+------------------------------------------------------------------+
//| Custom indicator initialization function                         |
//+------------------------------------------------------------------+
int OnInit()
{
    // Bind the buffers to the indicator
    SetIndexBuffer(0, HH_Buffer, INDICATOR_DATA);
    SetIndexBuffer(1, LL_Buffer, INDICATOR_DATA);
    SetIndexBuffer(2, EmptyPlaces_Buffer, INDICATOR_DATA); // Bind the empty places buffer
    SetIndexBuffer(3, CandleNum_Buffer, INDICATOR_DATA); // Bind the candle buffer

    // Set digits for the indicator
    IndicatorSetInteger(INDICATOR_DIGITS, _Digits);

    // Set a horizontal level at 0 (middle of the window)
    IndicatorSetDouble(INDICATOR_LEVELVALUE, 0, 0.0); // Level at 0
    IndicatorSetInteger(INDICATOR_LEVELS, 1);         // Number of levels
    IndicatorSetInteger(INDICATOR_LEVELCOLOR, clrGray); // Level color
    
    // Initialize buffers to 0
    ArrayInitialize(HH_Buffer, ZERO_VALUE);
    ArrayInitialize(LL_Buffer, ZERO_VALUE);
    ArrayInitialize(EmptyPlaces_Buffer, ZERO_VALUE);
    ArrayInitialize(CandleNum_Buffer, ZERO_VALUE);

    return(INIT_SUCCEEDED);
}

//+------------------------------------------------------------------+
//| Custom indicator calculation function                            |
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
    //--- Ensure rates_total is valid
    if (rates_total <= 0)
        return(0);
    
    // Determine the starting point based on the selected mode
    if (Mode == RecentCandlesMode)
    {

        // Start from the last 'RecentCandles'
        start = MathMax(rates_total - RecentCandles, prev_calculated > 0 ? prev_calculated - 1 : 0);

        // Clear data outside the range of RecentCandles
        for (int i = 0; i < rates_total - RecentCandles; i++)
        {
            HH_Buffer[i] = ZERO_VALUE;
            LL_Buffer[i] = ZERO_VALUE;
        }
    }
    else if (Mode == FromDateMode)
    {
        // Debug: Print the FromDate value
        // Print("FromDate: ", TimeToString(FromDate, TIME_DATE | TIME_MINUTES), prev_calculated);
        
        // Find the index of the first candle after the specified date
        for (int i = prev_calculated; i < rates_total; i++)
        {
            // Debug: Print the time of each candle
            // Print("Candle Time: ", TimeToString(time[i], TIME_DATE | TIME_MINUTES));

            if (time[i] >= FromDate)
            {
                start = i;
                //Debug: Print the start index and time
                Print("Start index found at: ", start, " Time: ", TimeToString(time[i], TIME_DATE | TIME_MINUTES));
                break;
            }
        }

        // If no valid start index is found, set start to rates_total to avoid processing
        if (start == -1)
        {
            Print("No valid start index found. Setting start to rates_total.");
            start = rates_total;
        }
        
        // Clear data before the specified date
        for (int i = 0; i < start; i++)
        {
            HH_Buffer[i] = ZERO_VALUE;
            LL_Buffer[i] = ZERO_VALUE;
        }
    }

//Print("Rates total: ", rates_total);
    for (int i = start; i < rates_total - 2; i++) // Ensure enough data for i+1 and i+2
    {
        // Get the high and low of the last two completed candles
        double high1 = high[i + 1];
        double low1 = low[i + 1];
        double high2 = high[i + 2];
        double low2 = low[i + 2];

        candleNum += 1; // Increment the candle number
        CandleNum_Buffer[i+2] = candleNum; // Store the candle number in the buffer
        
        // Check for Higher High and Higher Low
        if (high1 < high2 && low1 < low2)
        {
            double pipDifference = (high2 - high1) / (_Point * 10);
            HH_Buffer[i+2] = pipDifference;
            LL_Buffer[i+2] = ZERO_VALUE; // No value for LL in this case
            //HH_LL_Buffer[i+2] = pipDifference;
        }
        // Check for Lower Low and Lower High
        else if (low1 > low2 && high1 > high2)
        {
            double pipDifference = (low1 - low2) / (_Point * 10);
            LL_Buffer[i+2] = pipDifference * (-1);
            HH_Buffer[i+2] = ZERO_VALUE; // No value for HH in this case
            //HH_LL_Buffer[i+2] = pipDifference;
        }
        else
        {
            // No valid formation
            HH_Buffer[i+2] = 0;
            LL_Buffer[i+2] = 0;
            countEmptyPlaces += 1;
        }
        EmptyPlaces_Buffer[i+2] = countEmptyPlaces; // Store the count of empty places in the buffer

    }

    return(rates_total);
}

//+------------------------------------------------------------------+
//| Custom indicator deinitialization function                       |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
{
    // Reset all buffers to EMPTY_VALUE
    ArrayInitialize(HH_Buffer, EMPTY_VALUE);
    ArrayInitialize(LL_Buffer, EMPTY_VALUE);
    ArrayInitialize(EmptyPlaces_Buffer, EMPTY_VALUE);
    ArrayInitialize(CandleNum_Buffer, EMPTY_VALUE);

    // Reset all variables
    start = 0;
    countEmptyPlaces = 0;
    candleNum = 0;

    // Debug: Print deinitialization reason
    Print("Indicator deinitialized. Reason: ", reason);
}