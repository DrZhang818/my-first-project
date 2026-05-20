// InputsHelper.mqh
#ifndef __INPUTS_HELPER_MQH__
#define __INPUTS_HELPER_MQH__

// For SizeInPips indicator params
enum CalcType { High_Low, Open_Close};
enum DDType { Prev_Close_To_Max, Prev_HighLow_To_Max, Open_To_Max};

enum HourEnum
{
   H00, H01, H02, H03, H04, H05, H06, H07, H08, H09, H10, H11,
   H12, H13, H14, H15, H16, H17, H18, H19, H20, H21, H22, H23
};
enum MinuteEnum
{
   M00, M05, M10, M15, M20, M25, M30, M35, M40, M45, M50, M55
};

// Indicator: SizeInPips -> Buffers: 0-CandleSize, 1-CandleSize2, 2-SMA_HL, 3-SMA_OC, 4-Optimum, 5-CustomSL, 6-CustomSLATR
enum SizeInPips
{
   CandleSize,       // Candle Size
   CandleSize2,      // Candle Size2
   SMA_HL,           // SMA(High-Low)
   SMA_OC,           // SMA(Open-Close)
   //Optimum,          // Optimum
   CustomSL,         // Custom SL
   CustomSLATR       // Custom SL ATR
};

// Input parameters
sinput group ". . . : : | General Params | : : . . ."
input ENUM_TIMEFRAMES Timeframe = PERIOD_D1;    // Timeframe for the strategy
input HourEnum ActiveHourStart = H03;           // 🕒 Start Hour
input MinuteEnum ActiveMinuteStart = M00;       // 🕗 Start Minute
sinput string gap5;                             // 👉
input float OffsetInPts = 30;                   // Offset in points for Trade
input int MaxOpenTrades = 4;                    // Max number of open trades
input ENUM_ORDER_TYPE_FILLING FillingMode = ORDER_FILLING_RETURN;  // Input for filling mode
sinput string gap0 = " ";                       // 👉
input bool logging = false;                     // Enable logging
sinput group ". . . : : | Trading Params | : : . . ."
input bool OneOrderAtATime = true;              // One order at a time
input float RiskPercentage = 0;                 // Risk per trade (0 to disable)
input double LotSize = 0.01;                     // Lot size for orders
input float TakeProfit = 2;                     // Take profit multiplier
input int MaxTradePerSide = 1;                  // Max simultaneous BUY & SELL trades
// input double StopLoss = 3000;                // Stop loss in points
sinput string gap1 = " ";                       // 👉
sinput group ". . . : : | Trade Strategy Params | : : . . ."
input bool Activate3CStrategy = true;           // Activate 3 Candle Strategy?
input bool Activate4CStrategy = true;           // Activate 4 Candle Strategy?
input bool Activate3rdStrategy = true;           // Activate 3rd Strategy?
sinput string gap2 = " ";                       // 👉
sinput group ". . . : : | SL & TP Params | : : . . ."
input bool CutSLToHalf = true;                  // Cut SL to half
input bool TrailSL = true;                      // Enable trailing stop loss?
input bool DynamicTP = true;                    // Enable dynamic TP?
input SizeInPips DynTpType = SMA_HL;            // Dynamic TP type
sinput string gap3 = " ";                       // 👉
sinput group ". . . : : | EMA Params | : : . . ."
input int FastEMAPeriod = 9;                    // Fast EMA period
input int SlowEMAPeriod = 21;                   // Slow EMA period
sinput string gap4;                             // 👉
sinput group ". . . : : | Avg. Candle Calc. Indicator Params | : : . . ."
input int ci_period = 175;                       // SMA period
input double ci_howMuchBig = 10;                // How much bigger from ATR? (in %)
input CalcType ci_calcType = High_Low;          // ATR: High-Low or Open-Close
input DDType ci_ddType = Prev_HighLow_To_Max;   // Custom ATR for SL:

//--- Indicator handle
int SizeInPipsHandle = INVALID_HANDLE;

#endif // __INPUTS_HELPER_MQH__