//+------------------------------------------------------------------+
//|                                               StopLossHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"


//+------------------------------------------------------------------+
//| Trailing Stop Logic (only for batches where trailing is enabled) |
//+------------------------------------------------------------------+

void UpdateTrailingStops() {
   bool res = false;

   // if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for ", _Symbol, " | candleCount: ", candleCount, " | ema21_M5: ", ema21_M5);
      
   // if(debugging) Print("🔄 Rates Copies Successfully. PositionsTotal(): ", PositionsTotal());
    
   for(int i=0; i<PositionsTotal(); i++)
   {
      // if(debugging) Print("🔄i: ", i);
   
      ulong ticket = PositionGetTicket(i);

      if(!PositionSelectByTicket(ticket)) continue;
      if(PositionGetString(POSITION_SYMBOL) != _Symbol) continue;

      string comment = PositionGetString(POSITION_COMMENT);

      // Extract batch_id
      int idxBatch = StringFind(comment, "Batch:");
      int idxType = StringFind(comment, ";Typ:Trail");
      string batch_id = comment;
      
      StringReplace(batch_id, "Batch:", "");
      int idxSemi = StringFind(batch_id, ";");
      if(idxSemi != -1)
         batch_id = StringSubstr(batch_id, 0, idxSemi);

      long  type  =  PositionGetInteger(POSITION_TYPE);
      
      if(type == POSITION_TYPE_SELL) {
         res = UpdateSellTrailingStop(ticket, batch_id, i);
      }
      else if(type == POSITION_TYPE_BUY) {
         res = UpdateBuyTrailingStop(ticket, batch_id, i);
      }
      if(res){
         //if(debugging) Print("✅(UpdateTrailingStops)>>> Success! Trailing Stop for ticket: ", ticket, " (", batch_id,") is updated.");
      }
      else {
         //if(debugging) Print("❌(UpdateTrailingStops)>>> Trailing Stop for ticket: ", ticket, " (", batch_id,") is NOT updated. ");
      }
   }
   if(res){
      if(debugging) Print("✅✅✅(UpdateTrailingStops)>>> Success!✅✅✅");
   }
   else {
      // if(debugging) Print("❌❌❌(UpdateTrailingStops)>>> Failure! ❌❌❌");
   }
}

//+------------------------------------------------------------------+
bool UpdateBuyTrailingStop(ulong ticket, string batch_id, int i) {

   bool ret = false;
   int candleCount = trailingSLcandleCount; // Number of candles to check for trailing stop updates

   // if(debugging) Print("🌊 Batch ID: ", batch_id);

   if(!PositionSelectByTicket(ticket)) {
      if(debugging) Print("❌(UpdateTrailingStops)>>> Failed to select position by ticket: ", ticket);
      return false;
   }
   // CheckForExtraOrdinaryCandle(ticket);

   MqlRates rates[];
   if(CopyRates(_Symbol, LowerTF, 1, candleCount + 1, rates) < candleCount) {
      if(debugging) Print("❌(UpdateTrailingStops)>>> Failed to copy rates for symbol: ", _Symbol, " | candleCount: ", candleCount);
      return false; // Get last 3 completed bars
   }

   double   new_sl         =  0.0;
   double   old_sl         =  PositionGetDouble(POSITION_SL);
   double   price_open     =  PositionGetDouble(POSITION_PRICE_OPEN);
   double   price_current  =  PositionGetDouble(POSITION_PRICE_CURRENT);
   double   stops_level    =  SymbolInfoInteger(_Symbol, SYMBOL_TRADE_STOPS_LEVEL) * _Point;
   
   double oldSlGap         =  MathAbs(old_sl - price_open) * MathPow(10, _Digits);
   double currentSlGap     =  MathAbs(price_current - old_sl) * MathPow(10, _Digits);
   double lowerTfEma21     =  GetEMA(_Symbol, LowerTF, 21, 0);
   double higherTfEma21    =  GetEMA(_Symbol, HigherTF, 21, 0);
   double higherTfEma8     =  GetEMA(_Symbol, HigherTF, 8, 0);

   new_sl = rates[candleCount-1].low;
   
   if(price_current > price_open) {
      if(batch_id == "OrigBUY") {
         // if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for OrigBUY batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);
         
         for(int j=0; j<candleCount; j++) {
            if(rates[j].low < new_sl)
               new_sl = rates[j].low;
         }

         if(new_sl > higherTfEma8) {
            new_sl = higherTfEma8;
         }

         new_sl = OptimizeSL(new_sl, "buy");

         // if(debugging) Print("🔄⬇️(UpdateTrailingStops)>>> Updating BUY trailing SL: ", old_sl, " -> ", new_sl, " for ticket ", ticket, " batch ", batch_id, " countingCandles: ", candleCount);
         
         if(new_sl > old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }

      } else if(batch_id == "EmaBUY") {
         // if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for EmaBUY batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);
         if(lowerTfEma21 < higherTfEma21){
            new_sl = lowerTfEma21;
         }
         else if(currentSlGap > oldSlGap && higherTfEma8 > old_sl) {
            if(higherTfEma8 > lowerTfEma21) {
               new_sl = lowerTfEma21;
            } else {
               new_sl = higherTfEma8;
            }
         }
         new_sl = OptimizeSL(new_sl, "buy");
         if(new_sl > old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }
      } else if(batch_id == "CtrBUY") {
         // if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for CtrBUY batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);;
         if(old_sl > lowerTfEma21) {   // if(currentSlGap > oldSlGap && higherTfEma8 > old_sl) {
            new_sl = higherTfEma8;
         }
         new_sl = OptimizeSL(new_sl, "buy");
         if(new_sl > old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }
      } else {
         if(debugging) Print("❌(UpdateTrailingStops)>>> Invalid batch_id: ", batch_id, " for ticket: ", ticket);
         return false;
      }
   }
   // if(debugging) Print("🔄⬇️⁉️ price_current > price_open && ema21_M5 > old_sl : ", price_current > price_open && lowerTfEma21 > old_sl, " | (",price_current, " > ", price_open, ") && (", lowerTfEma21, " > ", old_sl,")");
   
   if(PendingStopOrderByType(ORDER_TYPE_SELL_STOP)) {
         DeletePendingOrdersByType(ORDER_TYPE_SELL_STOP, _Symbol);
         if(debugging) Print("🔄🔀(UpdateTrailingStops)>>> Deleted SELL_STOP Orders as Sell Position is Trailing");
   }

   // if (debugging) Print("🔄(UpdateTrailingStops)>>> MathAbs(old_sl - price_open):" , Round5(MathAbs(old_sl - price_open)), " x extraOrdinaryFactor(",extraOrdinaryFactor,"): ", Round5(MathAbs(old_sl - price_open)) * extraOrdinaryFactor, " MathAbs(price_current - price_open): ", Round5(MathAbs(price_current - price_open)), " _Point * 40: ", _Point * 40);

   return ret;
}

//+------------------------------------------------------------------+
bool UpdateSellTrailingStop(ulong ticket, string batch_id, int i) {
   
   bool ret = false;
   int candleCount = trailingSLcandleCount; // Number of candles to check for trailing stop updates
   // if(debugging) Print("🌊 Batch ID: ", batch_id);

   if(!PositionSelectByTicket(ticket)) {
      if(debugging) Print("❌(UpdateTrailingStops)>>> Failed to select position by ticket: ", ticket);
      return false;
   }

   MqlRates rates[];
   if(CopyRates(_Symbol, LowerTF, 1, candleCount + 1, rates) < candleCount){
      if(debugging) Print("❌(UpdateTrailingStops)>>> Failed to copy rates for symbol: ", _Symbol, " | candleCount: ", candleCount);
      return false; // Get last 3 completed bars
   }

   double   new_sl         =  0.0;
   double   old_sl         =  PositionGetDouble(POSITION_SL);
   double   price_open     =  PositionGetDouble(POSITION_PRICE_OPEN);
   double   price_current  =  PositionGetDouble(POSITION_PRICE_CURRENT);
   double   stops_level    =  SymbolInfoInteger(_Symbol, SYMBOL_TRADE_STOPS_LEVEL) * _Point;

   double oldSlGap         =  MathAbs(old_sl - price_open) * MathPow(10, _Digits);
   double currentSlGap     =  MathAbs(price_current - old_sl) * MathPow(10, _Digits);
   double lowerTfEma21     =  GetEMA(_Symbol, LowerTF, 21, 0);
   double higherTfEma21    =  GetEMA(_Symbol, HigherTF, 21, 0);
   double higherTfEma8     =  GetEMA(_Symbol, HigherTF, 8, 0);

   new_sl = rates[candleCount-1].high;

   if(price_current < price_open) {
      if(batch_id == "OrigSELL") {
         //if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for OrigSELL batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);
         for(int j=0; j<candleCount; j++) {
            if(rates[j].high > new_sl)
               new_sl = rates[j].high;
         }
         if(new_sl < higherTfEma8) {
            new_sl = higherTfEma8; // + SLPointOffset * _Point;
         }
         
         new_sl = OptimizeSL(new_sl, "sell");
         
         //if(debugging) Print("🔄⬇️(UpdateTrailingStops)>>> Updating SELL trailing SL: ", old_sl, " -> ", new_sl, " for ticket ", ticket, " batch ", batch_id, " countingCandles: ", candleCount);
         if(new_sl < old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }
      } else if(batch_id == "EmaSELL") {
         //if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for EmaSELL batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);
         if(lowerTfEma21 > higherTfEma21){
            new_sl = lowerTfEma21;
         }
         else if(currentSlGap > oldSlGap && higherTfEma8 < old_sl) {
            if(higherTfEma8 < lowerTfEma21) {
               new_sl = lowerTfEma21;
            } else {
               new_sl = higherTfEma8;
            }
         }
         new_sl = OptimizeSL(new_sl, "sell");
         if(new_sl < old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }
      } else if(batch_id == "CtrSELL") {
         // if(debugging) Print("🔄(UpdateTrailingStops)>>> Updating trailing stops for CtrSELL batch_id: ", batch_id, " | ticket: ", ticket, " | candleCount: ", candleCount);
         if(old_sl < lowerTfEma21) {   // if(currentSlGap > oldSlGap && higherTfEma8 < old_sl) {
            new_sl = higherTfEma8;
         } 
         new_sl = OptimizeSL(new_sl, "sell");
         if(new_sl < old_sl) {
            trade.PositionModify(ticket, new_sl, PositionGetDouble(POSITION_TP));
            ret = true;
         }
      } else {
         if(debugging) Print("❌(UpdateTrailingStops)>>> Invalid batch_id: ", batch_id, " for ticket: ", ticket);
         return false;
      }
   }
   // if(debugging) Print("🔄⬇️⁉️ price_current < price_open && higherTfEma8 < old_sl : ", price_current < price_open && higherTfEma8 < old_sl, " | (",price_current, " < ", price_open, ") && (", higherTfEma8, " < ", old_sl,")");
   
   if(PendingStopOrderByType(ORDER_TYPE_BUY_STOP)) {
         DeletePendingOrdersByType(ORDER_TYPE_BUY_STOP, _Symbol);
         if(debugging) Print("🔄🔀(UpdateTrailingStops)>>> Deleted BUY_STOP Orders as Buy Position is Trailing");
   }
   return ret;
}

//+------------------------------------------------------------------+
double OptimizeSL(double value, string type) {
   
   double spread = tick.ask - tick.bid;
   // if(debugging) Print("Before: ", value, " | Spread: ", spread," | tick.bid: ", tick.bid, " | tick.ask: ", tick.ask, " | tick.last: ", tick.last);
   
   if(type == "buy")
      value = value - SLPointOffset * _Point - spread;
   else if(type == "sell")
      value = value + SLPointOffset * _Point + spread;
   else
      if(debugging) Print("❌(OptimizeSL)>>> Invalid type for OptimizeSL: ", type);

   // if(debugging) Print("After: ", value);
   return NormalizeDouble(value, _Digits);
}

//+------------------------------------------------------------------+