//+------------------------------------------------------------------+
//|                                        Scalper-Fx.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#include <misc/TradeHelpers.mqh>
#include <Arrays/ArrayString.mqh>

//+------------------------------------------------------------------+
//| v1.05: User Inputs for Time Filter                               |
//+------------------------------------------------------------------+
enum HourEnum
{
   H00, H01, H02, H03, H04, H05, H06, H07, H08, H09, H10, H11,
   H12, H13, H14, H15, H16, H17, H18, H19, H20, H21, H22, H23
};
enum MinuteEnum
{
   M00, M05, M10, M15, M20, M25, M30, M35, M40, M45, M50, M55
};

#include "Libs/CandlesHelper.mq5"
#include "Libs/IndicatorsHelper.mq5"
#include "Libs/DrawingsHelper.mq5"
#include "Libs/TradeHelper.mq5"
#include "Libs/TimeHelper.mq5"
#include "Libs/MiscFunctionsHelper.mq5"

CArrayString trailingBatches;
CArrayString breakevenBatches;

CTrade trade;

//+------------------------------------------------------------------+
//| Timeframe Inputs                                                 |
//+------------------------------------------------------------------+
sinput group ". . . : : | Timeframe Inputs | : : . . ."
input ENUM_TIMEFRAMES HigherTF   = PERIOD_H1;   //  📊 Higher TimeFrame
input ENUM_TIMEFRAMES LowerTF    = PERIOD_M5;   //  📊 Lower TimeFrame
input int HigherTfAtrPeriod      = 14;          // 📈 ATR Period for Higher TimeFrame
input int LowerTfAtrPeriod       = 14;          // 📈 ATR Period for Lower TimeFrame
//+------------------------------------------------------------------+
//| Trading Parameters                                               |
//+------------------------------------------------------------------+
input group ". . . : : | Trading Params | : : . . ."
input bool DynamicLotSize = false;        // 🌀 Dynamic Lot Size?
input double AccountRisk = 0.1;           // 💣 Account Risk (in %)
input double MaxDailyRisk = 0.5;          // 💣 Maximum Risk (in %)
sinput string gap1;                       // 👉
input double Lots = 0.01;                 // 📐 Lot Size per Order
input int Slippage = 0;                   // 🔻 Slippage (in Points)
input int EntryPointOffset = 20;          //  🏹 Offset for Entries
input int SLPointOffset = 40;             // 🛑 Offset for Stops
sinput string gap2;                       // 👉
input int MaxActiveTrades = 6;            // #️⃣ Max No. of Active Trades
input int MaxActiveOrders = 6;            // #️⃣ Max No. of Pending Orders
input int TpForEma = 160;                 // 💰 Take Profit For Ema (in points)
input int TpForCtr = 320;                 // 💰 Take Profit For Ctr (in points)
input int TpForOrig = 640;                // 💰 Take Profit For Orig (in points)
sinput string gap3;                       // 👉
input bool CancelPendingsAtEOD = true;    // ⏻ Pending Orders Expire at 11:59 PM ?
input int trailingSLcandleCount = 5;      // #️⃣ No. of candles for trailing stops
input int consecutiveCandlesCount = 4;    // #️⃣ No. of consecutive candles for order
input int MAsApartByPoints = 10;          // ↔️ Minimum distance between MAs (in points)
input int minSLPoints = 100;              // ↔️ Minimum SL distance (in points)
// input double FirstOrderRR = 1.0;          // [ R : R ] for 1st Trade
// input bool SecondOrder = true;            // Place 2nd Order?
// input double SecondOrderRR = 2.0;         // [ R : R ] for 2nd Trade
// input bool TrailSecondOrder = false;      // Place Trailing SL (2rd) Order?
// input bool ThirdOrder = true;             // Place 3rd Order?
// input bool TrailThirdOrder = false;       // Place Trailing SL (3rd) Order?
// input double ThirdOrderRR = 3.0;          // [ R : R ] for 3rd Trade (0 = DISABLE)

//+------------------------------------------------------------------+
//| Time Parameters                                                  |
//+------------------------------------------------------------------+
input group ". . . : : | Trading Hours | : : . . ."
input bool CheckForActiveHours = true;             // ✅ ENABLE?
input bool CloseTradesAtEndOfActiveHours = false;  // 🚫 Close All Active Trades at End of Trading Window?
sinput string gap4;                                // 👉
input HourEnum ActiveHourStart = H05;              // 🕒 Start Hour
input MinuteEnum ActiveMinuteStart = M15;          // 🕗 Start Minute
input HourEnum ActiveHourEnd = H20;                // 🕒 End Hour
input MinuteEnum ActiveMinuteEnd = M15;            // 🕗 End Minute

sinput group ". . . : : | Miscellaneous | : : . . ."
sinput bool debugging            = true;        // 🔍 DEBUGGING?
sinput int MagicNumber           = 501200;      // ✨ EA Magic Number
sinput bool ShowRect             = true;        // 📐 Show Rectangle on Top Right Corner of Chart?
sinput int RectTextSize          = 8;          // 📐 Rectangle Text Size
sinput bool ShowSpread           = true;        // ↔️ Show Spread Inside Rectangle?
sinput bool ShowTickData         = false;        // 📊 Show Tick Data Inside Rectangle?
sinput bool ShowAtr              = true;        // 📈 Show ATR Data Inside Rectangle?
sinput bool ShowLastCandleSize   = true;        // 📈 Show Last Candle Size Inside Rectangle?
input int extraOrdinaryFactor    = 20;          // 🪄 Factor for Extraordinary Conditions

//+------------------------------------------------------------------+
//| Global state for trailing logic                                  |
//+------------------------------------------------------------------+  
MqlTick tick;
static datetime lastBarTime = 0;    // Last processed bar time
bool firstOrderTPHit    = false;    // Set to true when first order TP is hit
bool secondOrderTPHit   = false;    // Set to true when second order TP is hit
bool thirdOrderTPHit    = false;    // Set to true when third order TP is hit
int yPos = 0; // Y position for labels
// delete afterwards...
bool EnableTrailingOrder = true;    // Place Trailing SL (3rd) Order?
//+------------------------------------------------------------------+
datetime lastTriggerTime = 0;
datetime lastTriggerBarTime = 0;
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- create timer
   EventSetTimer(1);
   CreateRectangleLabel(); // Create a rectangle label for displaying information
//---
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//--- destroy timer
   EventKillTimer();
   
  }
//+------------------------------------------------------------------+
//| Expert tick function                                             |
//|..................................................................|
//| Main trading logic                                               |
//+------------------------------------------------------------------+
void OnTick() {
//---
   double atr_HigherTF = GetATR(_Symbol, HigherTF, HigherTfAtrPeriod, 0) * MathPow(10, _Digits - 1);
   double atr_LowerTF  = GetATR(_Symbol, LowerTF, LowerTfAtrPeriod, 0) * MathPow(10, _Digits - 1);
   if(ShowRect){
      if(ShowSpread) {
         yPos = DisplayBidAskSpreadLabels();  // Display Bid, Ask, and Spread as separate labels
      }
      if(ShowTickData) {
         if(SymbolInfoTick(_Symbol, tick)) {
            double bid = tick.bid;
            double ask = tick.ask;
            double last = tick.last;
            yPos = AddToRect("tickLastLabel", StringFormat("Last Tick: %.5f", last), yPos);
            yPos = AddToRect("tickSpreadLabel", StringFormat("Tick Spread: %.5f", ask - bid), yPos);
         }
      }
      if(ShowAtr) {
         yPos = AddToRect("AtrHigherLabel", StringFormat("H1 ATR(14) : %.1f pip", atr_HigherTF), yPos);
         yPos = AddToRect("AtrLowerLabel", StringFormat("M5 ATR(14): %.1f pip", atr_LowerTF), yPos);
      }
      if(ShowLastCandleSize) {
         MqlRates rates[];
         if(CopyRates(_Symbol, LowerTF, 0, 2, rates) > 0) {
            double lastCandleSize = MathAbs(rates[0].high - rates[0].low) * MathPow(10, _Digits - 1);
            yPos = AddToRect("lastLowerTfCandleLabel", StringFormat("Small: %.1f pip", lastCandleSize), yPos);
         }
         if(CopyRates(_Symbol, HigherTF, 0, 2, rates) > 0) {
            double lastCandleSize = MathAbs(rates[0].high - rates[0].low) * MathPow(10, _Digits - 1);
            yPos = AddToRect("lastHigherTfCandleLabel", StringFormat("Big: %.1f pip", lastCandleSize), yPos);
         }
      }
   }
}

//+------------------------------------------------------------------+
//| Timer function                                                   |
//+------------------------------------------------------------------+
void OnTimer()
{
   // static datetime lastBarTime = 0;    // Last processed bar time
   
   MqlRates rates[];
   if(CopyRates(_Symbol, LowerTF, 0, 10, rates) <= 0) return;

   // v1.03: Generate a unique batch ID for the current bar
   string batch_id = GenerateBatchID(rates[0].time);

   double entry, sl, tp1, tp2;
   datetime expiry = GetEndOfDayExpiration(); // <-- Set expiration to end of day

   // 1. Higher TimeFrame Bias
   double ema8_H1 = GetEMA(_Symbol, HigherTF, 8, 0);
   double ema21_H1 = GetEMA(_Symbol, HigherTF, 21, 0);
   double price_H1 = Round5(iClose(_Symbol, HigherTF, 0));

   bool sellBias = (ema8_H1 < ema21_H1 && price_H1 <= ema8_H1);
   bool buyBias  = (ema8_H1 > ema21_H1 && price_H1 >= ema8_H1);

   // 2. Lower TimeFrame EMAs
   double ema8_M5 = GetEMA(_Symbol, LowerTF, 8, 0);
   double ema13_M5 = GetEMA(_Symbol, LowerTF, 13, 0);
   double ema21_M5 = GetEMA(_Symbol, LowerTF, 21, 0);

   // ATR(14) for Higher and Lower timeframes
   double atr_HigherTF = GetATR(_Symbol, HigherTF, HigherTfAtrPeriod, 0);
   double atr_LowerTF  = GetATR(_Symbol, LowerTF, LowerTfAtrPeriod, 0);

   double close_M5 = Round5(rates[ArraySize(rates)-2].close);  // Old: Round5(rates[1].close);
   double high_M5 = Round5(rates[ArraySize(rates)-2].high);    // Old: Round5(rates[0].high);
   double low_M5 = Round5(rates[ArraySize(rates)-2].low);      // Old: Round5(rates[0].low);

   int activeTrades = CountActiveTrades();                                 // Number of Trades Active
   //if(debugging) Print("🕒(OnTimer)>>> Active trades: ", activeTrades);

   int pendingOrders = CountPendingOrders();                               // Number of Orders Pending
   //if(debugging) Print("🕒(OnTimer)>>> Pending orders: ", pendingOrders);

   if( activeTrades && EnableTrailingOrder)   //if( activeTrades && ( EnableTrailingOrder || checkTrailingOrder() ) )   // v1.04: updated location of this function call
      UpdateTrailingStops();

   if(CheckForActiveHours && !IsWithinActiveHours())
   {
      // Check if we are outside the active hours and close all trades is enabled
      if(CloseTradesAtEndOfActiveHours)
      {
         if (activeTrades) {
            CloseAllActiveTradesAtEndOfActiveHours();
            if(debugging) Print("☢️(OnTimer)>>> Outside active hours. Active trades: ", activeTrades, ". Closing all trades.");
         }
         if(pendingOrders) {
            CancelPendingOrders(trade, _Symbol, debugging);
            if(debugging) Print("☢️(OnTimer)>>> Outside active hours. Pending orders: ", pendingOrders, ". Closing all trades.");
         }
      }
      return; // Exit if outside active hours
   }

   if(pendingOrders) {                                                     // v1.05: check for condition as per base logic
         bool isDeleted = false;
         //--- Check if the last closed bar violated the EMA21
         if(close_M5 > ema8_H1 && ema8_H1 > ema21_M5) {  //ema21_M5) {  // && AreEMAsApart(ema8_M5, ema21_M5, 10)
            DeletePendingOrdersByType(ORDER_TYPE_SELL_STOP, Symbol());
            if(debugging) Print("🕒(OnTimer)>>> Deleted SELL_STOP Orders because of 21 EMA violation.");
            isDeleted = true;
         } 
         else if (close_M5 < ema8_H1 && ema8_H1 < ema21_M5) { //ema21_M5) {  // && AreEMAsApart(ema8_M5, ema21_M5, 10)
            DeletePendingOrdersByType(ORDER_TYPE_BUY_STOP, Symbol());
            if(debugging) Print("🕒(OnTimer)>>> Deleted BUY_STOP Orders because of 21 EMA violation.");
            isDeleted = true;
         }
      if(isDeleted) Print("🕒(OnTimer)>>> Deleted pending orders becasue of 21 EMA violation.");
   }
  
   if(rates[ArraySize(rates)-1].time == lastBarTime) return; // Only act on new bar
   lastBarTime = rates[ArraySize(rates)-1].time;
   
   if(debugging) Print("📈(OnTimer)>>> OpenPositions: ", OpenPositions(), " | ema8_M5: ", ema8_M5, " < ema13_M5: ", ema13_M5, " < ema21_M5: ", ema21_M5, " | CurrentTime: ", TimeCurrent());
   // for placing pending order of type: EmaSELL
   if(OpenPositions() < MaxActiveTrades && OpenOrders() < MaxActiveOrders && 
      CountOrdersAndPositionsByBatchType("EmaSELL") == 0 &&
      DESC == CheckLast4Closes_Ema(rates, ema8_M5, ema13_M5, ema21_M5)) {
      if (DESC ==  CheckLast4BarCloses(rates)) {
         double entry = rates[8].low - EntryPointOffset * _Point;  // - PointOffset * _Point;
         double sl = rates[8].high + SLPointOffset * _Point;
         sl = SetOptimumSL(entry, sl, "sell");
         double risk = MathAbs(sl - entry);
         if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, MAsApartByPoints))
            PlaceTrailingOrder(ORDER_TYPE_SELL_STOP, entry, sl, expiry, false, "EmaSELL");
      }
   }
   // for placing pending order of type: EmaBUY
   if(OpenPositions() < MaxActiveTrades && OpenOrders() < MaxActiveOrders && 
      CountOrdersAndPositionsByBatchType("EmaBUY") == 0 &&
      ASC == CheckLast4Closes_Ema(rates, ema8_M5, ema13_M5, ema21_M5)) {
      if (ASC ==  CheckLast4BarCloses(rates)) {
         double entry = rates[8].high + EntryPointOffset * _Point;  // - PointOffset * _Point;
         double sl = rates[8].low - SLPointOffset * _Point;
         sl = SetOptimumSL(entry, sl, "buy");
         double risk = MathAbs(sl - entry);
         if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, MAsApartByPoints))
            PlaceTrailingOrder(ORDER_TYPE_BUY_STOP, entry, sl, expiry, true, "EmaBUY");
      }
   }
   // for placing pending order of type: CtrSELL
   if(OpenPositions() < MaxActiveTrades && OpenOrders() < MaxActiveOrders && 
      CountOrdersAndPositionsByBatchType("CtrSELL") == 0 &&
      DESC ==  CheckLast4BarCloses(rates)) {
      double entry = MathAbs(rates[8].low - _Point * EntryPointOffset);  // - PointOffset * _Point;
      double sl = rates[8].high + SLPointOffset * _Point;
      sl = SetOptimumSL(entry, sl, "sell");
      double risk = MathAbs(sl - entry);
      // if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, 10))
      if(PositionsByTradeType(POSITION_TYPE_SELL) == 0 && PendingStopOrderByType(ORDER_TYPE_SELL_STOP) == 0)
         PlaceTrailingOrder(ORDER_TYPE_SELL_STOP, entry, sl, expiry, false, "CtrSELL");
      else
         if(debugging)  Print("➖(OnTimer)>>> Not enough space b/w EMAs for SELL_STOP order. | EMA8 - EMA13: ", Round5(MathAbs(ema8_M5 - ema13_M5)), " | EMA13 - EMA21: ", Round5(MathAbs(ema13_M5 - ema21_M5)), " | EMA8 - EMA21: ", Round5(MathAbs(ema8_M5 - ema21_M5)));
   }
   // for placing pending order of type: CtrBUY
   if(OpenPositions() < MaxActiveTrades && OpenOrders() < MaxActiveOrders && 
      CountOrdersAndPositionsByBatchType("CtrBUY") == 0 &&
      ASC ==  CheckLast4BarCloses(rates)) {
      double entry = rates[8].high + _Point * EntryPointOffset;  // - PointOffset * _Point;
      double sl = rates[8].low - SLPointOffset * _Point;
      sl = SetOptimumSL(entry, sl, "buy");
      double risk = MathAbs(sl - entry);
      // if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, 10))
      if(PositionsByTradeType(POSITION_TYPE_BUY) == 0 && PendingStopOrderByType(ORDER_TYPE_BUY_STOP) == 0)
         PlaceTrailingOrder(ORDER_TYPE_BUY_STOP, entry, sl, expiry, true, "CtrBUY");
      else
         if(debugging)  Print("➖(OnTimer)>>> Not enough space b/w EMAs for BUY_STOP order. | EMA8 - ema13: ", MathAbs(ema8_M5 - ema13_M5), " | EMA13 - EMA21: ", MathAbs(ema13_M5 - ema21_M5), " | EMA8 - EMA21: ", MathAbs(ema8_M5 - ema21_M5));
   }

   if(!sellBias && !buyBias) return; // No bias, no trade

   // 3. Trigger bar: price touches EMA8, but not closed above/below EMA21
   bool triggerSell = (sellBias && high_M5 >= ema8_M5 && ema8_M5 < ema13_M5 && ema13_M5 < ema21_M5 && close_M5 < ema21_M5);
   bool triggerBuy  = (buyBias  && low_M5 <= ema8_M5 && ema8_M5 > ema13_M5 && ema13_M5 > ema21_M5 && close_M5 > ema21_M5);

   Print("👆(OnTimer)>>> Trigger Sell: ", triggerSell, " | Trigger Buy: ", triggerBuy, " |>>> sellBias: ", sellBias, " | buyBias: ", buyBias, " |>>> ema8_M5,ema13_M5,ema21_M5: ", ema8_M5, ", ", ema13_M5, ", ", ema21_M5, " | close_M5: ", close_M5, " |>>> ema8_H1,ema21_H1: ", ema8_H1, ", ", ema21_H1, " | price_H1: ", price_H1);

   // v1.04: Find the trigger bar (usually the previous closed bar, i.e., rates[1])
   int triggerBarIndex = 1;
   datetime triggerBarTime = rates[triggerBarIndex].time;

   // v1.04: Only trigger if this is a new trigger bar
   if(triggerBarTime == lastTriggerBarTime) return;
   lastTriggerBarTime = triggerBarTime;

   // v1.04: Now, use rates[triggerBarIndex] for SL/TP calculation:
   double highTrigger = rates[triggerBarIndex].high;
   double lowTrigger = rates[triggerBarIndex].low;

   if((triggerSell || triggerBuy))
   {
      if(lastTriggerTime == rates[ArraySize(rates)-1].time) return; // Prevent duplicate triggers
      lastTriggerTime = rates[ArraySize(rates)-1].time;
      
      // --- v1.02: Check for max active trades ---
      if(activeTrades > MaxActiveTrades) {  // till v1.03: activeTrades >= MaxActiveTrades  | changing again in v2.0
         if(debugging) Print("⏳(OnTimer)>>> There are Trades already active (activeTrades: ", activeTrades, "). No new orders placed.");
         return;
      }

      // if(debugging) PrintRates("🕒(OnTimer)>>> " rates, " >> ", 10);

      // 4. Calculate levels
      //datetime expiry = iTime(_Symbol, PERIOD_D1, 0) + 24*60*60; // End of day
      double lowest5 = GetLowest(_Symbol, LowerTF, 5, 1);
      double highest5 = GetHighest(_Symbol, LowerTF, 5, 1);

      if(MathAbs(highest5 - lowest5) < 50 * _Point) {
         if(debugging) Print("➖(OnTimer)>>> ----- Price range is too low. Order (triggerSell: ", triggerSell,", triggerBuy: ", triggerBuy,") not placed. | RANGE: ", MathAbs(highest5 - lowest5), " | Highest: ", highest5, " | Lowest: ", lowest5, " | less than: ", 50 * _Point);
      }
      else if(triggerSell)
      {
         // --- v1.02->v1.03: changed position: Delete all pending orders before placing new ones
         //--- DeletePendingOrdersByType(ORDER_TYPE_BUY_STOP, Symbol());
      
         double highTrigger = rates[ArraySize(rates)-1].high;
         entry = MathAbs(lowest5 - EntryPointOffset * _Point);
         sl = highTrigger + SLPointOffset * _Point;
         sl = SetOptimumSL(entry, sl, "sell");
         double risk = MathAbs(sl - entry);
         //tp1 = entry - FirstOrderRR * risk; // 1:1
         //tp2 = entry - SecondOrderRR * risk; // 1:2

         //--- if(CountPendingOrders()) return; // Check if there are pending orders before placing new ones

         // Place 2 Sell Stop orders (fixed TP)
         if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, MAsApartByPoints) && CountOrdersAndPositionsByBatchType("OrigSELL") == 0)
            PlaceTrailingOrder(ORDER_TYPE_SELL_STOP, entry, risk, expiry, false, "OrigSELL");  // old: batch_id);
      }
      else if(triggerBuy)
      {      
         // --- v1.02->v1.03: changed position: Delete all pending orders before placing new ones
         //--- DeletePendingOrdersByType(ORDER_TYPE_SELL_STOP, Symbol());
         
         double lowTrigger = rates[ArraySize(rates)-1].low;
         entry = highest5 + EntryPointOffset * _Point;
         sl = MathAbs(lowTrigger - SLPointOffset) * _Point;
         sl = SetOptimumSL(entry, sl, "buy");
         double risk = MathAbs(entry - sl);
         //tp1 = entry + FirstOrderRR * risk; // 1:1
         //tp2 = entry + SecondOrderRR * risk; // 1:2

         //--- if(CountPendingOrders()) return; // Check if there are pending orders before placing new ones
         
         // Place 2 Buy Stop orders (fixed TP)
         if(AreEMAsApart(ema8_M5, ema13_M5, ema21_M5, MAsApartByPoints) && CountOrdersAndPositionsByBatchType("OrigBUY") == 0)
            PlaceTrailingOrder(ORDER_TYPE_BUY_STOP, entry, risk, expiry, true, "OrigBUY");  // old: batch_id);
      }
   }
   
}
//+------------------------------------------------------------------+
//| Trade function                                                   |
//+------------------------------------------------------------------+
void OnTrade() {
   // This function is called on any trade event (order open/close/modify)
   // We'll check if the first order TP was hit, and if so, set the flag and act accordingly

   // Loop through closed deals to check if first order TP was hit
   HistorySelect(TimeCurrent() - 60, TimeCurrent()); // last 7 days
   int totalDeals = HistoryDealsTotal();

   if(totalDeals == 0) return;

   ulong lastDeal = HistoryDealGetTicket(totalDeals - 1);
   long entryType = HistoryDealGetInteger(lastDeal, DEAL_ENTRY);
   long reason    = HistoryDealGetInteger(lastDeal, DEAL_REASON);

   if(entryType == DEAL_ENTRY_IN) {
      CancelPendingOrders(trade, _Symbol, debugging);
      if(debugging) Print("🔴(OnTrade)>>> Deleted all pending orders for symbol: ", _Symbol);
      return;
   }

   else if(entryType == DEAL_ENTRY_OUT && reason == DEAL_REASON_TP) {
      if(debugging) Print("✅(OnTrade)>>> TP Hit");
   /*
      MoveSecondOrderSLToBreakeven();     // Move SL of second order to breakeven
      MoveThirdOrderSLToBreakeven();      // Move SL of third order to breakeven

      for(int i = HistoryDealsTotal() - 1; i >= 0; i--) {
         ulong deal_ticket = HistoryDealGetTicket(i);
         string symbol = HistoryDealGetString(deal_ticket, DEAL_SYMBOL);
         if(symbol != _Symbol) continue;

         string comment = HistoryDealGetString(deal_ticket, DEAL_COMMENT);

         // Check if this is a TP close for a "FirstTP" order
         int idxBatch = StringFind(comment, "Batch:");
         int idxType = StringFind(comment, ";Typ:FirstTP");
         
         if(idxBatch != -1 && idxType != -1)
         {
            // Extract batch_id
            string batch_id = comment;
            StringReplace(batch_id, "Batch:", "");
            int idxSemi = StringFind(batch_id, ";");
            if(idxSemi != -1)
               batch_id = StringSubstr(batch_id, 0, idxSemi);

            // Mark this batch as processed for breakeven
            breakevenBatches.Add(batch_id);
            
            if(debugging) Print("✅(OnTrade)>>> First order TP hit for batch ", batch_id, ". Moving SL of second order to breakeven and enabling trailing for third order.");

            // Enable trailing for this batch (set a flag, or just allow trailing for this batch in UpdateTrailingStops)
            EnableTrailingForBatch(batch_id);

            // Only process once per batch per OnTrade
            break;
         }
      }
   */
   }
   else if(entryType == DEAL_ENTRY_OUT && reason == DEAL_REASON_SL) {
      if(debugging) Print("❌(OnTrade)>>> SL Hit");
   }
   else {
      if(debugging) Print("❓(OnTrade)>>> Other trade event: ", entryType, " | Reason: ", reason);
   }
}
//+------------------------------------------------------------------+
//| TradeTransaction function                                        |
//+------------------------------------------------------------------+
void OnTradeTransaction(const MqlTradeTransaction& trans,
                        const MqlTradeRequest& request,
                        const MqlTradeResult& result) {
   //---
}
//+------------------------------------------------------------------+
//| Tester function                                                  |
//+------------------------------------------------------------------+
double OnTester() {
   //---
   double ret=0.0;
   //---

   //---
   return(ret);
}
//+------------------------------------------------------------------+
//| TesterInit function                                              |
//+------------------------------------------------------------------+
void OnTesterInit() {
   //---

}
//+------------------------------------------------------------------+
//| TesterPass function                                              |
//+------------------------------------------------------------------+
void OnTesterPass() {
   //---

}
//+------------------------------------------------------------------+
//| TesterDeinit function                                            |
//+------------------------------------------------------------------+
void OnTesterDeinit() {
   //---
   EventKillTimer();

}
//+------------------------------------------------------------------+
//| ChartEvent function                                              |
//+------------------------------------------------------------------+
void OnChartEvent(const int id,
                  const long &lparam,
                  const double &dparam,
                  const string &sparam) {
   //---

}
//+------------------------------------------------------------------+
//| BookEvent function                                               |
//+------------------------------------------------------------------+
void OnBookEvent(const string &symbol) {
   //---

}
//+------------------------------------------------------------------+

//+------------------------------------------------------------------+