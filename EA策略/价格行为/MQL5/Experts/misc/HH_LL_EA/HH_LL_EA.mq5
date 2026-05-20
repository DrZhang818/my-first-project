//+------------------------------------------------------------------+
//|                                             HH LL EA.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#include <misc/TradeHelpers.mqh>
#include <misc/DebugHelpers.mqh>
#include "IndicatorsHelper.mqh"
#include "InputParamsHelper.mqh"
#include "ProcessNewCandle.mqh"

//--- Create a global trade object
CTrade trade;

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
{
//--- Initialize indicator handlers
   sma_handle = iCustom(Symbol(), inputTimeframe, "..\\Indicators\\misc\\SizeInPips", atr_val);
   if(sma_handle == INVALID_HANDLE)
   {
      if(debugging) Print("Failed to load SizeInPips indicator.");
      return false;
   }
// Load the SizeInPips indicator
   handle = iCustom(Symbol(), inputTimeframe, "..\\Indicators\\misc\\TI_HL_Diff", Mode, FromDate, RecentCandles);

    // Check if the indicator was loaded successfully
    if (handle == INVALID_HANDLE)
    {
        if(debugging) Print("Failed to load TI_HL_Diff indicator.");
        return 0;
    }
    
    if(debugging) Print("TI_HL_Diff indicator loaded successfully.");
//--- create timer
   EventSetTimer(1);
   //---
   /*
   ArrayResize(HH_Buffer, 150);         // Ensure the buffer has at least 150 elements//---
   ArrayFill(HH_Buffer, 0, 150, 0.0);   // Fill first 150 elements with 0.0
   ArrayResize(LL_Buffer, 150);         // Ensure the buffer has at least 150 elements
   ArrayFill(LL_Buffer, 0, 150, 0.0);   // Fill first 150 elements with 0.0
   */
//---
   return(INIT_SUCCEEDED);
}
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
      // Release the indicator handle
      if (handle != INVALID_HANDLE)
      {
         IndicatorRelease(handle);
         if(debugging) Print("TI_HL_Diff indicator released.");
      }
      //--- destroy timer
      EventKillTimer();
      
      // Release the indicator handles
      IndicatorRelease(handle);
      IndicatorRelease(sma_handle);

  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
void OnTick()
  {
//---

  }
//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer()
{
    // Get the time of the current candle
    datetime currentCandleTime = iTime(Symbol(), inputTimeframe, 0);

    // Check if a new candle has formed
    if (currentCandleTime != lastCandleTime)
    {
        // A new candle is formed
        if(debugging) PrintFormat("New Candle Formed: Time = %s", TimeToString(currentCandleTime, TIME_DATE | TIME_MINUTES));
        
        // Update the last processed candle time
        lastCandleTime = currentCandleTime;

        // Retrieve and process indicator data for the new candle
        ProcessNewCandle();
    }    
}
//+------------------------------------------------------------------+
