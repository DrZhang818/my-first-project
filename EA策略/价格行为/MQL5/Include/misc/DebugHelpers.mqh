//+------------------------------------------------------------------+
//|                                                 DebugHelpers.mqh |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#ifndef DEBUG_HELPERS_MQH
#define DEBUG_HELPERS_MQH

#property copyright "Copyright 2025, bill"
#property link      "bill"

void DBG_PRINT(string msg, bool debugging)
{
    if(debugging) Print(msg);
}

#endif 