//+------------------------------------------------------------------+
//|                                                 TradeHelpers.mqh |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#ifndef TRADE_HELPERS_MQH
#define TRADE_HELPERS_MQH

#property copyright "Copyright 2025, bill"
#property link      "bill"

#include <Trade/Trade.mqh>

 // Function to count the number of open orders
 int OpenOrders()
 {
      int openOrders = OrdersTotal();
      // Print("Number of open orders: ", openOrders);
      return openOrders;
 }
 // Function to count the number of open orders for the current chart symbol
 int OpenOrdersByChartSymbol()
 {
      string symbol = _Symbol;
      int count = 0;
      int total = OrdersTotal();
      for(int i = 0; i < total; i++) {
         if(OrderGetTicket(i) > 0) {
            if(OrderGetString(ORDER_SYMBOL) == _Symbol)
               count++;
         }
      }
      return count;
 }
//+------------------------------------------------------------------+
//| Returns the number of buy or sell positions for the current symbol
//| position_type: POSITION_TYPE_BUY or POSITION_TYPE_SELL
//+------------------------------------------------------------------+
int CountPositionsByType(ENUM_POSITION_TYPE position_type)
{
    int count = 0;
    int total = PositionsTotal();
    for(int i = 0; i < total; i++)
    {
        ulong ticket = PositionGetTicket(i);
        if(PositionSelectByTicket(ticket))
        {
            if(PositionGetString(POSITION_SYMBOL) == _Symbol &&
               PositionGetInteger(POSITION_TYPE) == position_type)
            {
                count++;
            }
        }
    }
    return count;
}

 // Function to count the number of open trades
 int OpenPositions()
 {
     int openTrades = PositionsTotal();
     // Print("Number of open trades: ", openTrades);
     return openTrades;
 }
  // Function to count and print the number of open trades for the current chart symbol
 int OpenPositionsByChartSymbol()
 {
    string symbol = _Symbol;
    int count = 0;
    int total = PositionsTotal();
    for(int i = 0; i < total; i++)
    {
        ulong ticket = PositionGetTicket(i);
        if(PositionSelectByTicket(ticket))
        {
           if(PositionGetString(POSITION_SYMBOL) == symbol)
              count++;
        }
    }
    // Print("Number of open trades for symbol ", symbol, ": ", count);
    return count;
 }
 //+------------------------------------------------------------------+
//| Returns the number of open orders of a specific type for _Symbol |
//| order_type: ORDER_TYPE_BUY, ORDER_TYPE_SELL, etc.                |
//+------------------------------------------------------------------+
int CountOpenOrdersByType(int order_type)
{
    int count = 0;
    int total = OrdersTotal();
    for(int i = 0; i < total; i++)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == _Symbol &&
           OrderGetInteger(ORDER_TYPE) == order_type)
        {
            count++;
        }
    }
    return count;
}
 
// Place a Buy Stop order
bool PlaceBuyStop(CTrade &trade, double lot, double price, string symbol, double sl, double tp, string comment = NULL)
{
    return trade.BuyStop(lot, price, symbol, sl, tp, NULL);
}

// Place a Sell Stop order
bool PlaceSellStop(CTrade &trade, double lot, double price, string symbol, double sl, double tp, string comment = NULL)
{
    return trade.SellStop(lot, price, symbol, sl, tp, NULL);
}

// Place a Buy Limit order
bool PlaceBuyLimit(CTrade &trade, double lot, double price, string symbol, double sl, double tp, string comment = NULL)
{
    return trade.BuyLimit(lot, price, symbol, sl, tp, NULL);
}

// Place a Sell Limit order
bool PlaceSellLimit(CTrade &trade, double lot, double price, string symbol, double sl, double tp, string comment = NULL)
{
    return trade.SellLimit(lot, price, symbol, sl, tp, NULL);
}

// Cancel all pending orders of a given type for a symbol
void CancelPendingOrders(CTrade &trade, int order_type, string symbol, bool debugging = false)
{
    for(int i=OrdersTotal()-1; i>=0; i--)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == symbol &&
           OrderGetInteger(ORDER_TYPE) == order_type)
        {
            if(!trade.OrderDelete(ticket))
            {
                if(debugging) Print("Failed to delete order: ", ticket, " - ", trade.ResultRetcodeDescription());
            }
            else
            {
                if(debugging) Print("Deleted order: ", ticket);
            }
        }
    }
}
// Cancel all pending orders of a given symbol
void CancelPendingOrders(CTrade &trade, string symbol, bool debugging = false)
{
    if(debugging) Print("OrdersTotal(): ", OrdersTotal());
    for(int i=OrdersTotal()-1; i>=0; i--)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == symbol)
        {
            if(!trade.OrderDelete(ticket))
            {
                if(debugging) Print("Failed to delete order: ", ticket, " - ", trade.ResultRetcodeDescription());
            }
            else
            {
                if(debugging) Print("Deleted order: ", ticket);
            }
        }
    }
}

// Returns true if there is any pending BUY STOP or SELL STOP order for the current symbol
bool HasPendingStopOrder(string symbol)
{
    for(int i=OrdersTotal()-1; i>=0; i--)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == symbol &&
           (OrderGetInteger(ORDER_TYPE) == ORDER_TYPE_BUY_STOP || OrderGetInteger(ORDER_TYPE) == ORDER_TYPE_SELL_STOP))
        {
            return true;
        }
    }
    return false;
}

//+------------------------------------------------------------------+
//| Returns the number of pending stop orders of a specific type     |
//| order_type: ORDER_TYPE_BUY_STOP or ORDER_TYPE_SELL_STOP          |
//+------------------------------------------------------------------+
int CountPendingStopOrderByType(int order_type)
{
    int count = 0;
    for(int i = OrdersTotal() - 1; i >= 0; i--)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 &&
           OrderGetString(ORDER_SYMBOL) == _Symbol &&
           OrderGetInteger(ORDER_TYPE) == order_type)
        {
            count++;
        }
    }
    return count;
}
#endif 