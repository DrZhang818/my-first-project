#ifndef INPUT_PARAMS_HELPER_MQH
#define INPUT_PARAMS_HELPER_MQH
//--- Input parameters for the indicator
input group "...::| Indicator Settings |::..."
input ENUM_TIMEFRAMES inputTimeframe = PERIOD_M5;   // Chart Period
input int Mode = 0;                                 // Mode (0 = Recent Candles, 1 = From Date)
input int RecentCandles = 150;                      // Number of recent candles (if Mode = 0)
input datetime FromDate = D'2025.01.01 00:00';      // Start date for FromDate mode  (if Mode = 1)
input bool debugging = false;                       // Enable/Disable debug prints

//--- Input parameters for trading
input group "...::| Trading Settings |::..."
input double lot_size = 0.01;   // Lot Size
input double t_p = 0;           // Take Profit (in points)
input double s_l = 0;           // Stop Loss (in points)
input double entry_gap = 20;    // Gap above/below the entry point (in points)
input double sl_gap = 50;       // Gap above/below the SL (in points)
input double tp_gap = 30;       // Gap above/below the TP (in points)

//--- Input parameters for dynamic TP & SL
input group "...::| Dynamic Settings |::..."
input double dyn_tp_mul = 2;        // Take Profit (multiple of ATR)
input double dyn_sl_mul = 1;        // Stop Loss (multiple of ATR)
input int atr_val = 22;             // ATR value (in points)

//--- Add global variables to store dynamic TP and SL (in points)
double dynamic_tp_pips = 0;
double dynamic_sl_pips = 0;
//--- Add global variable to store static TP & SL as per input params.
double take_profit = t_p;
double stop_loss = s_l;
//--- Global variable to track the last processed candle
datetime lastCandleTime = 0;

#endif 