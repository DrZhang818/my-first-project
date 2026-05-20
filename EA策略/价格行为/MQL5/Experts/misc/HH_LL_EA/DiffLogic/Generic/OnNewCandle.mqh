
//+----------------------------------------------------------------------+
//| Function to retrieve and process indicator data for generic candles  |
//+----------------------------------------------------------------------+
//void OnNewCandle()
//{
    //--- Populate buffers from indicator: "TI_HL_Diff"
    ProcessTI_HL_DiffIndicatorData();
    //--- Populate buffers from indicator: "SizeInPips" and calculate dynamic TP & SL
    ProcessSizeInPipsIndicatorData();
    // --- Get dynamic TP and SL from SizeInPips indicator
    if(take_profit == 0 || stop_loss == 0)
    {
         
         if(take_profit == 0){
            take_profit = dynamic_tp_pips;
            if(debugging) Print("Take Profit set to: ", take_profit, " pips");
         }
         if(stop_loss == 0){
            stop_loss = dynamic_sl_pips;
            if(debugging) Print("Stop Loss set to: ", stop_loss, " pips");
         }
    }

    // Check for open positions on this symbol
    if (OpenPositionsByChartSymbol() == 0 && !HasPendingStopOrder(Symbol()))
    {
        double price_high = iHigh(Symbol(), inputTimeframe, 1); // last closed candle's high
        double price_low  = iLow(Symbol(), inputTimeframe, 1);  // last closed candle's low

        // Place Buy Stop if HH_Buffer[0] is non-zero
        if (HH_Buffer[0] != 0.0)
        {        
            double buy_stop = price_high + entry_gap * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            // double sl = buy_stop - (stop_loss - sl_gap) * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            double sl = price_low - sl_gap * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            double tp = buy_stop + (take_profit - tp_gap) * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            
            CancelPendingOrders(trade, ORDER_TYPE_SELL_STOP, Symbol(), debugging);
            bool placed = PlaceBuyStop(trade, lot_size, buy_stop, Symbol(), sl, tp);
            if(debugging) Print("Buy Stop order placed at " + DoubleToString(buy_stop));
            Print("Buy Stop!", entry_gap);
                
            if (placed)
                if(debugging) Print("Buy Stop order placed at ", buy_stop, " TP: ", tp, " SL: ", sl, " | SymbolInfoDouble(Symbol(), SYMBOL_POINT): ", SymbolInfoDouble(Symbol(), SYMBOL_POINT));
            else
                if(debugging) Print("Failed to place Buy Stop: ", trade.ResultRetcodeDescription());
        }

        // Place Sell Stop if LL_Buffer[0] is non-zero
        if (LL_Buffer[0] != 0.0)
        {
            double sell_stop = price_low - entry_gap * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            // double sl = sell_stop + (stop_loss + sl_gap) * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            double sl = price_high + sl_gap * SymbolInfoDouble(Symbol(), SYMBOL_POINT);
            double tp = sell_stop - (take_profit + tp_gap) * SymbolInfoDouble(Symbol(), SYMBOL_POINT);

            CancelPendingOrders(trade, ORDER_TYPE_BUY_STOP, Symbol(), debugging);
            bool placed = PlaceSellStop(trade, lot_size, sell_stop, Symbol(), sl, tp);
            if(debugging) Print("Sell Stop order placed at " + DoubleToString(sell_stop), debugging);
            Print("Sell Stop!", entry_gap);
            
            if (placed)
                if(debugging) Print("Sell Stop order placed at ", sell_stop, " TP: ", tp, " SL: ", sl, " | SymbolInfoDouble(Symbol(), SYMBOL_POINT): ", SymbolInfoDouble(Symbol(), SYMBOL_POINT));
            else
                if(debugging) Print("Failed to place Sell Stop: ", trade.ResultRetcodeDescription());
        }
    }
    else
    {
        if(debugging) Print("Open position exists for ", Symbol(), ", no new order placed.");
    }
   
   // Calculate dynamic TP/SL
   double dyn_tp, dyn_sl;
   if(CalculateDynamicTPSL(Symbol(), inputTimeframe, atr_val, dyn_tp_mul, dyn_sl_mul, dyn_tp, dyn_sl, debugging))
   {
       take_profit = dyn_tp;
       stop_loss = dyn_sl;
   }
//}