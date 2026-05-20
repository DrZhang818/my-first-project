// This file contains test scripts for validating the Opening Range Breakout strategy.
// It includes test cases to ensure that the EA behaves as expected under various market conditions.

#include <Trade\Trade.mqh>
#include <OpeningRangeBreakoutEA.mqh>

input double TestADR = 0.02; // Example ADR value for testing
input double TestMinRangePercentage = 0.15;
input double TestMaxRangePercentage = 0.40;
input string TestMarketOpenTime = "16:30";
input string TestSessionEndTime = "23:00";

void OnStart() {
    Print("Starting Opening Range Breakout EA Tests...");

    // Test case 1: Validate ADR calculation
    double adr = CalculateADR();
    Print("Calculated ADR: ", adr);
    if (adr <= 0) {
        Print("Test Failed: ADR should be greater than 0.");
    } else {
        Print("Test Passed: ADR is valid.");
    }

    // Test case 2: Validate range measurement
    double rangeHigh, rangeLow;
    bool rangeValid = MeasureRange(rangeHigh, rangeLow);
    Print("Range High: ", rangeHigh, ", Range Low: ", rangeLow);
    if (rangeValid) {
        Print("Test Passed: Range measurement is valid.");
    } else {
        Print("Test Failed: Range measurement is invalid.");
    }

    // Test case 3: Validate order placement
    double lotSize = CalculateLotSize();
    if (lotSize > 0) {
        Print("Test Passed: Lot size calculation is valid.");
    } else {
        Print("Test Failed: Lot size should be greater than 0.");
    }

    // Additional test cases can be added here...

    Print("All tests completed.");
}