#ifndef PROCESS_NEW_CANDLE_MQH
#define PROCESS_NEW_CANDLE_MQH
//+------------------------------------------------------------------+
//| Function to retrieve and process indicator data for new candles  |
//+------------------------------------------------------------------+
void ProcessNewCandle()
{
    if(inputTimeframe == PERIOD_D1)
      {
         #include "DiffLogic\Daily\NewDailyCandle.mqh"
      }
    else
      {
         #include "DiffLogic\Generic\OnNewCandle.mqh"
      }
}

// Returns true if there is a pending stop order placed in the current candle
bool HasPendingStopOrderInCurrentCandle(string symbol, ENUM_TIMEFRAMES tf)
{
    datetime currentCandleOpen = iTime(symbol, tf, 0);

    for(int i = OrdersTotal() - 1; i >= 0; i--)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == symbol &&
           (OrderGetInteger(ORDER_TYPE) == ORDER_TYPE_BUY_STOP || OrderGetInteger(ORDER_TYPE) == ORDER_TYPE_SELL_STOP))
        {
            datetime orderTime = (datetime)OrderGetInteger(ORDER_TIME_SETUP);
            if(orderTime >= currentCandleOpen)
                return true; // Order placed in current candle
        }
    }
    return false; // No such order found
}

#endif 