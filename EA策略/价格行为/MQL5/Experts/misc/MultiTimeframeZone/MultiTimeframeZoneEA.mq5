//+------------------------------------------------------------------+
//|                                             MultiTimeframeZoneEA |
//|                                                    bill |
//|                                     bill |
//|                                                   Version: v1.11 |
//+------------------------------------------------------------------+
#define EA_VERSION "v1.11"
#property strict

#include <Trade\Trade.mqh>

#include "..\\..\\..\\Include\\misc\\Framework\\NewBarDetector.mqh"
#include "..\\..\\..\\Include\\misc\\Framework\\MultiTimeframeCoordinator.mqh"
#include "..\\..\\..\\Include\\misc\\Framework\\SymbolMath.mqh"
#include "..\\..\\..\\Include\\misc\\Risk\\RiskManager.mqh"
#include "..\\..\\..\\Include\\misc\\Trading\\OrderExecutor.mqh"
#include "..\\..\\..\\Include\\misc\\UI\\InfoPanel.mqh"
#include "../../../Include/misc/Debug/debug.MultiTimeframeZone.mqh"

//--- input parameters
input ulong            InpMagicNumber        = 50015001;
input ENUM_RISK_MODEL  InpRiskModel          = RISK_MODEL_PERCENT_EQUITY;
input double           InpPercentRisk        = 0.5;
input double           InpFixedLotSize       = 0.10;
input double           InpFixedCashRisk      = 1000.0;
input ENUM_STOP_MODEL  InpStopModel          = STOP_MODEL_STRATEGY_SL;
input double           InpStopLossPips       = 30.0;
input int              InpStopAtrPeriod      = 12;
input double           InpStopAtrMultiplier  = 1.5;
input double           InpSlBuffer           = 5.0;
input ENUM_TP_MODEL    InpTpModel            = TP_MODEL_FIXED_PIPS;
input double           InpTpPips             = 30.0;
input double           InpRewardRiskRatio    = 2.0;
input int              InpTpAtrPeriod        = 12;
input double           InpTpAtrMultiplier    = 2.0;
input ENUM_TIMEFRAMES  InpAtrTimeframe       = PERIOD_M15;
input bool             InpShowPanel          = true;
input ENUM_BASE_CORNER InpPanelCorner        = CORNER_LEFT_UPPER;
input int              InpPanelXOffset       = 10;
input int              InpPanelYOffset       = 30;
input color            InpPanelBgColor       = clrDarkSlateGray;
input color            InpPanelTextColor     = clrWhite;
input color            InpPanelBorderColor   = clrSteelBlue;
input bool               InpEnableEventLog     = true; // Enable event logging
//+------------------------------------------------------------------+
//| Event logging helper                                             |
//+------------------------------------------------------------------+
// Logging helpers now included from DebugHelpers.mqh

//--- module instances
CRiskManager                g_riskManager;
COrderExecutor              g_orderExecutor;
CMultiTimeframeCoordinator  g_coordinator;
CNewBarDetector             g_h4Detector;
CNewBarDetector             g_m30Detector;
CNewBarDetector             g_m15Detector;
CInfoPanel                  g_panel;

/**
 * Formats a list of current positions associated with this EA.
 * @return Multi-line string describing active trades.
 */
string DescribePositions()
  {
   string summary = "None";
   int total = PositionsTotal();
   int i;
   for(i = 0; i < total; i++)
     {
      ulong ticket = PositionGetTicket(i);
      if(ticket == 0)
         continue;
      if(PositionGetInteger(POSITION_MAGIC) != (long)InpMagicNumber)
         continue;
      if(summary == "None")
         summary = "";
      summary += StringFormat("%s %.2f @ %.5f\n",
                              PositionGetInteger(POSITION_TYPE) == POSITION_TYPE_BUY ? "BUY" : "SELL",
                              PositionGetDouble(POSITION_VOLUME),
                              PositionGetDouble(POSITION_PRICE_OPEN));
     }
   return summary;
  }

/**
 * Calculates today's profit and loss in account currency.
 * @return Summed profit for the current day.
 */
double CalculateDailyPnL()
  {
   datetime now      = TimeCurrent();
   string   dateText = TimeToString(now, TIME_DATE);
   datetime dayStart = StringToTime(dateText + " 00:00");
   if(!HistorySelect(dayStart, now))
      return 0.0;

   double profit = 0.0;
   int deals = HistoryDealsTotal();
   int i;
   for(i = 0; i < deals; i++)
     {
      ulong ticket = HistoryDealGetTicket(i);
      if(ticket == 0)
         continue;
      if((ulong)HistoryDealGetInteger(ticket, DEAL_MAGIC) != InpMagicNumber)
         continue;
      profit += HistoryDealGetDouble(ticket, DEAL_PROFIT);
      profit += HistoryDealGetDouble(ticket, DEAL_SWAP);
      profit += HistoryDealGetDouble(ticket, DEAL_COMMISSION);
     }
   return profit;
  }

/**
 * Composes the status text for the information panel.
 */
string BuildPanelText()
  {
   const double bid        = SymbolInfoDouble(_Symbol, SYMBOL_BID);
   const double ask        = SymbolInfoDouble(_Symbol, SYMBOL_ASK);
   const double spreadPips = CSymbolMath::PriceToPips(_Symbol, ask - bid);

   string zonesText;
   g_coordinator.Describe(zonesText);

   string text;
   text += StringFormat("Spread: %.1f pips\n", spreadPips);
   text += StringFormat("Equity: %.2f\n", AccountInfoDouble(ACCOUNT_EQUITY));
   text += StringFormat("Balance: %.2f\n", AccountInfoDouble(ACCOUNT_BALANCE));
   text += StringFormat("Day P/L: %.2f\n", CalculateDailyPnL());
   text += "Trades:\n" + DescribePositions();
   if(zonesText != "")
      text += "Zones:\n" + zonesText;
   return text;
  }

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
int OnInit()
  {
   g_h4Detector.Configure(_Symbol, PERIOD_H4);
   g_m30Detector.Configure(_Symbol, PERIOD_M30);
   g_m15Detector.Configure(_Symbol, PERIOD_M15);

   SRiskConfig cfg;
   cfg.riskModel         = InpRiskModel;
   cfg.percentRisk       = InpPercentRisk;
   cfg.fixedLot          = InpFixedLotSize;
   cfg.fixedCash         = InpFixedCashRisk;
   cfg.stopModel         = InpStopModel;
   cfg.stopPips          = InpStopLossPips;
   cfg.stopAtrPeriod     = InpStopAtrPeriod;
   cfg.stopAtrMultiplier = InpStopAtrMultiplier;
   cfg.stopSlBuffer      = InpStopSlBuffer;
   cfg.tpModel           = InpTpModel;
   cfg.tpPips            = InpTpPips;
   cfg.rewardRiskRatio   = InpRewardRiskRatio;
   cfg.tpAtrPeriod       = InpTpAtrPeriod;
   cfg.tpAtrMultiplier   = InpTpAtrMultiplier;
   cfg.atrTimeframe      = InpAtrTimeframe;

   if(!g_riskManager.Initialise(_Symbol, cfg))
     {
      Print(__FUNCTION__, ": Failed to initialise risk manager");
      return INIT_FAILED;
     }

   g_orderExecutor.Configure(_Symbol, InpMagicNumber);
   g_coordinator.Initialise(_Symbol, g_riskManager, g_orderExecutor);

   g_panel.Configure(InpShowPanel, StringFormat("MTZ_%I64d", ChartID()), InpPanelCorner, 
                     InpPanelXOffset, InpPanelYOffset, InpPanelBgColor, InpPanelTextColor, InpPanelBorderColor);

   return INIT_SUCCEEDED;
  }

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
   g_panel.Destroy();
   g_riskManager.Shutdown();
  }

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void OnTick()
  {
   if(g_h4Detector.Check())
      g_coordinator.OnNewBarH4();
   if(g_m30Detector.Check())
      g_coordinator.OnNewBarM30();
   if(g_m15Detector.Check())
      g_coordinator.OnNewBarM15();

   g_coordinator.OnTick();

   g_panel.Update(BuildPanelText());
  }

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
void OnChartEvent(const int id, const long &lparam, const double &dparam, const string &sparam)
  {
   g_panel.OnChartEvent(id, lparam, dparam, sparam);
  }
//+------------------------------------------------------------------+
