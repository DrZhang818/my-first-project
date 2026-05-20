//+------------------------------------------------------------------+
//|                   DayOfWeek.mqh                                  |
//|   Returns the current day of week as a string (e.g., "Monday")   |
//+------------------------------------------------------------------+

//--- Include the Time library for date and time functions
#include <Tools/DateTime.mqh>

// Returns the current day of week as a string (e.g., "Monday")
string CurrentDayOfWeek()
{
    // Get current server time
    datetime now = TimeCurrent();

    // Create a CDateTime object and initialize it with the current time
    CDateTime dt;
    dt.DateTime(now);
        
    //--- Print day of week (full and short)
    // Print("Day of week: ", dt.DayName(), " (Day number: ", dt.day_of_week, ")");

    return dt.DayName(); // Return the full name of the day of the week
}
