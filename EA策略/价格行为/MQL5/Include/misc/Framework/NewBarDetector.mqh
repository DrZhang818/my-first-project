/**
 * @file NewBarDetector.mqh
 * @brief Provides utilities to detect new bar events reliably across timeframes.
 */

#ifndef __THIVYAM_NEWBAR_DETECTOR_MQH__
#define __THIVYAM_NEWBAR_DETECTOR_MQH__

#include <Object.mqh>

/**
 * Helper class that tracks candle timestamps for a timeframe and reports new bar events.
 */
class CNewBarDetector : public CObject
  {
private:
   ENUM_TIMEFRAMES   m_timeframe;   ///< Target timeframe to watch.
   datetime          m_lastBarTime; ///< Cached open time of the most recent bar.
   string            m_symbol;      ///< Symbol for the requested series.

public:
                     CNewBarDetector()
     {
      Configure(_Symbol, PERIOD_CURRENT);
     }

                     CNewBarDetector(const string symbol, const ENUM_TIMEFRAMES timeframe)
     {
      m_symbol      = symbol;
      m_timeframe   = timeframe;
      m_lastBarTime = 0;
     }

   /**
    * Sets the symbol and timeframe that will be monitored.
    * @param symbol Trading symbol (defaults to chart symbol).
    * @param timeframe Timeframe to track.
    */
   void              Configure(const string symbol, const ENUM_TIMEFRAMES timeframe)
     {
      m_symbol      = symbol;
      m_timeframe   = timeframe;
      m_lastBarTime = 0;
     }

   /**
    * Evaluates whether a new bar has appeared for the configured timeframe.
    * @return true when a new closed bar is available; otherwise false.
    */
   bool              Check()
     {
      datetime times[2];
      if(CopyTime(m_symbol, m_timeframe, 0, 2, times) != 2)
         return false;

      if(m_lastBarTime == 0)
        {
         m_lastBarTime = times[1];
         return true;
        }

      if(times[1] != m_lastBarTime)
        {
         m_lastBarTime = times[1];
         return true;
        }

      return false;
     }
  };

#endif // __THIVYAM_NEWBAR_DETECTOR_MQH__
