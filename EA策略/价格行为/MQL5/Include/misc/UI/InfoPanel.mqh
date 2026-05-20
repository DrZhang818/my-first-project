/**
 * @file InfoPanel.mqh
 * @brief Implements a draggable on-chart information panel for diagnostics.
 */

#ifndef __THIVYAM_INFO_PANEL_MQH__
#define __THIVYAM_INFO_PANEL_MQH__

#include <Object.mqh>
#include <ChartObjects\ChartObjectsTxtControls.mqh>

/**
 * Draws a floating panel displaying runtime diagnostics.
 */
class CInfoPanel : public CObject
  {
private:
   string            m_prefix;
   bool              m_enabled;
   bool              m_minimized;
   long              m_chartId;
  ENUM_BASE_CORNER  m_corner;
   int               m_xOffset;
   int               m_yOffset;
   color             m_bgColor;
   color             m_textColor;
   color             m_borderColor;

   string            ContainerName() { return m_prefix + "_panel"; }
   string            LabelName() { return m_prefix + "_label"; }
   string            ButtonName() { return m_prefix + "_toggle"; }

   void              CreateOuter()
     {
      const string container = ContainerName();
      if(ObjectFind(m_chartId, container) < 0)
        {
         ObjectCreate(m_chartId, container, OBJ_RECTANGLE_LABEL, 0, 0, 0);
         ObjectSetInteger(m_chartId, container, OBJPROP_CORNER, m_corner);
         ObjectSetInteger(m_chartId, container, OBJPROP_XDISTANCE, m_xOffset);
         ObjectSetInteger(m_chartId, container, OBJPROP_YDISTANCE, m_yOffset);
         ObjectSetInteger(m_chartId, container, OBJPROP_COLOR, m_bgColor);
         ObjectSetInteger(m_chartId, container, OBJPROP_BORDER_COLOR, m_borderColor);
         ObjectSetInteger(m_chartId, container, OBJPROP_BACK, true);
         ObjectSetInteger(m_chartId, container, OBJPROP_XSIZE, 200);
         ObjectSetInteger(m_chartId, container, OBJPROP_YSIZE, 120);
         ObjectSetInteger(m_chartId, container, OBJPROP_SELECTABLE, true);
         ObjectSetInteger(m_chartId, container, OBJPROP_HIDDEN, false);
        }
     }

   void              CreateButton()
     {
      const string button = ButtonName();
      if(ObjectFind(m_chartId, button) < 0)
        {
         ObjectCreate(m_chartId, button, OBJ_BUTTON, 0, 0, 0);
         ObjectSetInteger(m_chartId, button, OBJPROP_CORNER, m_corner);
         ObjectSetInteger(m_chartId, button, OBJPROP_XDISTANCE, m_xOffset + 170);
         ObjectSetInteger(m_chartId, button, OBJPROP_YDISTANCE, m_yOffset + 5);
         ObjectSetInteger(m_chartId, button, OBJPROP_XSIZE, 20);
         ObjectSetInteger(m_chartId, button, OBJPROP_YSIZE, 20);
         ObjectSetString(m_chartId, button, OBJPROP_TEXT, m_minimized ? "+" : "-");
         ObjectSetInteger(m_chartId, button, OBJPROP_FONTSIZE, 10);
        }
     }

   void              CreateLabel(const string text)
     {
      const string label = LabelName();
      if(ObjectFind(m_chartId, label) < 0)
        {
         ObjectCreate(m_chartId, label, OBJ_LABEL, 0, 0, 0);
        }
      ObjectSetInteger(m_chartId, label, OBJPROP_CORNER, m_corner);
      ObjectSetInteger(m_chartId, label, OBJPROP_XDISTANCE, m_xOffset + 10);
      ObjectSetInteger(m_chartId, label, OBJPROP_YDISTANCE, m_yOffset + 30);
      ObjectSetInteger(m_chartId, label, OBJPROP_FONTSIZE, 9);
      ObjectSetInteger(m_chartId, label, OBJPROP_COLOR, m_textColor);
      ObjectSetString(m_chartId, label, OBJPROP_TEXT, text);
     }

public:
                     CInfoPanel()
     {
      m_prefix      = "InfoPanel";
      m_enabled     = false;
      m_minimized   = false;
      m_chartId     = ChartID();
      m_corner      = CORNER_LEFT_UPPER;
      m_xOffset     = 10;
      m_yOffset     = 30;
      m_bgColor     = clrDarkSlateGray;
      m_textColor   = clrWhite;
      m_borderColor = clrSteelBlue;
     }

   /**
    * Configures the panel visibility and position preferences.
    * @param enabled Whether the panel should be rendered.
    * @param prefix Unique prefix for chart object naming.
    * @param corner Screen corner to anchor the panel.
    * @param xOffset Horizontal offset from the corner.
    * @param yOffset Vertical offset from the corner.
    * @param bgColor Background color of the panel (default: clrDarkSlateGray).
    * @param textColor Text color (default: clrWhite).
    * @param borderColor Border color (default: clrSteelBlue).
    */
  void              Configure(const bool enabled,
                     const string prefix,
                     const ENUM_BASE_CORNER corner,
                               const int xOffset,
                               const int yOffset,
                               const color bgColor = clrDarkSlateGray,
                               const color textColor = clrWhite,
                               const color borderColor = clrSteelBlue)
     {
      m_enabled     = enabled;
      m_prefix      = prefix;
      m_corner      = corner;
      m_xOffset     = xOffset;
      m_yOffset     = yOffset;
      m_bgColor     = bgColor;
      m_textColor   = textColor;
      m_borderColor = borderColor;
     }

   /**
    * Updates the panel content using the supplied lines.
    * @param lines Text to display, separated by newline characters.
    */
   void              Update(const string lines)
     {
      if(!m_enabled)
        {
         Destroy();
         return;
        }

      CreateOuter();
      CreateButton();
      CreateLabel(m_minimized ? "" : lines);
      ObjectSetString(m_chartId, ButtonName(), OBJPROP_TEXT, m_minimized ? "+" : "-");
     }

   /**
    * Processes chart events to enable dragging and minimisation.
    * @param id Event identifier.
    * @param lparam First parameter.
    * @param dparam Second parameter.
    * @param sparam Text parameter (object name).
    */
   void              OnChartEvent(const int id, const long lparam, const double dparam, const string sparam)
     {
      if(!m_enabled)
         return;

      if(id == CHARTEVENT_OBJECT_CLICK && sparam == ButtonName())
        {
         m_minimized = !m_minimized;
         ObjectSetString(m_chartId, ButtonName(), OBJPROP_TEXT, m_minimized ? "+" : "-");
         return;
        }

      if(id == CHARTEVENT_OBJECT_DRAG && sparam == ContainerName())
        {
         m_xOffset = (int)ObjectGetInteger(m_chartId, ContainerName(), OBJPROP_XDISTANCE);
         m_yOffset = (int)ObjectGetInteger(m_chartId, ContainerName(), OBJPROP_YDISTANCE);
        }
     }

   /**
    * Removes the panel from the chart.
    */
   void              Destroy()
     {
      ObjectDelete(m_chartId, ContainerName());
      ObjectDelete(m_chartId, LabelName());
      ObjectDelete(m_chartId, ButtonName());
     }
  };

#endif // __THIVYAM_INFO_PANEL_MQH__
