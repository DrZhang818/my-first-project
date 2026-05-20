#include "../Debug/debug.MultiTimeframeZone.mqh"
/**
 * @file MultiTimeframeCoordinator.mqh
 * @brief Bridges the three-level zone workflow (H4, M30, M15) and trading actions.
 */

#ifndef __THIVYAM_MULTI_TIMEFRAME_COORDINATOR_MQH__
#define __THIVYAM_MULTI_TIMEFRAME_COORDINATOR_MQH__

#include "NewBarDetector.mqh"
#include "../Risk/RiskManager.mqh"
#include "../Trading/OrderExecutor.mqh"
#include "../Zones/ZonePatternDetector.mqh"
#include "../Zones/ZoneRepository.mqh"

/**
 * Drives the multi-timeframe zone logic and executes trades once all confirmations align.
 */
class CMultiTimeframeCoordinator : public CObject
  {
private:
   string             m_symbol;
   CZoneRepository    m_repository;
   CRiskManager      *m_risk;
   COrderExecutor    *m_executor;
   ENUM_TIMEFRAMES    m_tfH4;
   ENUM_TIMEFRAMES    m_tfM30;
   ENUM_TIMEFRAMES    m_tfM15;

   bool               ZoneExists(const datetime anchor, const ENUM_ZONE_DIRECTION direction)
     {
      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *ctx = m_repository.At(i);
         if(ctx == NULL)
            continue;
         CZoneState *zone = ctx.Zone();
         if(zone.AnchorTime() == anchor && zone.Direction() == direction)
            return true;
        }
      return false;
     }

   void               HandleH4Breaks(const double closePrice)
     {
      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *ctx = m_repository.At(i);
         if(ctx == NULL)
            continue;

         CZoneState *zone = ctx.Zone();
             const bool  broken = zone.RegisterClose(closePrice);
             if(broken)
                {
                  if(zone.IsReversal())
                     {
                      ::LogEvent("H4: " + (zone.Direction() == ZONE_DIRECTION_BUY ? "Buy Zone reversed to Sell Reversal Zone" : "Sell Zone reversed to Buy Reversal Zone"));
                      zone.SetLabel("H4 Reversal");
                      zone.SetColor(zone.Direction() == ZONE_DIRECTION_BUY ? clrLime : clrTomato);
                      ctx.ResetMonitoring();
                      ctx.AttachChild(NULL);
                     }
                  else
                      if(!zone.IsActive())
                         {
                           ::LogEvent("H4: " + (zone.Direction() == ZONE_DIRECTION_BUY ? "Buy Zone broken" : "Sell Zone broken"));
                           CM30ZoneContext *m30child = ctx.Child();
                           if(m30child != NULL)
                              {
                               CM15ZoneContext *leaf = m30child.Child();
                               if(leaf != NULL)
                                  {
                                    // cancel any pending orders linked to the final M15 zone
                                    if(leaf.OrderPlaced())
                                        m_executor.CancelPending(leaf.Ticket());
                                  }
                              }
                         }
                }
         zone.Render();
        }

      m_repository.PurgeTerminated();
     }

   void               DetectNewH4Zones(MqlRates &rates[], const int count)
     {
      SZoneDefinition def;
      def.timeframe = m_tfH4;

         SZoneDefinition defBuy;
         defBuy.timeframe = m_tfH4;
         if(CZonePatternDetector::DetectLatest(rates, count, ZONE_DIRECTION_BUY, defBuy))
            {
             if(!ZoneExists(defBuy.anchorTime, ZONE_DIRECTION_BUY))
                {
                  ::LogEventPattern("H4: Regular Engulfing Buy pattern detected", defBuy.zoneHigh, defBuy.zoneLow, defBuy.anchorTime);
                  ::LogEventZone("H4: Regular Buy Zone created", defBuy.zoneHigh, defBuy.zoneLow);
                  defBuy.label = "H4 Buy";
                  defBuy.timeframe = m_tfH4;
                  CZoneState *state = new CZoneState(defBuy, clrLime);
                  CH4ZoneContext *ctx = new CH4ZoneContext(state);
                  state.Render();
                  m_repository.Add(ctx);
                }
            }

         SZoneDefinition defSell;
         defSell.timeframe = m_tfH4;
         if(CZonePatternDetector::DetectLatest(rates, count, ZONE_DIRECTION_SELL, defSell))
            {
             if(!ZoneExists(defSell.anchorTime, ZONE_DIRECTION_SELL))
                {
                  ::LogEventPattern("H4: Regular Engulfing Sell pattern detected", defSell.zoneHigh, defSell.zoneLow, defSell.anchorTime);
                  ::LogEventZone("H4: Regular Sell Zone created", defSell.zoneHigh, defSell.zoneLow);
                  defSell.label = "H4 Sell";
                  defSell.timeframe = m_tfH4;
                  CZoneState *state = new CZoneState(defSell, clrTomato);
                  CH4ZoneContext *ctx = new CH4ZoneContext(state);
                  state.Render();
                  m_repository.Add(ctx);
                }
            }
     }

   void               ProcessM30Breaks(const double closePrice)
     {
      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *h4 = m_repository.At(i);
         if(h4 == NULL)
            continue;
         CM30ZoneContext *m30 = h4.Child();
         if(m30 == NULL)
            continue;

         CZoneState *zone = m30.Zone();
         const bool  broken = zone.RegisterClose(closePrice);
         if(broken)
           {
            ::LogEvent("M30: " + (zone.Direction() == ZONE_DIRECTION_BUY ? "Buy Zone broken" : "Sell Zone broken"));
            zone.Terminate();
            CM15ZoneContext *m15child = m30.Child();
            if(m15child != NULL && m15child.OrderPlaced())
               m_executor.CancelPending(m15child.Ticket());
            h4.AttachChild(NULL);
            h4.DisableM30Search();
            ::LogEvent("M30: Zone deleted");
           }
        }
     }

   void               ActivateM30Monitoring(const double price)
     {
      const datetime nowTime = TimeCurrent();
      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *ctx = m_repository.At(i);
         if(ctx == NULL)
            continue;
         if(ctx.IsM30SearchDisabled())
            continue;

         CZoneState *zone = ctx.Zone();
         if(!zone.IsActive())
            continue;

         if(zone.ContainsPrice(price) && !ctx.IsMonitoringM30())
            ctx.BeginMonitoringM30(nowTime);

         zone.Render();
         CM30ZoneContext *child = ctx.Child();
         if(child != NULL)
           {
            CZoneState *childZone = child.Zone();
            childZone.Render();
            CM15ZoneContext *leaf = child.Child();
            if(leaf != NULL)
              {
               CZoneState *leafZone = leaf.Zone();
               leafZone.Render();
              }
           }
        }
     }

   void               ActivateM15Monitoring()
     {
      const double price = (SymbolInfoDouble(m_symbol, SYMBOL_BID) + SymbolInfoDouble(m_symbol, SYMBOL_ASK)) * 0.5;
      const datetime nowTime = TimeCurrent();

      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *h4 = m_repository.At(i);
         if(h4 == NULL)
            continue;
         CM30ZoneContext *m30 = h4.Child();
         if(m30 == NULL)
            continue;
         if(m30.IsM15SearchDisabled())
            continue;

         CZoneState *m30Zone = m30.Zone();
         if(m30Zone.ContainsPrice(price) && !m30.IsMonitoringM15())
            m30.BeginMonitoringM15(nowTime);
        }
     }

   void               DetectM30Zones(MqlRates &rates[], const int count)
     {
      const datetime barTime = rates[1].time;

      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *ctx = m_repository.At(i);
         if(ctx == NULL)
            continue;
         if(!ctx.ShouldMonitorM30(barTime))
            continue;
         if(ctx.IsM30SearchDisabled())
            continue;

         CZoneState *h4Zone = ctx.Zone();
         const ENUM_ZONE_DIRECTION direction = h4Zone.Direction();

             SZoneDefinition def;
             def.timeframe = m_tfM30;
             def.label     = direction == ZONE_DIRECTION_BUY ? "M30 Buy" : "M30 Sell";
             if(CZonePatternDetector::DetectLatest(rates, count, direction, def))
                {
                  ::LogEventPattern("M30: " + (direction == ZONE_DIRECTION_BUY ? "Regular pattern detected (Buy)" : "Regular pattern detected (Sell)"), def.zoneHigh, def.zoneLow, def.anchorTime);
                  ::LogEventZone("M30: " + (direction == ZONE_DIRECTION_BUY ? "Buy Zone created" : "Sell Zone created"), def.zoneHigh, def.zoneLow);
                  CZoneState *state = new CZoneState(def, direction == ZONE_DIRECTION_BUY ? clrGreen : clrRed);
                  CM30ZoneContext *child = new CM30ZoneContext(state);
                  ctx.AttachChild(child);
                  ctx.DisableM30Search();
                  state.Render();
                }
        }
     }

   void               DetectM15ZonesAndTrade(MqlRates &rates[], const int count)
     {
      const datetime barTime = rates[1].time;

      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *h4 = m_repository.At(i);
         if(h4 == NULL)
            continue;
         CM30ZoneContext *m30 = h4.Child();
         if(m30 == NULL)
            continue;
         if(!m30.ShouldMonitorM15(barTime) || m30.IsM15SearchDisabled())
            continue;

         CZoneState *h4Zone = h4.Zone();
         const ENUM_ZONE_DIRECTION direction = h4Zone.Direction();

             SZoneDefinition def;
             def.timeframe = m_tfM15;
             def.label     = direction == ZONE_DIRECTION_BUY ? "M15 Buy" : "M15 Sell";
             if(!CZonePatternDetector::DetectLatest(rates, count, direction, def))
                  continue;

            ::LogEventPattern("M15: " + (direction == ZONE_DIRECTION_BUY ? "Regular pattern detected (Buy)" : "Regular pattern detected (Sell)"), def.zoneHigh, def.zoneLow, def.anchorTime);
            ::LogEventZone("M15: " + (direction == ZONE_DIRECTION_BUY ? "Buy Zone created" : "Sell Zone created"), def.zoneHigh, def.zoneLow);

             CZoneState *state = new CZoneState(def, direction == ZONE_DIRECTION_BUY ? clrChartreuse : clrSalmon);
             CM15ZoneContext *leaf = new CM15ZoneContext(state);
             m30.AttachChild(leaf);
             m30.DisableM15Search();
             state.Render();

             const bool isBuy = (direction == ZONE_DIRECTION_BUY);
             const double entryPrice = isBuy ? state.High() : state.Low();

             double stopPrice = 0.0;
             double stopPips  = 0.0;
             bool slOk = false;
             ::LogEvent(stopPrice);
             if(m_risk.Config().stopModel == STOP_MODEL_STRATEGY_SL)
                {
                  // For StrategySL, pass zoneHigh/zoneLow for correct SL placement
                  slOk = m_risk.CalculateStopLoss(entryPrice, isBuy, stopPrice, stopPips, state.High(), state.Low());
                }
             else
                {
                  slOk = m_risk.CalculateStopLoss(entryPrice, isBuy, stopPrice, stopPips);
                }
             if(!slOk)
                {
                  ::LogEvent("Risk: Failed to compute stop-loss");
                  continue;
                }
             ::LogEvent(stopPrice);

             double takeProfit = 0.0;
             if(!m_risk.CalculateTakeProfit(entryPrice, isBuy, stopPips, takeProfit))
                {
                  ::LogEvent("Risk: Failed to compute take-profit");
                  continue;
                }

             ::LogEventTrade("M15: SL/TP calculated", entryPrice, stopPrice, takeProfit);

             const double lots = m_risk.CalculatePositionSize(stopPips);
             if(lots <= 0.0)
                {
                  ::LogEvent("Risk: Lot size <= 0.0, trade skipped");
                  continue;
                }

             const double ask = SymbolInfoDouble(m_symbol, SYMBOL_ASK);
             const double bid = SymbolInfoDouble(m_symbol, SYMBOL_BID);
             const double currentPrice = isBuy ? ask : bid;
             if(isBuy && entryPrice >= currentPrice)
                {
                  ::LogEvent("Trade: Buy limit price must be below current ask, trade skipped");
                  continue;
                }
             if(!isBuy && entryPrice <= currentPrice)
                {
                  ::LogEvent("Trade: Sell limit price must be above current bid, trade skipped");
                  continue;
                }

             ulong ticket = 0;
             if(m_executor.PlaceLimit(isBuy, entryPrice, stopPrice, takeProfit, lots, def.label, ticket))
                {
                  ::LogEventTrade("M15: Trade placed", entryPrice, stopPrice, takeProfit);
                  leaf.MarkOrderPlaced(ticket);
                }
        }
     }

public:
                     CMultiTimeframeCoordinator()
     {
      m_symbol = _Symbol;
      m_risk   = NULL;
      m_executor = NULL;
      m_tfH4  = PERIOD_H4;
      m_tfM30 = PERIOD_M30;
      m_tfM15 = PERIOD_M15;
     }

   /**
    * Initialises the coordinator.
    * @param symbol Trading symbol to operate on.
    * @param risk Reference to the risk manager instance.
    * @param executor Reference to the order executor.
    */
   void              Initialise(const string symbol, CRiskManager &risk, COrderExecutor &executor)
     {
      m_symbol  = symbol;
      m_risk    = &risk;
      m_executor= &executor;
     }

   /** Processes a newly closed H4 candle. */
   void              OnNewBarH4()
     {
      MqlRates rates[];
      ArraySetAsSeries(rates, true);
      const int copied = CopyRates(m_symbol, m_tfH4, 0, 64, rates);
      if(copied < 4)
         return;

      HandleH4Breaks(rates[1].close);
      DetectNewH4Zones(rates, copied);
     }

   /** Processes a newly closed M30 candle. */
   void              OnNewBarM30()
     {
      MqlRates rates[];
      ArraySetAsSeries(rates, true);
      const int copied = CopyRates(m_symbol, m_tfM30, 0, 96, rates);
      if(copied < 4)
         return;

      ProcessM30Breaks(rates[1].close);
      DetectM30Zones(rates, copied);
     }

   /** Processes a newly closed M15 candle and triggers trade placement. */
   void              OnNewBarM15()
     {
      MqlRates rates[];
      ArraySetAsSeries(rates, true);
      const int copied = CopyRates(m_symbol, m_tfM15, 0, 128, rates);
      if(copied < 4)
         return;

      DetectM15ZonesAndTrade(rates, copied);
     }

   /**
    * Updates per tick logic (price-in-zone monitoring and chart rendering).
    */
   void              OnTick()
     {
      const double mid = (SymbolInfoDouble(m_symbol, SYMBOL_BID) + SymbolInfoDouble(m_symbol, SYMBOL_ASK)) * 0.5;
      ActivateM30Monitoring(mid);
      ActivateM15Monitoring();
     }

   /**
    * Converts repository state into readable strings for the UI panel.
    * @param[out] info Aggregated description of active zones.
    */
   void              Describe(string &info)
     {
      info = "";
      for(int i = 0; i < m_repository.Total(); ++i)
        {
         CH4ZoneContext *ctx = m_repository.At(i);
         if(ctx == NULL)
            continue;
         CZoneState *zone = ctx.Zone();
         info += StringFormat("H4 %s (%.5f/%.5f)\n",
                              zone.Direction() == ZONE_DIRECTION_BUY ? "Buy" : "Sell",
                              zone.High(), zone.Low());
        }
     }
  };

#endif // __THIVYAM_MULTI_TIMEFRAME_COORDINATOR_MQH__
