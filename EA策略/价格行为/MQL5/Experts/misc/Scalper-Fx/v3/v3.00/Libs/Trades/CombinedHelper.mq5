//+------------------------------------------------------------------+
//|                                               CombinedHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"

//+------------------------------------------------------------------+
//| Count all pending orders and open positions with a specific type |
//| (typeStr is the value of param:type in the comment, e.g. "Trail")|
//+------------------------------------------------------------------+
int CountOrdersAndPositionsByBatchType(const string &typeStr)
{
    int count = 0;

    // Count pending orders
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

    // Count open positions
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
    if(debugging) Print("🔢(CountOrdersAndPositionsByBatchType) >>> CountOrdersAndPositionsByBatchType(", typeStr, "): ", count);
    return count;
}

//+------------------------------------------------------------------+