/**
 * @file ZonePatternDetector.mqh
 * @brief Implements engulfing-pattern detection for multi-candle configurations.
 */

#ifndef __THIVYAM_ZONE_PATTERN_DETECTOR_MQH__
#define __THIVYAM_ZONE_PATTERN_DETECTOR_MQH__

#include "ZoneTypes.mqh"

/**
 * Provides static helper functions to detect engulfing patterns.
 */
class CZonePatternDetector
  {
public:
   /**
    * Scans the supplied price arrays for the first matching pattern.
    * @param rates Array of rates (chronological order, index 0 = most recent).
    * @param count Number of elements available in the array.
    * @param direction Desired zone direction (buy/sell).
    * @param[out] definition Populated zone definition when a pattern is found.
    * @return true when a matching pattern is identified.
    */
  static bool        Detect(MqlRates &rates[],
                             const int       count,
                             const ENUM_ZONE_DIRECTION direction,
                             SZoneDefinition &definition)
     {
      if(count < 4)
         return false;

      for(int i = 2; i < count; ++i)
        {
         if(direction == ZONE_DIRECTION_BUY)
           {
            if(IsRegularBullish(rates, i, i-1))
              {
               PopulateDefinition(rates, i, direction, PATTERN_REGULAR, definition);
               return true;
              }
            if(IsIrregularBullish(rates, i))
              {
               PopulateDefinition(rates, i, direction, PATTERN_IRREGULAR, definition);
               return true;
              }
           }
         else
           {
            if(IsRegularBearish(rates, i, i-1))
              {
               PopulateDefinition(rates, i, direction, PATTERN_REGULAR, definition);
               return true;
              }
            if(IsIrregularBearish(rates, i))
              {
               PopulateDefinition(rates, i, direction, PATTERN_IRREGULAR, definition);
               return true;
              }
           }
        }

      return false;
     }

   /**
    * Evaluates only the most recently closed candle for a matching pattern.
    * @param rates Array of rates with index 0 representing the current (forming) bar.
    * @param count Number of elements in the array.
    * @param direction Desired zone direction.
    * @param[out] definition Zone definition initialised when a match is found.
    * @return true when the latest closed bar completes a valid pattern.
    */
  static bool        DetectLatest(MqlRates &rates[],
                                   const int       count,
                                   const ENUM_ZONE_DIRECTION direction,
                                   SZoneDefinition &definition)
     {
      if(count < 4)
         return false;

      int anchorIndex = -1;
      ENUM_ENGULFING_PATTERN pattern = PATTERN_NONE;

      if(direction == ZONE_DIRECTION_BUY)
        {
         if(IsRegularBullish(rates, 2, 1))
           {
            anchorIndex = 2;
            pattern     = PATTERN_REGULAR;
           }
         else
           {
            anchorIndex = FindIrregularBullishLatest(rates, count);
            if(anchorIndex != -1)
               pattern = PATTERN_IRREGULAR;
           }
        }
      else
        {
         if(IsRegularBearish(rates, 2, 1))
           {
            anchorIndex = 2;
            pattern     = PATTERN_REGULAR;
           }
         else
           {
            anchorIndex = FindIrregularBearishLatest(rates, count);
            if(anchorIndex != -1)
               pattern = PATTERN_IRREGULAR;
           }
        }

      if(anchorIndex == -1 || pattern == PATTERN_NONE)
         return false;

      PopulateDefinition(rates, anchorIndex, direction, pattern, definition);
      return true;
     }

private:
  static void        PopulateDefinition(MqlRates &rates[],
                                         const int anchorIndex,
                                         const ENUM_ZONE_DIRECTION direction,
                                         const ENUM_ENGULFING_PATTERN pattern,
                                         SZoneDefinition &definition)
     {
      definition.direction = direction;
      definition.pattern   = pattern;
      definition.zoneHigh  = rates[anchorIndex].high;
      definition.zoneLow   = rates[anchorIndex].low;
      definition.anchorTime= rates[anchorIndex].time;
     }

  static bool        IsRegularBullish(MqlRates &rates[], const int bearishIndex, const int bullishIndex)
     {
      return (rates[bearishIndex].close < rates[bearishIndex].open &&
              rates[bullishIndex].close > rates[bullishIndex].open &&
              rates[bullishIndex].close > rates[bearishIndex].high);
     }

  static bool        IsRegularBearish(MqlRates &rates[], const int bullishIndex, const int bearishIndex)
     {
      return (rates[bullishIndex].close > rates[bullishIndex].open &&
              rates[bearishIndex].close < rates[bearishIndex].open &&
              rates[bearishIndex].close < rates[bullishIndex].low);
     }

  static bool        IsIrregularBullish(MqlRates &rates[], const int index)
     {
      if(index < 3)
         return false;

      if(rates[index].close >= rates[index].open)
         return false;

      bool allBullish = true;
      bool engulfed   = false;
      for(int i = index-1; i >= 1; --i)
        {
         if(rates[i].close <= rates[i].open)
           {
            allBullish = false;
            break;
           }
         if(rates[i].close > rates[index].high)
            engulfed = true;
        }
      return allBullish && engulfed;
     }

  static bool        IsIrregularBearish(MqlRates &rates[], const int index)
     {
      if(index < 3)
         return false;

      if(rates[index].close <= rates[index].open)
         return false;

      bool allBearish = true;
      bool engulfed   = false;
      for(int i = index-1; i >= 1; --i)
        {
         if(rates[i].close >= rates[i].open)
           {
            allBearish = false;
            break;
           }
         if(rates[i].close < rates[index].low)
            engulfed = true;
        }
      return allBearish && engulfed;
     }

  static int         FindIrregularBullishLatest(MqlRates &rates[], const int count)
     {
      if(rates[1].close <= rates[1].open)
         return -1;

      int startIdx = -1;
      for(int i = 2; i < count; ++i)
        {
         if(rates[i].close < rates[i].open)
           {
            startIdx = i;
            break;
           }
         if(rates[i].close <= rates[i].open)
            return -1;
        }

      if(startIdx == -1)
         return -1;

      bool engulfed = false;
      for(int i = 1; i < startIdx; ++i)
        {
         if(rates[i].close <= rates[i].open)
            return -1;
         if(rates[i].close > rates[startIdx].high)
            engulfed = true;
        }

      return engulfed ? startIdx : -1;
     }

  static int         FindIrregularBearishLatest(MqlRates &rates[], const int count)
     {
      if(rates[1].close >= rates[1].open)
         return -1;

      int startIdx = -1;
      for(int i = 2; i < count; ++i)
        {
         if(rates[i].close > rates[i].open)
           {
            startIdx = i;
            break;
           }
         if(rates[i].close >= rates[i].open)
            return -1;
        }

      if(startIdx == -1)
         return -1;

      bool engulfed = false;
      for(int i = 1; i < startIdx; ++i)
        {
         if(rates[i].close >= rates[i].open)
            return -1;
         if(rates[i].close < rates[startIdx].low)
            engulfed = true;
        }

      return engulfed ? startIdx : -1;
     }
  };

#endif // __THIVYAM_ZONE_PATTERN_DETECTOR_MQH__
