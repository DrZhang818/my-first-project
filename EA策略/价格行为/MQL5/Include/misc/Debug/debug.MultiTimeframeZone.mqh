//+------------------------------------------------------------------+
//|   debug.MultiTimeframeZone.mqh                                   |
//|   Logging and formatting helpers for MultiTimeframeZone EA       |
//+------------------------------------------------------------------+
#ifndef DEBUG_MULTITIMEFRAMEZONE_MQH
#define DEBUG_MULTITIMEFRAMEZONE_MQH

int GetPriceDigits()
  {
   return (int)SymbolInfoInteger(_Symbol, SYMBOL_DIGITS);
  }

string FormatPrice(const double price)
  {
   int digits = GetPriceDigits();
   return DoubleToString(price, digits);
  }

string FormatTime(const datetime t)
  {
   return TimeToString(t, TIME_DATE|TIME_MINUTES);
  }

void LogEvent(const string eventText)
  {
   if(InpEnableEventLog)
      Print("[EVENT] ", eventText);
  }

void LogEventZone(const string prefix, const double high, const double low)
  {
   if(InpEnableEventLog)
      Print("[EVENT] ", prefix, ". High: ", FormatPrice(high), " | Low: ", FormatPrice(low));
  }

void LogEventPattern(const string prefix, const double high, const double low, const datetime t)
  {
   if(InpEnableEventLog)
      Print("[EVENT] ", prefix, ". High: ", FormatPrice(high), " | Low: ", FormatPrice(low), " | Time: ", FormatTime(t));
  }

void LogEventTrade(const string prefix, const double entry, const double sl, const double tp)
  {
   if(InpEnableEventLog)
      Print("[EVENT] ", prefix, ". Entry: ", FormatPrice(entry), " | SL: ", FormatPrice(sl), " | TP: ", FormatPrice(tp));
  }

#endif // DEBUG_MULTITIMEFRAMEZONE_MQH
