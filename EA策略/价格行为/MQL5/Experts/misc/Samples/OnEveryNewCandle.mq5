//+------------------------------------------------------------------+
//|                                             OnEveryNewCandle.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "1.00"

//--- input parameters
input ENUM_TIMEFRAMES inputTimeframe = PERIOD_H4; // Chart Period

input string   InputText="New Candle!";

//--- Global variable to track the last processed candle
datetime lastCandleTime = 0;

//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- create timer
   EventSetTimer(1);
   
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//--- destroy timer
   EventKillTimer();
   
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
        PrintFormat("New Candle Formed: Time = %s", TimeToString(currentCandleTime, TIME_DATE | TIME_MINUTES));

        // Update the last processed candle time
        lastCandleTime = currentCandleTime;

        // Retrieve and process indicator data for the new candle
        ProcessNewCandleData();
    }   
  }
  
//+------------------------------------------------------------------+
//| Function to retrieve and process indicator data for new candles  |
//+------------------------------------------------------------------+
void ProcessNewCandleData()
{
    Print("New Candle Data Goes Here...");
}
//+------------------------------------------------------------------+
