//+------------------------------------------------------------------+
//|                                              PositionsHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
bool checkTrailingOrder() {
   for(int i=0; i<PositionsTotal(); i++)
   {
      ulong ticket = PositionGetTicket(i);
      if(!PositionSelectByTicket(ticket)) continue;
      if(PositionGetString(POSITION_SYMBOL) != _Symbol) continue;

      string comment = PositionGetString(POSITION_COMMENT);
      int idxBatch = StringFind(comment, "Batch:");
      int idxType = StringFind(comment, ";Typ:Trail");

      Print("🔍(checkTrailingOrder)>>> ??? idxBatch: ", idxBatch, ", idxTyp: ", idxType, ", full-comment: ", comment);

      if(idxBatch != -1 && idxType != -1)
         return true;
   }
   return false;
}

//+------------------------------------------------------------------+
bool checkTrailingByBatchOrder(const string &typeStr) {

   int total_O_P_count = CountOrdersAndPositionsByBatchType(typeStr);
   
   if(total_O_P_count > 0){
      int total_O_count = CountPositionsByBatchType(typeStr);
      int total_P_count = CountOrdersByBatchType(typeStr);

      if(debugging) Print("🧐 ⚠️ (checkTrailingByBatchOrder)>>> Orders count: ", total_O_count, ", Positions count: ", total_P_count, ", typeStr: ", typeStr);

      if(total_O_count > 0){
         ulong orderTicket = GetOrdersByBatchType(typeStr);

         if (debugging) Print("🧐 ⚠️ ‼️ (checkTrailingByBatchOrder)>>> Order ticket: ", orderTicket, ", typeStr: ", typeStr);

         return true;
      }
      if(total_P_count > 0){
         ulong positionTicket = GetPositionsByBatchType(typeStr);
         if (debugging) Print("🧐 ⚠️ ‼️ (checkTrailingByBatchOrder)>>> Position ticket: ", positionTicket, ", typeStr: ", typeStr);
         return true;
      }
   }
   return false;
}

//+------------------------------------------------------------------+
//| Find all positions and return ticket number of a specific        |
//| type (typeStr is the value of param:Batch in the comment,        |
//| e.g. "CtrBUY, EmaBUY, OrigBUY")                                  |
//+------------------------------------------------------------------+
ulong GetPositionsByBatchType(const string &typeStr)
{
    // Count open positions
    int totalPositions = PositionsTotal();
    ulong ticket  = 0;
    for(int i = 0; i < totalPositions; i++)
    {
        ticket = PositionGetTicket(i);
        if(PositionSelectByTicket(ticket) && PositionGetString(POSITION_SYMBOL) == _Symbol)
        {
            string comment = PositionGetString(POSITION_COMMENT);
            string searchStr = "Batch:" + typeStr;
            if(StringFind(comment, searchStr) != -1){
               if(debugging) Print("💭(GetPositionsByBatchType) >>> ticket(", typeStr, "): ", ticket);
               return ticket; // Return the ticket number of the first matching position
            }
        }
    }
    return 0;
}

//+------------------------------------------------------------------+
int CountPositionsByBatchType(const string &typeStr)
{
    int count = 0;
    // Count open positions of specific batch type
    int totalPositions = PositionsTotal();
    for(int i = 0; i < totalPositions; i++)
    {
        ulong ticket = PositionGetTicket(i);
        if(PositionSelectByTicket(ticket) && PositionGetString(POSITION_SYMBOL) == _Symbol)
        {
            string comment = PositionGetString(POSITION_COMMENT);
            string searchStr = "Batch:" + typeStr;
            if(StringFind(comment, searchStr) != -1)
                count++;
        }
    }
    if(debugging) Print("🔢(CountPositionsByBatchType) >>> CountPositionsByBatchType(", typeStr, "): ", count);
    return count;
}

//+------------------------------------------------------------------+
//| Helper: Close all active trades at end of active hours    |
//+------------------------------------------------------------------+
void CloseAllActiveTradesAtEndOfActiveHours()
{
   if(!CloseTradesAtEndOfActiveHours)
      return;

   if(IsWithinActiveHours())
      return;

   for(int i = PositionsTotal() - 1; i >= 0; i--)
   {
      if(PositionGetSymbol(i) == _Symbol)
      {
         ulong ticket = PositionGetTicket(i);
         trade.PositionClose(ticket);
         if(debugging) Print("⏻(CloseAllActiveTradesAtEndOfActiveHours)>>> Closed active trade at end of active hours. Ticket: ", ticket);
      }
   }
}

//+------------------------------------------------------------------+
//| Helper: Count trades (POSITION_TYPE_BUY or POSITION_TYPE_SELL)   |
//+------------------------------------------------------------------+
int PositionsByTradeType(ENUM_POSITION_TYPE type) {
   int count = 0;
   count = CountPositionsByType(type); // Count open positions
   return count;
}

//+------------------------------------------------------------------+
//| v1.02: Helper: Count active trades (pending + open)              |
//+------------------------------------------------------------------+
int CountActiveTrades() {
   int count = 0;
   count = OpenPositionsByChartSymbol(); // Count open positions
   return count;
}

//+------------------------------------------------------------------+
//| Move SL of order to breakeven for a batch                        |
//+------------------------------------------------------------------+
void MovePositionSLToBreakeven(string batch_id)
{
   string findInComment = "Batch:" + batch_id;
   for(int i=0; i<PositionsTotal(); i++)
   {
      if (debugging) { Print("⁉️(MovePositionSLToBreakeven) ********"); PrintTrailingBatches(); }

      ulong ticket = PositionGetTicket(i);
      if(!PositionSelectByTicket(ticket)) continue;
      if(PositionGetString(POSITION_SYMBOL) != _Symbol) continue;

      string comment = PositionGetString(POSITION_COMMENT);
      if(StringFind(comment, findInComment) == -1) continue;

      double open_price = PositionGetDouble(POSITION_PRICE_OPEN);
      double tp = PositionGetDouble(POSITION_TP);

      if(debugging) Print("⁉️(MovePositionSLToBreakeven)>>> Moving SL of third order (batch ", "batch_id", ") to breakeven: ", open_price, " for ticket ", ticket);
      trade.PositionModify(ticket, open_price, tp);
   }
}
//+------------------------------------------------------------------+