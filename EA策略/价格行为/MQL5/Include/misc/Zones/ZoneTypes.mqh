/**
 * @file ZoneTypes.mqh
 * @brief Common data structures and enumerations for supply/demand zone handling.
 */

#ifndef __THIVYAM_ZONE_TYPES_MQH__
#define __THIVYAM_ZONE_TYPES_MQH__

#include <Object.mqh>

/** Direction of the zone or trading bias. */
enum ENUM_ZONE_DIRECTION
  {
   ZONE_DIRECTION_BUY  = 1,
   ZONE_DIRECTION_SELL = -1
  };

/** Stage in the lifecycle of a zone. */
enum ENUM_ZONE_PHASE
  {
   ZONE_PHASE_ACTIVE = 0,
   ZONE_PHASE_REVERSAL,
   ZONE_PHASE_TERMINATED
  };

/** Classification of the detected engulfing pattern. */
enum ENUM_ENGULFING_PATTERN
  {
   PATTERN_NONE = 0,
   PATTERN_REGULAR,
   PATTERN_IRREGULAR
  };

/**
 * Represents the key attributes of a zone.
 */
struct SZoneDefinition
  {
   ENUM_TIMEFRAMES     timeframe;
   ENUM_ZONE_DIRECTION direction;
   ENUM_ENGULFING_PATTERN pattern;
   double              zoneHigh;
   double              zoneLow;
   datetime            anchorTime;
   string              label;

                     SZoneDefinition()
     {
      timeframe = PERIOD_CURRENT;
      direction = ZONE_DIRECTION_BUY;
      pattern   = PATTERN_NONE;
      zoneHigh  = 0.0;
      zoneLow   = 0.0;
      anchorTime= 0;
     }
  };

/**
 * Holds runtime metadata for a zone instance.
 */
class CZoneState : public CObject
  {
private:
   SZoneDefinition    m_def;
   ENUM_ZONE_PHASE    m_phase;
   int                m_breakCount;
   string             m_rectName;
   color              m_color;
   bool               m_visible;

public:
                     CZoneState(const SZoneDefinition &definition,
              const color           displayColor,
              const bool            isVisible = true)
     {
      m_def        = definition;
      m_phase      = ZONE_PHASE_ACTIVE;
      m_breakCount = 0;
      m_color      = displayColor;
      m_visible    = isVisible;
      m_rectName   = StringFormat("Zone_%s_%d_%I64d", EnumToString(m_def.timeframe), m_def.direction, m_def.anchorTime);
     }

                    ~CZoneState()
     {
      ObjectDelete(0, m_rectName);
     }

   /** Returns the underlying definition. */
   SZoneDefinition    Definition() { return m_def; }

   /** Returns the object name used on the chart. */
   string             ObjectName() { return m_rectName; }
   datetime           AnchorTime() { return m_def.anchorTime; }
   ENUM_ZONE_DIRECTION Direction() { return m_def.direction; }
   ENUM_TIMEFRAMES    Timeframe() { return m_def.timeframe; }
   double             High() { return m_def.zoneHigh; }
   double             Low() { return m_def.zoneLow; }

   /** Updates the chart label text. */
   void               SetLabel(const string label)
     {
      m_def.label = label;
      if(ObjectFind(0, m_rectName) >= 0)
         ObjectSetString(0, m_rectName, OBJPROP_TEXT, m_def.label);
     }

   /** Updates the drawing colour. */
   void               SetColor(const color value)
     {
      m_color = value;
      if(ObjectFind(0, m_rectName) >= 0)
         ObjectSetInteger(0, m_rectName, OBJPROP_COLOR, m_color);
     }

   /** Sets the visual visibility. */
   void               SetVisible(const bool visible)
     {
      m_visible = visible;
      if(ObjectFind(0, m_rectName) >= 0)
         ObjectSetInteger(0, m_rectName, OBJPROP_HIDDEN, !visible);
     }

   /** Returns true if the zone is currently active (not terminated). */
   bool               IsActive() { return m_phase != ZONE_PHASE_TERMINATED; }

   /** Returns true when the zone is in reversal state. */
   bool               IsReversal() { return m_phase == ZONE_PHASE_REVERSAL; }

   /** Updates the rectangle on the chart or creates it if missing. */
   void               Render()
     {
      if(!m_visible)
         return;

      const bool exists = (ObjectFind(0, m_rectName) >= 0);
      if(!exists)
        {
         ObjectCreate(0, m_rectName, OBJ_RECTANGLE, 0, m_def.anchorTime, m_def.zoneHigh, TimeCurrent(), m_def.zoneLow);
         ObjectSetInteger(0, m_rectName, OBJPROP_BACK, false);
         ObjectSetInteger(0, m_rectName, OBJPROP_COLOR, m_color);
         ObjectSetInteger(0, m_rectName, OBJPROP_STYLE, STYLE_DASH);
         ObjectSetInteger(0, m_rectName, OBJPROP_WIDTH, 1);
         ObjectSetString(0, m_rectName, OBJPROP_TEXT, m_def.label);
         ObjectSetInteger(0, m_rectName, OBJPROP_RAY_RIGHT, true);
        }
      else
        {
         ObjectMove(0, m_rectName, 0, m_def.anchorTime, m_def.zoneHigh);
         ObjectMove(0, m_rectName, 1, TimeCurrent(), m_def.zoneLow);
        }
     }

   /**
    * Tests whether a closing price breaks the zone boundaries.
    * @param closePrice Close price of the candle under inspection.
    * @return true when the zone experiences a break event.
    */
   bool               RegisterClose(const double closePrice)
     {
      if(m_phase == ZONE_PHASE_TERMINATED)
         return false;

      bool broken = false;
      if(m_def.direction == ZONE_DIRECTION_BUY)
         broken = (closePrice < m_def.zoneLow);
      else
         broken = (closePrice > m_def.zoneHigh);

      if(!broken)
         return false;

      ++m_breakCount;
      if(m_phase == ZONE_PHASE_ACTIVE)
        {
         m_phase = ZONE_PHASE_REVERSAL;
         FlipDirection();
        }
      else
         if(m_phase == ZONE_PHASE_REVERSAL)
            m_phase = ZONE_PHASE_TERMINATED;

      return true;
     }

   /**
    * Re-maps the zone to the opposite direction when a reversal is triggered.
    */
   void               FlipDirection()
     {
      if(m_phase == ZONE_PHASE_TERMINATED)
         return;
      if(m_def.direction == ZONE_DIRECTION_BUY)
         m_def.direction = ZONE_DIRECTION_SELL;
      else
         m_def.direction = ZONE_DIRECTION_BUY;
      if(ObjectFind(0, m_rectName) >= 0)
        {
         ObjectSetInteger(0, m_rectName, OBJPROP_COLOR, m_color);
         ObjectSetString(0, m_rectName, OBJPROP_TEXT, m_def.label);
        }
     }

   /**
    * Checks if price currently trades within the zone boundaries.
    * @param price Current market price.
    * @return true when price lies between high/low.
    */
   bool               ContainsPrice(const double price)
     {
      const double top    = MathMax(m_def.zoneHigh, m_def.zoneLow);
      const double bottom = MathMin(m_def.zoneHigh, m_def.zoneLow);
      return (price <= top && price >= bottom);
     }

   /**
    * Marks the zone as terminated and removes the chart object.
    */
   void               Terminate()
     {
      m_phase = ZONE_PHASE_TERMINATED;
      ObjectDelete(0, m_rectName);
     }
  };

#endif // __THIVYAM_ZONE_TYPES_MQH__
