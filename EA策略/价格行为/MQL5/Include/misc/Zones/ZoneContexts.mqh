/**
 * @file ZoneContexts.mqh
 * @brief Defines runtime context objects for the multi-timeframe zone workflow.
 */

#ifndef __THIVYAM_ZONE_CONTEXTS_MQH__
#define __THIVYAM_ZONE_CONTEXTS_MQH__

#include <Arrays\ArrayObj.mqh>

#include "ZoneTypes.mqh"

//+------------------------------------------------------------------+
//|                                                                  |
//+------------------------------------------------------------------+
class CM30ZoneContext;
class CM15ZoneContext;

/** Runtime representation of an H4 zone, including child zone state. */
class CH4ZoneContext : public CObject
  {
private:
   CZoneState        *m_zone;
   bool              m_monitoringM30;
   datetime          m_monitorStartTime;
   CM30ZoneContext   *m_child;
   bool              m_m30SearchDisabled;

public:
                     CH4ZoneContext(CZoneState *zone)
     {
      m_zone              = zone;
      m_monitoringM30     = false;
      m_monitorStartTime  = 0;
      m_child             = NULL;
      m_m30SearchDisabled = false;
     }

   virtual             ~CH4ZoneContext()
     {
      if(m_child != NULL)
         delete m_child;
      delete m_zone;
     }

   CZoneState         *Zone() { return m_zone; }
   CM30ZoneContext    *Child() { return m_child; }

   bool                IsMonitoringM30() { return m_monitoringM30; }
   bool                IsM30SearchDisabled() { return m_m30SearchDisabled; }

   void                BeginMonitoringM30(const datetime time)
     {
      m_monitoringM30    = true;
      m_monitorStartTime = time;
     }

   bool                ShouldMonitorM30(const datetime barTime)
     {
      return (m_monitoringM30 && barTime >= m_monitorStartTime);
     }

   void                AttachChild(CM30ZoneContext *child)
     {
      if(m_child != NULL)
         delete m_child;
      m_child = child;
      if(child != NULL)
         m_m30SearchDisabled = true;
     }

   void                ResetMonitoring()
     {
      m_monitoringM30    = false;
      m_monitorStartTime = 0;
      m_m30SearchDisabled = false;
     }

   void                DisableM30Search()
     {
      m_monitoringM30     = false;
      m_monitorStartTime  = 0;
      m_m30SearchDisabled = true;
     }
  };

/** Runtime representation of an M30 zone with optional M15 child. */
class CM30ZoneContext : public CObject
  {
private:
   CZoneState        *m_zone;
   bool              m_monitoringM15;
   datetime          m_monitorStartTime;
   CM15ZoneContext   *m_child;
   bool              m_m15SearchDisabled;

public:
                     CM30ZoneContext(CZoneState *zone)
     {
      m_zone              = zone;
      m_monitoringM15     = false;
      m_monitorStartTime  = 0;
      m_child             = NULL;
      m_m15SearchDisabled = false;
     }

   virtual             ~CM30ZoneContext()
     {
      if(m_child != NULL)
         delete m_child;
      delete m_zone;
     }

   CZoneState         *Zone() { return m_zone; }

   bool                IsMonitoringM15() { return m_monitoringM15; }
   bool                IsM15SearchDisabled() { return m_m15SearchDisabled; }

   void                BeginMonitoringM15(const datetime time)
     {
      m_monitoringM15    = true;
      m_monitorStartTime = time;
     }

   bool                ShouldMonitorM15(const datetime barTime)
     {
      return (m_monitoringM15 && barTime >= m_monitorStartTime);
     }

   void                AttachChild(CM15ZoneContext *child)
     {
      if(m_child != NULL)
         delete m_child;
      m_child = child;
      if(child != NULL)
         m_m15SearchDisabled = true;
     }

   CM15ZoneContext    *Child() { return m_child; }

   void                ResetMonitoring()
     {
      m_monitoringM15    = false;
      m_monitorStartTime = 0;
      m_m15SearchDisabled = false;
     }

   void                DisableM15Search()
     {
      m_monitoringM15     = false;
      m_monitorStartTime  = 0;
      m_m15SearchDisabled = true;
     }
  };

/** Runtime representation of an M15 zone that will generate an entry. */
class CM15ZoneContext : public CObject
  {
private:
   CZoneState        *m_zone;
   bool              m_orderPlaced;
   ulong             m_ticket;

public:
                     CM15ZoneContext(CZoneState *zone)
     {
      m_zone        = zone;
      m_orderPlaced = false;
      m_ticket      = 0;
     }

   virtual             ~CM15ZoneContext()
     {
      delete m_zone;
     }

   CZoneState         *Zone() { return m_zone; }

   bool                OrderPlaced() { return m_orderPlaced; }
   void                MarkOrderPlaced(const ulong ticket)
     {
      m_orderPlaced = true;
      m_ticket      = ticket;
     }

   ulong               Ticket() { return m_ticket; }
  };

#endif // __THIVYAM_ZONE_CONTEXTS_MQH__
