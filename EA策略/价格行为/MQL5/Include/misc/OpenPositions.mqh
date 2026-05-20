#include <Trade\Trade.mqh>

 // Function to count and print the number of open trades
 int OpenPositions()
 {
     int openTrades = PositionsTotal();
     Print("Number of open trades: ", openTrades);
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
    Print("Number of open trades for symbol ", symbol, ": ", count);
    return count;
 }
 