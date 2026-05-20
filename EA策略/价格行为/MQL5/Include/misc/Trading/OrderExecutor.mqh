/**
 * @file OrderExecutor.mqh
 * @brief Wraps the CTrade interface with additional safety checks and logging.
 */

#ifndef __THIVYAM_ORDER_EXECUTOR_MQH__
#define __THIVYAM_ORDER_EXECUTOR_MQH__

#include <Trade\Trade.mqh>

/**
 * Performs limit-order placement with margin checks and logging.
 */
class COrderExecutor : public CObject
  {
private:
   CTrade            m_trade;
   string            m_symbol;

public:
                     COrderExecutor()
     {
      m_symbol = _Symbol;
     }

   /**
    * Sets the trading symbol and expert magic number.
    * @param symbol Trading symbol.
    * @param magic Expert advisor magic number.
    */
   void              Configure(const string symbol, const ulong magic)
     {
      m_symbol = symbol;
      m_trade.SetExpertMagicNumber((uint)magic);
     }

   /**
    * Places a pending limit order with safety checks.
    * @param isBuy True for buy limit, false for sell limit.
    * @param entryPrice Desired entry price.
    * @param stopLoss Stop-loss price.
    * @param takeProfit Take-profit price.
    * @param lots Position size.
    * @param comment Trade comment for journal visibility.
    * @param[out] ticket Resulting order ticket.
    * @return true when the order request was successful.
    */
   bool              PlaceLimit(const bool   isBuy,
                                const double entryPrice,
                                const double stopLoss,
                                const double takeProfit,
                                const double lots,
                                const string comment,
                                ulong       &ticket)
     {
      if(lots <= 0.0)
        {
         Print(__FUNCTION__, ": Invalid lot size");
         return false;
        }

      double margin = 0.0;
      if(!OrderCalcMargin(isBuy ? ORDER_TYPE_BUY_LIMIT : ORDER_TYPE_SELL_LIMIT,
                          m_symbol,
                          lots,
                          entryPrice,
                          margin))
        {
         Print(__FUNCTION__, ": OrderCalcMargin failed. Error ", GetLastError());
         return false;
        }

      const double freeMargin = AccountInfoDouble(ACCOUNT_MARGIN_FREE);
      if(margin > freeMargin)
        {
         Print(__FUNCTION__, ": Insufficient margin. Required=", margin, " Free=", freeMargin);
         return false;
        }

      bool result = false;
      if(isBuy)
         result = m_trade.BuyLimit(lots, entryPrice, m_symbol, stopLoss, takeProfit, ORDER_TIME_GTC, 0, comment);
      else
         result = m_trade.SellLimit(lots, entryPrice, m_symbol, stopLoss, takeProfit, ORDER_TIME_GTC, 0, comment);

      if(!result)
        {
         const int errorCode = GetLastError();
         Print(__FUNCTION__, ": Order placement failed. Error ", errorCode);
         return false;
        }

      ticket = m_trade.ResultOrder();
      return true;
     }

   /**
    * Cancels an outstanding pending order ticket.
    * @param ticket Order ticket to remove.
    * @return true when the ticket is cancelled or not found.
    */
   bool              CancelPending(const ulong ticket)
     {
      if(ticket == 0)
         return true;

      if(!OrderSelect(ticket))
         return true;

      if(OrderGetInteger(ORDER_TYPE) != ORDER_TYPE_BUY_LIMIT &&
         OrderGetInteger(ORDER_TYPE) != ORDER_TYPE_SELL_LIMIT)
         return true;

      if(m_trade.OrderDelete(ticket))
         return true;

      Print(__FUNCTION__, ": Failed to delete order ", ticket, " error=", GetLastError());
      return false;
     }
  };

#endif // __THIVYAM_ORDER_EXECUTOR_MQH__
