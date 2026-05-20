//+------------------------------------------------------------------+
//|                                                   TimeHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Helper: get the end of the current day in server time            |
//+------------------------------------------------------------------+
datetime GetEndOfDayExpiration()
{
    datetime now = TimeCurrent();
    MqlDateTime dt;
    TimeToStruct(now, dt);
   //  dt.hour = 23;
   //  dt.min = 00;
   //  dt.sec = 59;
    return StructToTime(dt);
}

//+------------------------------------------------------------------+
//| Helper: Check if current time is within active hours             |
//+------------------------------------------------------------------+
bool IsWithinActiveHours()
{
   MqlDateTime dt;
   TimeToStruct(TimeCurrent(), dt);

   int startHour = EnumHourToInt(ActiveHourStart);
   int startMin  = EnumMinuteToInt(ActiveMinuteStart);
   int endHour   = EnumHourToInt(ActiveHourEnd);
   int endMin    = EnumMinuteToInt(ActiveMinuteEnd);

   int nowHM = dt.hour * 60 + dt.min;
   int startHM = startHour * 60 + startMin;
   int endHM = endHour * 60 + endMin;

   if(startHM < endHM)
      return (nowHM >= startHM && nowHM < endHM);
   else // Overnight window (e.g., 22:00 to 06:00)
      return (nowHM >= startHM || nowHM < endHM);
}

//+------------------------------------------------------------------+
//| Helper: Convert enum to int hour/minute                          |
//+------------------------------------------------------------------+
int EnumHourToInt(HourEnum h) {
   return (int)h;
}

int EnumMinuteToInt(MinuteEnum m) {
   return (int)m * 5; 
}
