#include <Trade/Trade.mqh>
#include "../Include/OpeningRangeBreakoutEA.mqh"

input ENUM_TIMEFRAMES Timeframe = PERIOD_M5;
input int ADRPeriod = 10;
input double MinRangePercentage = 0.15;
input double MaxRangePercentage = 0.40;
input string MarketOpenTime = "16:30";
input string SessionEndTime = "23:00";
input double StopLossPercentage = 0.15;
input double TakeProfitMultiple = 1.0;
input bool EnableTrailingStop = true;
input double TrailingStopPercentage = 0.15;
input bool TrailUntilBreakEven = false;
input bool EnablePartialProfit = true;
input double PartialProfitPercentage = 0.30;
input double PartialClosePercentage = 75.0;
input bool EnableLossRecovery = true;
input double LossRecoveryMultiplier = 1.1;
input bool PortfolioMode = false;
input double StartingBalance = 5000.00;
input bool debugging = false;

COpeningRangeBreakoutEA orbEA; // Create an instance

CTrade Trade;
double ADR;
datetime openTime, endTime;
double currentRisk;

int OnInit() {
    ChartSetSymbolPeriod(0, _Symbol, Timeframe);
    ADR = orbEA.CalculateADR(_Symbol, ADRPeriod);
    openTime = StringToTime(TimeToString(TimeCurrent(), TIME_DATE) + " " + MarketOpenTime);
    endTime = StringToTime(TimeToString(TimeCurrent(), TIME_DATE) + " " + SessionEndTime);
    currentRisk = GetInitialRisk();
    if(debugging) Print("OnInit: ADR: ", ADR, " | openTime: ", openTime, " | endTime: ", endTime, " | currentRisk: ", currentRisk); // for debugging
    return(INIT_SUCCEEDED);
}

void OnTick() {
    // Example values (replace with actual calculations)
    double currentBalance = AccountInfoDouble(ACCOUNT_BALANCE);
    double profitToday = orbEA.CalculateTodaysProfit();
    double openProfit = 0.0;   // Replace with actual calculation
    double nettProfit = 0.0;  // Replace with actual calculation
    double rangeSize = orbEA.CalculateRangeSize(Timeframe);   // Replace with actual calculation
    double minRangeSize = ADR * MinRangePercentage;
    double maxRangeSize = ADR * MaxRangePercentage;
    double lastTradeProfit = 0.0; // Replace with actual calculation
    double nextRiskAmount = 0.0; // Replace with actual calculation
    double previousDayProfit = 0.0; // Replace with actual calculation

    // Call the function to display the info box
    if(orbEA.DisplayInfoBox(StartingBalance, currentBalance, openProfit, nettProfit,
                        ADR, minRangeSize, maxRangeSize, lastTradeProfit,
                        nextRiskAmount, previousDayProfit))
    {
        // Info box displayed successfully
        //Print("Box created successfully.");
    }
    else {
        Print("Failed to create box.");
    }
    
    orbEA.DrawRangeLines(openTime, Timeframe, "DailyRange", debugging);

    if (TimeCurrent() < openTime || TimeCurrent() >= endTime) return;
    if (!IsNewCandle()) return;

    double rangeHigh, rangeLow;
    if (orbEA.MeasureRange(rangeHigh, rangeLow)) {
        CancelPendingOrders();
        orbEA.PlacePendingOrders(rangeHigh, rangeLow);
    }

    orbEA.ManageTrades();
    CheckSessionEnd();
}

void CheckSessionEnd() {
    if (TimeCurrent() >= endTime) {
        for (int i = PositionsTotal() - 1; i >= 0; i--) {
            Trade.PositionClose(PositionGetTicket(i));
        }
        CancelPendingOrders();
    }
}

bool IsNewCandle() {
    static datetime lastTime = 0;
    datetime currentTime = iTime(_Symbol, Timeframe, 0);
    if (currentTime != lastTime) {
        lastTime = currentTime;
        return true;
    }
    return false;
}

void CancelPendingOrders() {
    for (int i = OrdersTotal() - 1; i >= 0; i--) {
        Trade.OrderDelete(OrderGetTicket(i));
    }
}

double GetInitialRisk() {
    return 1.0; // Placeholder for risk calculation
}