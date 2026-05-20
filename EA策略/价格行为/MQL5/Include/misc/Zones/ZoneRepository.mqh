/**
 * @file ZoneRepository.mqh
 * @brief Maintains collections of zones across hierarchies.
 */

#ifndef __THIVYAM_ZONE_REPOSITORY_MQH__
#define __THIVYAM_ZONE_REPOSITORY_MQH__

#include <Object.mqh>
#include <Arrays\ArrayObj.mqh>

#include "ZoneContexts.mqh"

/**
 * Lightweight container for active H4 zones.
 */
class CZoneRepository : public CObject
  {
private:
   CArrayObj         m_h4Zones;

public:
   /**
    * Creates an empty zone repository.
    */
   CZoneRepository()
     {
      // CArrayObj initializes automatically
     }

   /**
    * Releases owned zone contexts.
    */
   virtual ~CZoneRepository()
     {
      Clear();
     }

   /**
    * Returns the number of stored H4 zone contexts.
    * @return Count of managed zones.
    */
   int Total()
     {
      return m_h4Zones.Total();
     }

   /**
    * Retrieves the zone context at the requested index.
    * @param index Zero-based index inside the repository.
    * @return Pointer to the stored context or NULL when out of range.
    */
   CH4ZoneContext *At(const int index)
     {
      if(index < 0 || index >= m_h4Zones.Total())
         return NULL;
      CObject *obj = m_h4Zones.At(index);
      return (CH4ZoneContext*)obj;
     }

   /**
    * Adds a new H4 zone context to the repository.
    * @param zone Context instance that becomes owned by the repository.
    */
   void Add(CH4ZoneContext *zone)
     {
      if(zone == NULL)
         return;

      if(!m_h4Zones.Add(zone))
        {
         Print(__FUNCTION__, ": Failed to append zone context");
         delete zone;
        }
     }

   /**
    * Removes and destroys the context stored at the given index.
    * @param index Zero-based index to delete.
    */
   void RemoveAt(const int index)
     {
      if(index < 0 || index >= m_h4Zones.Total())
         return;

      CObject *obj = m_h4Zones.At(index);
      CH4ZoneContext *ctx = (CH4ZoneContext*)obj;
      if(ctx != NULL)
         delete ctx;

      m_h4Zones.Delete(index);
     }

   /**
    * Iterates all zones and removes those that reached the termination phase.
    */
   void PurgeTerminated()
     {
      for(int i = m_h4Zones.Total() - 1; i >= 0; --i)
        {
         CObject *obj = m_h4Zones.At(i);
         if(obj == NULL)
            continue;
            
         CH4ZoneContext *ctx = (CH4ZoneContext*)obj;
         CZoneState *state = ctx.Zone();
         
         if(state != NULL && state.IsActive())
            continue;

         RemoveAt(i);
        }
     }

private:
   /**
    * Destroys every stored context and clears the array.
    */
   void Clear()
     {
      for(int i = m_h4Zones.Total() - 1; i >= 0; --i)
        {
         CObject *obj = m_h4Zones.At(i);
         CH4ZoneContext *ctx = (CH4ZoneContext*)obj;
         if(ctx != NULL)
            delete ctx;
        }

      m_h4Zones.Clear();
     }
  };

#endif // __THIVYAM_ZONE_REPOSITORY_MQH__
