// Global variables
datetime lastCandleTime = 0; // Tracks the last candle's opening time
uint tickCount = 0;          // Tracks the number of ticks in the current candle
int indicatorHandle = -1;    // Handle for the custom indicator

double tickCountBuffer[];

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
{
   // Initialize the global variable for tick count
   GlobalVariableSet("TickCount", tickCount);

   // Create a handle for the custom indicator
   indicatorHandle = iCustom(_Symbol, _Period, "misc/CustomTickVolume/CustomTickVolume");

   // Check if the handle is valid
   if (indicatorHandle == INVALID_HANDLE)
   {
      Print("Failed to create handle for CustomTickVolume indicator");
      return(INIT_FAILED);
   }

   return(INIT_SUCCEEDED);
}

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
{
   // Get the opening time of the current candle
   datetime currentCandleTime = iTime(_Symbol, _Period, 0);

   // Check if a new candle has started
   if(currentCandleTime != lastCandleTime)
   {
      // Print the tick count for the previous candle
      if(lastCandleTime != 0) // Skip the first initialization
        CustomTickVolumeCall();

      // Reset the tick counter for the new candle
      tickCount = 0;
      lastCandleTime = currentCandleTime;
   }

   // Increment the tick counter for the current candle
   tickCount++;
}

//+------------------------------------------------------------------+
//| Function to call the custom indicator                            |
//+------------------------------------------------------------------+
void CustomTickVolumeCall()
{
    GlobalVariableSet("TickCount", tickCount);
    // Update the custom indicator by passing the tick count
    if (indicatorHandle != INVALID_HANDLE)
    {
        //indicatorHandle = iCustom(_Symbol, _Period, "misc/CustomTickVolume/CustomTickVolume");
        CopyBuffer(indicatorHandle, 0, 0, 1, tickCountBuffer);
        //IndicatorRelease(indicatorHandle);
    }
    else
    {
        Print("Invalid indicator handle");
    }
    //tickCountBuffer[0] = tickCount; // Store the tick count in the buffer
    // Print("Tick Count for the last candle: ", tickCountBuffer[0]);
    // Print("Current Tick Count: ", tickCount);
}

//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
{
   // Release the custom indicator handle
   if (indicatorHandle != INVALID_HANDLE)
   {
      IndicatorRelease(indicatorHandle);
   }
}
