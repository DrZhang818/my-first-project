//+------------------------------------------------------------------+
//|                                           D-Break-S4.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property copyright "Copyright 2025"
#property version   "1.00"
#include <Trade\Trade.mqh>
CTrade trade;

//+------------------------------------------------------------------+
//| v1.05: User Inputs for Time Filter                               |
//+------------------------------------------------------------------+
enum HourEnum
{
   H00, H01, H02, H03, H04, H05, H06, H07, H08, H09, H10, H11,
   H12, H13, H14, H15, H16, H17, H18, H19, H20, H21, H22, H23
};
enum MinuteEnum
{
   M00, M05, M10, M15, M20, M25, M30, M35, M40, M45, M50, M55
};
enum SLTPMethod { CandleSize, ATR };
enum ExpireAt { Never, EndOFDay, EndOfCandle, _24Hours };

//--- Inputs
input ENUM_TIMEFRAMES InpTimeframe = PERIOD_D1;
input string InpSymbols = "";                     // Currency pairs, e.g. "EURUSD,GBPUSD,USDJPY"

sinput string gap4;                               // 👉
input HourEnum ActiveHourStart = H04;             // 🕒 Start Hour
input MinuteEnum ActiveMinuteStart = M00;         // 🕗 Start Minute
input HourEnum ActiveHourEnd = H21;               // 🕒 End Hour
input MinuteEnum ActiveMinuteEnd = M00;           // 🕗 End Minute

// input string InpActiveStart = "04:00";
// input string InpActiveEnd   = "17:00";
input double Lots = 0.01;                 // Lot size for orders
sinput bool debugging = true;             // Debugging ON?
input int OffsetPips = 4;                 // Offset in pips for pending orders

input SLTPMethod SL_Method = CandleSize;  // SL Method:
input SLTPMethod TP_Method = CandleSize;  // TP Method:

input int ATRPeriod = 14;                 // ATR period for ATR calculation
input double SlPercentOfCandle = 1.0;     // SL in % of candle size
input double TpPercentOfCandle = 2.0;     // TP in % of candle size

input ExpireAt OrdersExpireAt = EndOFDay;   // Orders Expire At

//--- Globals
datetime lastProcessedBarTime[10];        // up to 10 symbols

//--- Helper: calculate ATR for the selected symbol/timeframe/period:
double GetATR(const string symbol, ENUM_TIMEFRAMES tf, int period)
{
   int handle = iATR(symbol, tf, period);
   if(handle == INVALID_HANDLE) return 0.0;
   double atr[];
   if(CopyBuffer(handle, 0, 1, 1, atr) != 1) {
      IndicatorRelease(handle);
      return 0.0;
   }
   IndicatorRelease(handle);
   return atr[0];
}

//--- Helper: Split comma separated symbols
int SplitSymbols(const string symbols, string &arr[])
{
  int count = 0;
  string temp[];
  StringSplit(symbols, ',', temp);
  for(int i=0; i<ArraySize(temp); i++)
  {
    string s = temp[i];
    StringTrimLeft(s);
    StringTrimRight(s);
    if(s != "") { ArrayResize(arr, count+1); arr[count++] = s; }
  }
  return count;
}

//--- Helper: Check if time is within active window
bool IsActiveTime()
{
   MqlDateTime tm;
   TimeToStruct(TimeCurrent(), tm);
   int now = tm.hour*60 + tm.min;
   // int start = StringToInteger(StringSubstr(InpActiveStart,0,2))*60 + StringToInteger(StringSubstr(InpActiveStart,3,2));
   // int end   = StringToInteger(StringSubstr(InpActiveEnd,0,2))*60 + StringToInteger(StringSubstr(InpActiveEnd,3,2));
   int start = EnumHourToInt(ActiveHourStart) * 60 + EnumMinuteToInt(ActiveMinuteStart);
   int end   = EnumHourToInt(ActiveHourEnd) * 60 + EnumMinuteToInt(ActiveMinuteEnd);
   
   return (now >= start && now <= end);
}

//--- Helper: Convert enum to int hour/minute
int EnumHourToInt(HourEnum h)   { return (int)h; }
int EnumMinuteToInt(MinuteEnum m) { return (int)m * 5; }

//--- Helper: Returns today's last minute (23:59) as datetime
datetime EndOfDayExpiration()
{
   MqlDateTime dt;
   TimeToStruct(TimeCurrent(), dt);
   dt.hour = 23;
   dt.min  = 59;
   dt.sec  = 0;
   return StructToTime(dt);
}

//--- Helper: Calculate expiration time for the next candle
datetime NextDayCandleExpiration(const string symbol, ENUM_TIMEFRAMES tf)
{
   MqlRates rates[1];
   if(CopyRates(symbol, tf, 0, 1, rates) != 1)
      return TimeCurrent() + 3600; // fallback: 1 hour from now
   int tf_sec = PeriodSeconds(tf);
   // return rates[0].time + tf_sec;

   datetime nextBarTime = rates[0].time + tf_sec;
   
  // Parse InpActiveStart
  //  int startHour = StringToInteger(StringSubstr(InpActiveStart,0,2));
  //  int startMin  = StringToInteger(StringSubstr(InpActiveStart,3,2));
  int startHour = ActiveHourStart;
  int startMin = ActiveMinuteStart;

   MqlDateTime dt;
   TimeToStruct(nextBarTime, dt);
   dt.hour = startHour;
   dt.min  = startMin;
   dt.sec  = 0;
   return StructToTime(dt);
}

//--- Helper: Calculate expiration time for the next candle (1 minute before close of tf candle)
datetime NextCandleExpiration(const string symbol, ENUM_TIMEFRAMES tf)
{
   MqlRates rates[1];
   if(CopyRates(symbol, tf, 0, 1, rates) != 1)
      return TimeCurrent() + 3600; // fallback: 1 hour from now
   int tf_sec = PeriodSeconds(tf);
   datetime nextBarClose = rates[0].time + tf_sec;
   return nextBarClose - 60; // 1 minute before close
}

//+------------------------------------------------------------------+
//| Expert tick function                                             |
//+------------------------------------------------------------------+
//--- Main logic
void OnTick() {

  if(!IsActiveTime()) return;

  string symbols[50];
  int symbolCount = 0;
  if(InpSymbols == "")
  {
    symbols[0] = _Symbol;
    symbolCount = 1;
  }
  else
  {
    symbolCount = SplitSymbols(InpSymbols, symbols);
  }

  for(int s=0; s<symbolCount; s++)
  {
    string sym = symbols[s];
    if(!SymbolSelect(sym, true)) continue;

    // Get last 2 closed candles on selected timeframe
    MqlRates rates[3];
    if(CopyRates(sym, InpTimeframe, 1, 2, rates) != 2) continue;

    datetime barTime = rates[1].time;
    if(lastProcessedBarTime[s] == barTime) continue; // already processed
    lastProcessedBarTime[s] = barTime;

    double pip = SymbolInfoDouble(sym, SYMBOL_POINT) * (SymbolInfoInteger(sym, SYMBOL_DIGITS) == 3 || SymbolInfoInteger(sym, SYMBOL_DIGITS) == 5 ? 10 : 1);
    double prevCandleSize = MathAbs(rates[1].high - rates[1].low) / pip;
    double atrPips = GetATR(sym, InpTimeframe, ATRPeriod) / pip;

    if(debugging) Print("Symbol: ", sym, " ATR: ", atrPips, " Candle Size: ", prevCandleSize, " Pip: ", pip);
    
    // --- SL/TP calculation logic
    double sl_size = (SL_Method == CandleSize) ? prevCandleSize * SlPercentOfCandle * pip : SlPercentOfCandle * atrPips * pip;
    double tp_size = (TP_Method == CandleSize) ? prevCandleSize * TpPercentOfCandle * pip : TpPercentOfCandle * atrPips * pip;

    datetime expiration;
    
    if(OrdersExpireAt == Never)
      expiration = 0; // No expiration
    else if(OrdersExpireAt == EndOFDay)
      expiration = EndOfDayExpiration();
    else if(OrdersExpireAt == EndOfCandle)
      expiration = NextCandleExpiration(sym, InpTimeframe);
    else if(OrdersExpireAt == _24Hours)
      expiration = NextDayCandleExpiration(sym, InpTimeframe);
    else // Default to EndOfCandle
      expiration = EndOfDayExpiration();

    // Bullish
    if(rates[1].close > rates[1].open)
    {
        double buyStopPrice  = rates[1].close + OffsetPips * pip;
        double buyStopSL     = buyStopPrice - sl_size;
        double buyStopTP     = buyStopPrice + tp_size;
        double sellLimitPrice= rates[1].high + OffsetPips * pip;
        double sellLimitSL   = sellLimitPrice + sl_size;
        double sellLimitTP   = sellLimitPrice - tp_size;

        trade.BuyStop(Lots, buyStopPrice, sym, buyStopSL, buyStopTP, ORDER_TIME_SPECIFIED, expiration);
        trade.SellLimit(Lots, sellLimitPrice, sym, sellLimitSL, sellLimitTP, ORDER_TIME_SPECIFIED, expiration);
    }
    // Bearish
    else if(rates[1].close < rates[1].open)
    {
        double sellStopPrice = rates[1].close - OffsetPips * pip;
        double sellStopSL    = sellStopPrice + sl_size;
        double sellStopTP    = sellStopPrice - tp_size;
        double buyLimitPrice = rates[1].low - OffsetPips * pip;
        double buyLimitSL    = buyLimitPrice - sl_size;
        double buyLimitTP    = buyLimitPrice + tp_size;

        trade.SellStop(Lots, sellStopPrice, sym, sellStopSL, sellStopTP, ORDER_TIME_SPECIFIED, expiration);
        trade.BuyLimit(Lots, buyLimitPrice, sym, buyLimitSL, buyLimitTP, ORDER_TIME_SPECIFIED, expiration);
    }
    if(debugging) Print("Expiration for ", sym, ": ", TimeToString(expiration, TIME_DATE|TIME_SECONDS), 
    " Now: ", TimeToString(TimeCurrent(), TIME_DATE|TIME_SECONDS));
  }
}
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- create timer
   EventSetTimer(60);
   
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
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer()
  {
//---
   
  }
//+------------------------------------------------------------------+
//| Trade function                                                   |
//+------------------------------------------------------------------+
void OnTrade()
  {
//---
   
  }
//+------------------------------------------------------------------+
//| TradeTransaction function                                        |
//+------------------------------------------------------------------+
void OnTradeTransaction(const MqlTradeTransaction& trans,
                        const MqlTradeRequest& request,
                        const MqlTradeResult& result)
  {
//---
   
  }
//+------------------------------------------------------------------+
//| Tester function                                                  |
//+------------------------------------------------------------------+
double OnTester()
  {
//---
   double ret=0.0;
//---

//---
   return(ret);
  }
//+------------------------------------------------------------------+
//| TesterInit function                                              |
//+------------------------------------------------------------------+
void OnTesterInit()
  {
//---
   
  }
//+------------------------------------------------------------------+
//| TesterPass function                                              |
//+------------------------------------------------------------------+
void OnTesterPass()
  {
//---
   
  }
//+------------------------------------------------------------------+
//| TesterDeinit function                                            |
//+------------------------------------------------------------------+
void OnTesterDeinit()
  {
//---
   
  }
//+------------------------------------------------------------------+
//| ChartEvent function                                              |
//+------------------------------------------------------------------+
void OnChartEvent(const int id,
                  const long &lparam,
                  const double &dparam,
                  const string &sparam)
  {
//---
   
  }
//+------------------------------------------------------------------+
//| BookEvent function                                               |
//+------------------------------------------------------------------+
void OnBookEvent(const string &symbol)
  {
//---
   
  }
//+------------------------------------------------------------------+
