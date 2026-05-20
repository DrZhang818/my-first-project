/**
 * @file RiskManager.mqh
 * @brief Implements dynamic risk-position sizing and stop/target calculations.
 */

#ifndef __THIVYAM_RISK_MANAGER_MQH__
#define __THIVYAM_RISK_MANAGER_MQH__

#include <Trade\Trade.mqh>

#include "..\\Framework\\SymbolMath.mqh"

/** Enumerates the supported position sizing models. */
enum ENUM_RISK_MODEL
  {
   RISK_MODEL_PERCENT_EQUITY = 0,
   RISK_MODEL_FIXED_LOT      = 1,
   RISK_MODEL_FIXED_CASH     = 2
  };

/** Enumerates the supported stop-loss derivation models. */
enum ENUM_STOP_MODEL
   {
    STOP_MODEL_FIXED_PIPS = 0,
    STOP_MODEL_ATR        = 1,
    STOP_MODEL_STRATEGY_SL = 2
   };

/** Enumerates the supported take-profit derivation models. */
enum ENUM_TP_MODEL
  {
   TP_MODEL_FIXED_PIPS = 0,
   TP_MODEL_RR_RATIO   = 1,
   TP_MODEL_ATR        = 2
  };

/**
 * Bundles user-configurable risk parameters for easier initialisation.
 */
struct SRiskConfig
  {
   ENUM_RISK_MODEL   riskModel;
   double            percentRisk;
   double            fixedLot;
   double            fixedCash;
   ENUM_STOP_MODEL   stopModel;
   double            stopPips;
   int               stopAtrPeriod;
   double            stopAtrMultiplier;
   double            stopSlBuffer;
   ENUM_TP_MODEL     tpModel;
   double            tpPips;
   double            rewardRiskRatio;
   int               tpAtrPeriod;
   double            tpAtrMultiplier;
   ENUM_TIMEFRAMES   atrTimeframe;

                     SRiskConfig()
     {
      riskModel         = RISK_MODEL_PERCENT_EQUITY;
      percentRisk       = 0.5;
      fixedLot          = 0.01;
      fixedCash         = 1000.0;
      stopModel         = STOP_MODEL_FIXED_PIPS;
      stopPips          = 30.0;
      stopAtrPeriod     = 12;
      stopAtrMultiplier = 1.5;
      stopSlBuffer      = 5.0;
      tpModel           = TP_MODEL_FIXED_PIPS;
      tpPips            = 30.0;
      rewardRiskRatio   = 2.0;
      tpAtrPeriod       = 12;
      tpAtrMultiplier   = 2.0;
      atrTimeframe      = PERIOD_M15;
     }
  };

/**
 * Centralises risk sizing and SL/TP derivation according to the requested models.
 */
class CRiskManager : public CObject
  {
private:
   string            m_symbol;
   SRiskConfig       m_config;
   int               m_atrStopHandle;
   int               m_atrTpHandle;

   double            GetLatestAtrValue(const int handle)
     {
      if(handle == INVALID_HANDLE)
         return 0.0;

      double atr[1];
      if(CopyBuffer(handle, 0, 1, 1, atr) != 1)
         return 0.0;

      return atr[0];
     }

public:
                     CRiskManager()
     {
      m_symbol        = _Symbol;
      m_atrStopHandle = INVALID_HANDLE;
      m_atrTpHandle   = INVALID_HANDLE;
     }

   /**
    * Configures the risk manager and provisions indicator handles where required.
    * @param symbol Trading symbol that positions will be executed on.
    * @param config Set of user-supplied risk parameters.
    * @return true on success; otherwise false.
    */
   bool              Initialise(const string symbol, const SRiskConfig &config)
     {
      m_symbol = symbol;
      m_config = config;

      if(m_atrStopHandle != INVALID_HANDLE)
         IndicatorRelease(m_atrStopHandle);
      if(m_atrTpHandle != INVALID_HANDLE)
         IndicatorRelease(m_atrTpHandle);

      m_atrStopHandle = (m_config.stopModel == STOP_MODEL_ATR)
                        ? iATR(m_symbol, m_config.atrTimeframe, m_config.stopAtrPeriod)
                        : INVALID_HANDLE;

      m_atrTpHandle   = (m_config.tpModel == TP_MODEL_ATR)
                        ? iATR(m_symbol, m_config.atrTimeframe, m_config.tpAtrPeriod)
                        : INVALID_HANDLE;

      const bool atrStopOk = (m_config.stopModel == STOP_MODEL_ATR) ? (m_atrStopHandle != INVALID_HANDLE) : true;
      const bool atrTpOk   = (m_config.tpModel == TP_MODEL_ATR) ? (m_atrTpHandle != INVALID_HANDLE) : true;
      return atrStopOk && atrTpOk;
     }

   /**
    * Releases any indicator handles owned by the class.
    */
   void              Shutdown()
     {
      if(m_atrStopHandle != INVALID_HANDLE)
         IndicatorRelease(m_atrStopHandle);
      if(m_atrTpHandle != INVALID_HANDLE)
         IndicatorRelease(m_atrTpHandle);
      m_atrStopHandle = INVALID_HANDLE;
      m_atrTpHandle   = INVALID_HANDLE;
     }

   /**
    * Determines the stop-loss price and the underlying pip distance.
    * @param entryPrice Planned entry price for the order.
    * @param isBuy true for long trades, false for shorts.
    * @param[out] stopPrice Resulting stop price.
    * @param[out] stopLossPips Resulting pip distance (absolute value).
    * @return true when the computation succeeds.
    */
   bool              CalculateStopLoss(const double entryPrice,
                                       const bool   isBuy,
                                       double      &stopPrice,
                                       double      &stopLossPips,
                                       double      zoneHigh = 0.0,
                                       double      zoneLow = 0.0)
     {
         double distancePips = 0.0;
         if(m_config.stopModel == STOP_MODEL_FIXED_PIPS)
             distancePips = m_config.stopPips;
         else if(m_config.stopModel == STOP_MODEL_ATR)
            {
             const double atr = GetLatestAtrValue(m_atrStopHandle);
             if(atr <= 0.0)
                  return false;
             distancePips = CSymbolMath::PriceToPips(m_symbol, atr * m_config.stopAtrMultiplier);
            }
         else if(m_config.stopModel == STOP_MODEL_STRATEGY_SL)
            {
             // StrategySL: SL = Low of M15 zone - SlBuffer (Buy), High of M15 zone + SlBuffer (Sell)
             if(isBuy)
                {
                  stopPrice = zoneLow - CSymbolMath::PipsToPrice(m_symbol, m_config.stopSlBuffer);
                  distancePips = CSymbolMath::PriceToPips(m_symbol, entryPrice - stopPrice);
                }
             else
                {
                  stopPrice = zoneHigh + CSymbolMath::PipsToPrice(m_symbol, m_config.stopSlBuffer);
                  distancePips = CSymbolMath::PriceToPips(m_symbol, stopPrice - entryPrice);
                }
             stopLossPips = distancePips;
             return true;
            }

         if(distancePips <= 0.0)
             return false;

         const double priceDistance = CSymbolMath::PipsToPrice(m_symbol, distancePips);
         stopPrice     = isBuy ? entryPrice - priceDistance : entryPrice + priceDistance;
         // Always apply SL buffer
         if(isBuy)
             stopPrice -= CSymbolMath::PipsToPrice(m_symbol, m_config.stopSlBuffer);
         else
             stopPrice += CSymbolMath::PipsToPrice(m_symbol, m_config.stopSlBuffer);
         stopLossPips  = CSymbolMath::PriceToPips(m_symbol, MathAbs(entryPrice - stopPrice));
         return true;
     }

   /**
    * Determines the take-profit price given the computed stop-loss distance.
    * @param entryPrice Planned entry price for the order.
    * @param isBuy true for long trades, false for shorts.
    * @param stopLossPips Absolute pip distance used for the stop-loss.
    * @param[out] takeProfitPrice Resulting TP price.
    * @return true when the computation succeeds.
    */
   bool              CalculateTakeProfit(const double entryPrice,
                                         const bool   isBuy,
                                         const double stopLossPips,
                                         double      &takeProfitPrice)
     {
      double targetPips = 0.0;
      switch(m_config.tpModel)
        {
         case TP_MODEL_FIXED_PIPS:
            targetPips = m_config.tpPips;
            break;
         case TP_MODEL_RR_RATIO:
            targetPips = stopLossPips * m_config.rewardRiskRatio;
            break;
         case TP_MODEL_ATR:
           {
            const double atr = GetLatestAtrValue(m_atrTpHandle);
            if(atr <= 0.0)
               return false;
            targetPips = CSymbolMath::PriceToPips(m_symbol, atr * m_config.tpAtrMultiplier);
           }
         break;
        }

      if(targetPips <= 0.0)
         return false;

      const double priceDistance = CSymbolMath::PipsToPrice(m_symbol, targetPips);
      takeProfitPrice = isBuy ? entryPrice + priceDistance : entryPrice - priceDistance;
      return true;
     }

   /**
    * Calculates the position size in lots according to the configured risk profile.
    * @param stopLossPips Absolute pip distance between entry and stop.
    * @return Suggested lot size (broker-normalised).
    */
   double            CalculatePositionSize(const double stopLossPips)
     {
      if(stopLossPips <= 0.0)
         return 0.0;

      switch(m_config.riskModel)
        {
         case RISK_MODEL_FIXED_LOT:
            return CSymbolMath::NormalizeLots(m_symbol, m_config.fixedLot);

         case RISK_MODEL_FIXED_CASH:
           {
            const double tickValue = SymbolInfoDouble(m_symbol, SYMBOL_TRADE_TICK_VALUE);
            const double tickSize  = SymbolInfoDouble(m_symbol, SYMBOL_TRADE_TICK_SIZE);
            if(tickValue <= 0.0 || tickSize <= 0.0)
               return 0.0;
            const double priceDistance = CSymbolMath::PipsToPrice(m_symbol, stopLossPips);
            const double riskPerLot    = priceDistance / tickSize * tickValue;
            if(riskPerLot <= 0.0)
               return 0.0;
            const double lots = m_config.fixedCash / riskPerLot;
            return CSymbolMath::NormalizeLots(m_symbol, lots);
           }

         case RISK_MODEL_PERCENT_EQUITY:
         default:
           {
            const double equity        = AccountInfoDouble(ACCOUNT_EQUITY);
            const double cashRisk      = equity * m_config.percentRisk / 100.0;
            const double tickValue     = SymbolInfoDouble(m_symbol, SYMBOL_TRADE_TICK_VALUE);
            const double tickSize      = SymbolInfoDouble(m_symbol, SYMBOL_TRADE_TICK_SIZE);
            if(tickValue <= 0.0 || tickSize <= 0.0)
               return 0.0;
            const double priceDistance = CSymbolMath::PipsToPrice(m_symbol, stopLossPips);
            const double riskPerLot    = priceDistance / tickSize * tickValue;
            if(riskPerLot <= 0.0)
               return 0.0;
            const double lots          = cashRisk / riskPerLot;
            return CSymbolMath::NormalizeLots(m_symbol, lots);
           }
        }
     }

   /**
    * Exposes the active configuration.
    */
   SRiskConfig       Config()
     {
      return m_config;
     }
  };

#endif // __THIVYAM_RISK_MANAGER_MQH__
