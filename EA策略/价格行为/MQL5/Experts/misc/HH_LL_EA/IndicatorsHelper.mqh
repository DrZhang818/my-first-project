#ifndef INDICATORS_HELPERS_MQH
#define INDICATORS_HELPERS_MQH

//--- Indicator handles
int handle;                   // Handle for 'TI_HL_Diff' indicator
int sma_handle;               // Handle for 'SizeInPips' indicator

//--- Buffers to store indicator data
double HH_Buffer[];           // Higher High differences
double LL_Buffer[];           // Lower Low differences
double EmptyPlaces_Buffer[];  // Empty places count
double CandleNum_Buffer[];    // Candle numbers
int startPositionOfBuffer = 1; // Start position for the buffer
int numElemToCopyBuffer = 1; // Number of elements to copy from the buffer

// Copy buffer data from an indicator
bool GetIndicatorBuffer(int handle, int buffer_num, int start_pos, int count, double &buffer[])
{
    return (CopyBuffer(handle, buffer_num, start_pos, count, buffer) > 0);
}

// Calculate dynamic TP/SL using SizeInPips indicator
bool CalculateDynamicTPSL(string symbol, ENUM_TIMEFRAMES tf, int period, double tp_mul, double sl_mul, double &tp, double &sl, bool debugging = false)
{
    /*int sma_handle = iCustom(symbol, tf, "..\\Indicators\\misc\\SizeInPips", period);
    if(sma_handle == INVALID_HANDLE)
    {
        if(debugging) Print("Failed to load SizeInPips indicator.");
        return false;
    }*/
    double SMABuffer[1];
    if(CopyBuffer(sma_handle, 0, 1, 1, SMABuffer) <= 0)
    {
        if(debugging) Print("Failed to retrieve data from SizeInPips indicator.");
        IndicatorRelease(sma_handle);
        return false;
    }
    tp = tp_mul * SMABuffer[0];
    sl = sl_mul * SMABuffer[0];
    //IndicatorRelease(sma_handle);
    return true;
}

//+------------------------------------------------------------------+
//| Custom function to process 'TI_HL_Diff' indicator data           |
//+------------------------------------------------------------------+
void ProcessTI_HL_DiffIndicatorData()
{
   /*
   //--- Load the SizeInPips indicator
   handle = iCustom(Symbol(), inputTimeframe, "..\\Indicators\\misc\\TI_HL_Diff", Mode, FromDate, RecentCandles);

    // Check if the indicator was loaded successfully
    if (handle == INVALID_HANDLE)
    {
        if(debugging) Print("Failed to load TI_HL_Diff indicator.");
        return;
    }
    
    if(debugging) Print("TI_HL_Diff indicator loaded successfully.");
    */
    // Retrieve data for the latest candle from the indicator
    if (CopyBuffer(handle, 0, startPositionOfBuffer, numElemToCopyBuffer, HH_Buffer) <= 0 ||
        CopyBuffer(handle, 1, startPositionOfBuffer, numElemToCopyBuffer, LL_Buffer) <= 0 ||
        CopyBuffer(handle, 2, startPositionOfBuffer, numElemToCopyBuffer, EmptyPlaces_Buffer) <= 0 ||
        CopyBuffer(handle, 3, startPositionOfBuffer, numElemToCopyBuffer, CandleNum_Buffer) <= 0)
    {
        DBG_PRINT("Failed to retrieve data from TI_HL_Diff indicator.", debugging);
        //IndicatorRelease(handle);
        return;
    }
    
    //--- Release the indicator handle
    IndicatorRelease(handle);

}
//+------------------------------------------------------------------+
//| Custom function to process 'SizeInPips' indicator data           |
//+------------------------------------------------------------------+
void ProcessSizeInPipsIndicatorData()
{
    // Create a handle for the SizeInPips indicator
    //sma_handle = iCustom(Symbol(), inputTimeframe, "..\\Indicators\\misc\\SizeInPips", atr_val);

    if (sma_handle == INVALID_HANDLE)
    {
        if(debugging) Print("Failed to load SizeInPips indicator.");
        return;
    }

    double SMABuffer[1]; // Buffer to hold at least 1 values

    // Copy the last two values from the indicator buffer (buffer 0)
    if (CopyBuffer(sma_handle, 0, 1, 1, SMABuffer) <= 0)
    {
        if(debugging) Print("Failed to retrieve data from SizeInPips indicator.");
        //IndicatorRelease(sma_handle);
        return;
    }

    // Calculate new TP and SL based on SMABuffer[1]
    dynamic_tp_pips = dyn_tp_mul * SMABuffer[0];
    dynamic_sl_pips = dyn_sl_mul * SMABuffer[0];

    //PrintFormat("Updated TP = %.2f, SL = %.2f (from SizeInPips: %.2f)", dynamic_tp_pips, dynamic_sl_pips, SMABuffer[0]);
    if(debugging) Print("Updated TP = ", dynamic_tp_pips, ", SL = ", dynamic_sl_pips, " (SMABuffer[0]: ", SMABuffer[0], ")");

    //--- Release the indicator handle
    IndicatorRelease(sma_handle);

    // You can now use new_tp and new_sl for further trade logic as needed
}

#endif 