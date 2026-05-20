// OpeningRangeBreakoutEA.mqh
// This file defines the functions and classes used by the Opening Range Breakout EA.

#include <Trade/Trade.mqh>
#include <Math/Stat/Stat.mqh>

class COpeningRangeBreakoutEA {
private:
    double ADR;
    double currentRisk;
    datetime openTime, endTime;
    double profitToday; // Variable to store today's profit
    double rangeSize; // Variable to store the calculated range size
    
public:
    COpeningRangeBreakoutEA() {}
    COpeningRangeBreakoutEA(int adrPeriod, double minRangePercentage, double maxRangePercentage, 
                           string marketOpenTime, string sessionEndTime) {
        ADR = CalculateADR(_Symbol, adrPeriod);
        openTime = StringToTime(TimeToString(TimeCurrent(), TIME_DATE) + " " + marketOpenTime);
        endTime = StringToTime(TimeToString(TimeCurrent(), TIME_DATE) + " " + sessionEndTime);
        currentRisk = 1.0; // Default initial risk
    }

    double CalculateADR(string symbol, int adrPeriod) {
        double sum = 0;
        for(int i=1; i<=adrPeriod; i++)
        {
           double high = iHigh(symbol, PERIOD_D1, i);
           double low  = iLow(symbol, PERIOD_D1, i);
           sum += (high - low);
        }
        return (adrPeriod > 0) ? sum / adrPeriod : 0;
    }

    bool MeasureRange(double &high, double &low) {
        int barsSinceOpen = iBars(_Symbol, PERIOD_M5);
        if (barsSinceOpen > 6) return false;

        high = iHigh(_Symbol, PERIOD_M5, iHighest(_Symbol, PERIOD_M5, MODE_HIGH, barsSinceOpen, 1));
        low = iLow(_Symbol, PERIOD_M5, iLowest(_Symbol, PERIOD_M5, MODE_LOW, barsSinceOpen, 1));
        double range = high - low;
        return (range >= (0.15 * ADR) && range <= (0.40 * ADR)); // Example percentages
    }

    void PlacePendingOrders(double high, double low) {
        double lotSize = CalculateLotSize();
        double slDistance = ADR * 0.15; // Example stop loss percentage
        double tpDistance = ADR * 1.0; // Example take profit multiple

        CTrade trade;
        trade.BuyStop(lotSize, high, _Symbol, high - slDistance, high + tpDistance);
        trade.SellStop(lotSize, low, _Symbol, low + slDistance, low - tpDistance);
    }

    double CalculateLotSize() {
        // Implement risk calculation logic here
        return currentRisk; // Placeholder
    }

    static void ManageTrades() {
        for (int i = PositionsTotal() - 1; i >= 0; i--) {
            ulong ticket = PositionGetTicket(i);
            if (PositionSelectByTicket(ticket)) {
                // Manage each position (trailing stops, partial closes, etc.)
            }
        }
    }

    void CheckSessionEnd() {
        if (TimeCurrent() >= endTime) {
            for (int i = PositionsTotal() - 1; i >= 0; i--) {
                CTrade trade;
                trade.PositionClose(PositionGetTicket(i));
            }
        }
    }
    
    // Function to display values in a rectangle box
    bool DisplayInfoBox(double startingBalance, double currentBalance,
                    double openProfit, double nettProfit, double adr,
                    double minRangeSize, double maxRangeSize, double lastTradeProfit,
                    double nextRiskAmount, double previousDayProfit)
    {
        // Define the base name for the labels
        string baseName = "InfoBox_";
        int yOffset = 20; // Vertical spacing between labels

        // Create or update each label
        CreateOrUpdateLabel(baseName + "StartingBalance", StringFormat("Starting Balance: %.2f", startingBalance), 10, yOffset * 2);
        CreateOrUpdateLabel(baseName + "CurrentBalance", StringFormat("Current Balance: %.2f", currentBalance), 10, yOffset * 3);
        CreateOrUpdateLabel(baseName + "ProfitToday", StringFormat("Profit Today: %.2f", profitToday), 10, yOffset * 4);
        CreateOrUpdateLabel(baseName + "OpenProfit", StringFormat("Open Profit: %.2f", openProfit), 10, yOffset * 5);
        CreateOrUpdateLabel(baseName + "NettProfit", StringFormat("Nett Profit: %.2f", nettProfit), 10, yOffset * 6);
        CreateOrUpdateLabel(baseName + "ADR", StringFormat("ADR: %.2f", adr), 10, yOffset * 7);
        CreateOrUpdateLabel(baseName + "RangeSize", StringFormat("Range Size: %.2f", rangeSize), 10, yOffset * 8);
        CreateOrUpdateLabel(baseName + "MinRangeSize", StringFormat("Min Range Size: %.2f", minRangeSize), 10, yOffset * 9);
        CreateOrUpdateLabel(baseName + "MaxRangeSize", StringFormat("Max Range Size: %.2f", maxRangeSize), 10, yOffset * 10);
        CreateOrUpdateLabel(baseName + "LastTradeProfit", StringFormat("Last Trade Profit: %.2f", lastTradeProfit), 10, yOffset * 11);
        CreateOrUpdateLabel(baseName + "NextRiskAmount", StringFormat("Next Risk Amount: %.2f", nextRiskAmount), 10, yOffset * 12);
        CreateOrUpdateLabel(baseName + "PreviousDayProfit", StringFormat("Previous Day Profit: %.2f", previousDayProfit), 10, yOffset * 13);
        return true;
    }

   // Helper function to create or update a label
   void CreateOrUpdateLabel(string name, string text, int xDistance, int yDistance) {
        int fontSize = 10; // Font size for labels
        if (ObjectFind(0, name) == -1)
        {
            if (!ObjectCreate(0, name, OBJ_LABEL, 0, 0, 0)) {
                Print("Failed to create object: ", name, " Error: ", GetLastError());
                return;
            }
            Print("Yes: ", name, " | ", text, " | ", xDistance, " | ", yDistance);
            ObjectSetInteger(0, name, OBJPROP_CORNER, CORNER_LEFT_UPPER);
            ObjectSetInteger(0, name, OBJPROP_XDISTANCE, xDistance);
            ObjectSetInteger(0, name, OBJPROP_YDISTANCE, yDistance);
            ObjectSetInteger(0, name, OBJPROP_COLOR, clrBlack);
            ObjectSetInteger(0, name, OBJPROP_FONTSIZE, fontSize);
        }
        ObjectSetString(0, name, OBJPROP_TEXT, text);
    }
    // Function to calculate today's profit
   double CalculateTodaysProfit() {
      profitToday = 0.0; // Reset profitToday to 0
      datetime todayStart = iTime(_Symbol, PERIOD_D1, 0); // Start of today's trading day
      
      // Loop through all historical deals
      for (int i = HistoryDealsTotal() - 1; i >= 0; i--) {
         ulong dealTicket = HistoryDealGetTicket(i); // Get the ticket of the historical deal
         if (dealTicket > 0) {
            datetime dealTime = (datetime)HistoryDealGetInteger(dealTicket, DEAL_TIME); // Get deal time
            double dealProfit = HistoryDealGetDouble(dealTicket, DEAL_PROFIT); // Get deal profit
            
            // Check if the deal occurred today
            if (dealTime >= todayStart)
               profitToday += dealProfit; // Add profit to today's total
         }
      }
      return profitToday;
   }
    // Function to calculate the range size
    double CalculateRangeSize(ENUM_TIMEFRAMES timeframe) {
        rangeSize = 0.0; // Reset range size
        // Get the index of the first candle after the market open time
        int totalBars = iBars(_Symbol, timeframe);
        for (int i = totalBars - 1; i >= 0; i--) {
            datetime candleTime = iTime(_Symbol, timeframe, i);
            if (candleTime >= openTime) {
                // Calculate the range size of the first candle
                double high = iHigh(_Symbol, timeframe, i);
                double low = iLow(_Symbol, timeframe, i);
                rangeSize = high - low;
                break; // Exit the loop after finding the first candle
            }
        }
        return rangeSize;
    }
    bool DrawRangeLines(datetime marketOpenTime, ENUM_TIMEFRAMES timeframe, string rangeName, bool debug) {
        // Calculate a future time (e.g., 10 years from the starting time)
        datetime time2 = marketOpenTime + 24 * 60 * 60; // 1 day in seconds

        // Get the index of the first candle after the market open time
        int totalBars = iBars(_Symbol, timeframe);
        if(debug) Print(">>> DrawRangeLines(): totalBars : ", totalBars);
        if(debug) Print(">>> DrawRangeLines(): currentCandleTime : ", iTime(_Symbol, timeframe, 0), " | marketOpenTime: ",  marketOpenTime);
        for (int i = totalBars - 1; i >= 0; i--) {
            datetime candleTime = iTime(_Symbol, timeframe, i);
            if (candleTime >= marketOpenTime) {
                // Get the high and low of the first candle
                double high = iHigh(_Symbol, timeframe, i);
                double low = iLow(_Symbol, timeframe, i);

               // Create or update the high line
               string highLineName = rangeName + "_High";
               if (ObjectFind(0, highLineName) < 0)
                 {
                    // Object doesn't exist, create a new trend line
                    if (!ObjectCreate(0, highLineName, OBJ_TREND, 0, marketOpenTime, high, time2, high))
                    {
                        Print("Failed to create trend line object: ", GetLastError());
                        return false;
                    }
                 }
               else
                 {
                    // Object exists, update its coordinates
                    ObjectSetInteger(0, highLineName, OBJPROP_TIME, 0, marketOpenTime);
                    ObjectSetDouble(0, highLineName, OBJPROP_PRICE, 0, high);
                    ObjectSetDouble(0, highLineName, OBJPROP_PRICE, 1, high); // Same price for horizontal line
                    ObjectSetInteger(0, highLineName, OBJPROP_TIME, 1, time2);
                 } 

               // Create or update the low line
               string lowLineName = rangeName + "_Low";
               if (ObjectFind(0, lowLineName) < 0)
                 {  
                    // Object doesn't exist, create a new trend line
                    if (!ObjectCreate(0, lowLineName, OBJ_TREND, 0, marketOpenTime, low, time2, low))
                    {
                        Print("Failed to create trend line object: ", GetLastError());
                        return false;
                    }
                 }
               else
                 {
                    // Object exists, update its coordinates
                    ObjectSetInteger(0, lowLineName, OBJPROP_TIME, 0, marketOpenTime);
                    ObjectSetDouble(0, lowLineName, OBJPROP_PRICE, 0, low);
                    ObjectSetDouble(0, lowLineName, OBJPROP_PRICE, 1, low); // Same price for horizontal line
                    ObjectSetInteger(0, lowLineName, OBJPROP_TIME, 1, time2);
                 }
                 // Set the ray property to extend the line to the right
                  ObjectSetInteger(0, highLineName, OBJPROP_RAY_RIGHT, true);
                  ObjectSetInteger(0, lowLineName, OBJPROP_RAY_RIGHT, true);
               
                  // Set visual properties for high line
                  ObjectSetInteger(0, highLineName, OBJPROP_COLOR, clrGreen);          // Line color
                  ObjectSetInteger(0, highLineName, OBJPROP_STYLE, STYLE_SOLID);       // Line style (e.g., solid, STYLE_DASH)
                  ObjectSetInteger(0, highLineName, OBJPROP_WIDTH, 1);                 // Line width
                  // Set visual properties for low line
                  ObjectSetInteger(0, lowLineName, OBJPROP_COLOR, clrRed);             // Line color
                  ObjectSetInteger(0, lowLineName, OBJPROP_STYLE, STYLE_SOLID);        // Line style (e.g., solid, STYLE_DASH)
                  ObjectSetInteger(0, lowLineName, OBJPROP_WIDTH, 1);                  // Line width
               
                  // Prevent the lines from being manually selected or moved
                  ObjectSetInteger(0, highLineName, OBJPROP_SELECTABLE, false);
                  ObjectSetInteger(0, highLineName, OBJPROP_SELECTED, false);
                  ObjectSetInteger(0, lowLineName, OBJPROP_SELECTABLE, false);
                  ObjectSetInteger(0, lowLineName, OBJPROP_SELECTED, false);

                break; // Exit the loop after processing the first candle
            }
        }
        return true;
    }
};