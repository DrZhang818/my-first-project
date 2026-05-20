//+------------------------------------------------------------------+
//|                                          PendingOrdersHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Place Pending Order (updated in v1.03)                           |
//+------------------------------------------------------------------+
void PlacePendingOrder(ENUM_ORDER_TYPE type, double price, double sl, double tp, datetime expiry, string batch_id, string order_type)
{
   MqlTradeRequest req = {};
   MqlTradeResult res = {};
   req.action = TRADE_ACTION_PENDING;
   req.symbol = _Symbol;
   req.volume = Lots;
   req.type = type;
   req.price = NormalizeDouble(price, _Digits);
   req.sl = NormalizeDouble(sl, _Digits);
   req.tp = NormalizeDouble(tp, _Digits);
   req.deviation = Slippage;
   req.type_filling = ORDER_FILLING_FOK;
   req.type_time = ORDER_TIME_SPECIFIED_DAY; // Set order type time to specified day
   req.expiration = expiry;
   req.comment = "Batch:" + batch_id + ";Typ:" + order_type;
   if(!OrderSend(req, res))
   {
      Print("OrderSend failed: ", res.retcode, " - ", res.comment);
   }
   else
   {
      // Draw arrow on chart at the candle where the order is placed
      MqlRates rates[];
      int arrowIndex = 9; // Use the most recent closed candle
      string arrowName = order_type + "_Arrow_" + batch_id + "_" + IntegerToString(type) + "_" + IntegerToString(res.order);
      bool isBuy = (type == ORDER_TYPE_BUY_STOP || type == ORDER_TYPE_BUY_LIMIT);
      double arrowPrice = isBuy ? rates[arrowIndex].low - (10 * _Point) : rates[arrowIndex].high + (10 * _Point);
      DrawOrderArrow(arrowName, rates, arrowIndex, arrowPrice, isBuy);
      
   }
}

//+------------------------------------------------------------------+
//| Place Trailing Order (no TP, trailing SL) DELETE                 |
//+------------------------------------------------------------------+
void PlaceTrailingOrder(ENUM_ORDER_TYPE type, double price, double sl, datetime expiry, bool isBuy, string batch_id)
{
   double optimumPrice = price;
   double ask = SymbolInfoDouble(_Symbol, SYMBOL_ASK);
   double bid = SymbolInfoDouble(_Symbol, SYMBOL_BID);
   double tp = 0.0;
   if(type == ORDER_TYPE_BUY_STOP) {
      if(optimumPrice < ask)
         optimumPrice = ask + SLPointOffset * _Point;
      if(batch_id == "EmaBUY")
         tp = optimumPrice + TpForEma * _Point;
      else if(batch_id == "CtrBUY")
         tp = optimumPrice + TpForCtr * _Point;
      else if(batch_id == "OrigBUY")
         tp = optimumPrice + TpForOrig * _Point;
   } else if(type == ORDER_TYPE_SELL_STOP) {
      if(optimumPrice > bid)
         optimumPrice = bid - SLPointOffset * _Point;
      if(batch_id == "EmaSELL")
         tp = optimumPrice - TpForEma * _Point;
      else if(batch_id == "CtrSELL")
         tp = optimumPrice - TpForCtr * _Point;
      else if(batch_id == "OrigSELL")
         tp = optimumPrice - TpForOrig * _Point;
   }
   MqlTradeRequest req = {};
   MqlTradeResult res = {};
   req.action = TRADE_ACTION_PENDING;
   req.symbol = _Symbol;
   req.volume = Lots;
   req.type = type;
   req.price = NormalizeDouble(optimumPrice, _Digits);
   req.sl = NormalizeDouble(sl, _Digits);
   req.tp = NormalizeDouble(tp, _Digits);
   req.deviation = Slippage;
   req.type_filling = ORDER_FILLING_FOK;
   if(CancelPendingsAtEOD)
      req.type_time = ORDER_TIME_SPECIFIED_DAY; // Set order type time to specified day
   req.expiration = expiry;
   req.comment = "Batch:" + batch_id + ";Type:Trailing";
   if(finalCheckBeforeOrderSend())
      if(!OrderSend(req, res))
      {
         Print("OrderSend (trailing) failed: ", res.retcode, " - ", res.comment);
      }
      else
      {  
         if (debugging) Print("➕(PlaceTrailingOrder)>>> Order placed successfully. Order ID: ", res.order, " | Type: ", type, " | Price: ", price, " | SL: ", sl, " | TP: ", 0.0, " | Expiry: ", expiry, " | Comment: ", req.comment);
         // Draw arrow on chart at the candle where the order is placed
         MqlRates rates[];
         if(CopyRates(_Symbol, LowerTF, 0, 10, rates) <= 0) return;
         int arrowIndex = 9;  // 1 = most recent closed candle
         string arrowName = "Trailing_Arrow_" + batch_id + "_" + IntegerToString(type) + "_" + IntegerToString(res.order);
         double arrowPrice = isBuy ? rates[arrowIndex].low - (10 * _Point) : rates[arrowIndex].high + (10 * _Point);
         DrawOrderArrow(arrowName, rates, arrowIndex, arrowPrice, isBuy);
      }
   else {
      if(debugging) Print("❌(PlaceTrailingOrder)>>> finalCheckBeforeOrderSend() failed.");
   }
   checkTrailingByBatchOrder(batch_id);
}

//+------------------------------------------------------------------+
//| Find all pending orders and return ticket number of a specific   |
//| type (typeStr is the value of param:Batch in the comment,        |
//| e.g. "CtrBUY, EmaBUY, OrigBUY")                                  |
//+------------------------------------------------------------------+
ulong GetOrdersByBatchType(const string &typeStr)
{
    // Count pending orders
    int totalOrders = OrdersTotal();
    ulong ticket  = 0;
    for(int i = 0; i < totalOrders; i++)
    {
        ticket = OrderGetTicket(i);
        if(ticket > 0 && OrderGetString(ORDER_SYMBOL) == _Symbol)
        {
            string comment = OrderGetString(ORDER_COMMENT);
            // Look for ";Typ:typeStr" in the comment
            string searchStr = "Batch:" + typeStr;
            if(StringFind(comment, searchStr) != -1) {
               if(debugging) Print("💭(GetOrdersByBatchType) >>> ticket(", typeStr, "): ", ticket);
               return ticket; // Return the ticket number of the first matching position
            }
        }
    }
    return 0;
}

//+------------------------------------------------------------------+
int CountOrdersByBatchType(const string &typeStr)
{
    int count = 0;
    // Count pending orders of specific batch type
    int totalOrders = OrdersTotal();
    for(int i = 0; i < totalOrders; i++)
    {
        ulong ticket = OrderGetTicket(i);
        if(ticket > 0 && OrderGetString(ORDER_SYMBOL) == _Symbol)
        {
            string comment = OrderGetString(ORDER_COMMENT);
            // Look for ";Typ:typeStr" in the comment
            string searchStr = "Batch:" + typeStr;
            if(StringFind(comment, searchStr) != -1)
                count++;
        }
    }
    if(debugging) Print("🔢(CountOrdersByBatchType) >>> CountOrdersByBatchType(", typeStr, "): ", count);
    return count;
}

//+------------------------------------------------------------------+
//| Helper: Count pending orders                                     |
//+------------------------------------------------------------------+
int CountPendingOrders() {
   int count = 0;
   count = OpenOrdersByChartSymbol();
   return count;
}

//+------------------------------------------------------------------+
//| Helper: Delete pending orders by Type of Order                   |
//+------------------------------------------------------------------+
void DeletePendingOrdersByType(int order_type, string symbol) {
   
   if(debugging) Print("🚫(DeletePendingOrdersByType)>>> Deleting all pending orders of type ", order_type, " for symbol ", symbol);
   CancelPendingOrders(trade, order_type, Symbol(), debugging);
}

//+------------------------------------------------------------------+
//| Helper: Count trades ORDER_TYPE_BUY_STOP or ORDER_TYPE_SELL_STOP |
//+------------------------------------------------------------------+
int PendingStopOrderByType(ENUM_ORDER_TYPE type) {
   int count = 0;
   count = CountPendingStopOrderByType(type); // Count pending stop orders
   return count;
}


//+------------------------------------------------------------------+