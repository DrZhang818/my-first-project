//+------------------------------------------------------------------+
//|                              misc/Panel/BasePanel.mqh |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+

#ifndef BASEPANEL_MQH
#define BASEPANEL_MQH

// BasePanel header file for Panel module

//+------------------------------------------------------------------+
//| includes                                                         |
//| ................................................................ |
//| Include definitions for various GUI controls like buttons,       |
//| edit fields, date pickers, etc., which are used in the dialog.   |
//+------------------------------------------------------------------+
#include <Trade\AccountInfo.mqh>
#include "EmptyPanel.mqh" // Include the EmptyPanel class for base functionality
#include <Controls/Button.mqh>
#include <Controls/Edit.mqh>
#include <Controls/Label.mqh>

//+------------------------------------------------------------------+
//| defines                                                          |
//| ................................................................ |
//| define constants for layout properties such as margins, gaps,    |
//| and dimensions of the controls. These values are used to         |
//| position and size the controls dynamically.                      |
//+------------------------------------------------------------------+
//--- indents and gaps
#define INDENT_LEFT             (11)    // indent from left (with allowance for border width)
#define INDENT_TOP              (11)    // indent from top (with allowance for border width)
#define INDENT_RIGHT            (11)    // indent from right (with allowance for border width)
#define INDENT_BOTTOM           (11)    // indent from bottom (with allowance for border width)
#define CONTROLS_GAP_X          (5)     // gap by X coordinate
#define CONTROLS_GAP_Y          (5)     // gap by Y coordinate
//--- for buttons
#define BUTTON_WIDTH            (100)   // size by X coordinate
#define BUTTON_HEIGHT           (20)    // size by Y coordinate
//--- for the indication area
#define EDIT_HEIGHT             (20)    // size by Y coordinate
//--- for group controls
#define GROUP_WIDTH             (150)   // size by X coordinate
#define LIST_HEIGHT             (179)   // size by Y coordinate
#define RADIO_HEIGHT            (56)    // size by Y coordinate
#define CHECK_HEIGHT            (93)    // size by Y coordinate
#define LABEL_HEIGHT            (20)    // size by Y coordinate

//+------------------------------------------------------------------+
//| Class BasePanel                                                  |
//| Usage: main dialog of the Controls application                   |
//| ................................................................ |
//| BasePanel inherits from EmptyPanel which inherits CAppDialog,    |
//| which provides the base functionality for creating and           |
//| managing dialog windows.                                         |
//+------------------------------------------------------------------+
class BasePanel : public EmptyPanel
  {
    //--- These private member variables represent the various controls in the dialog.
    //--- Each control is an instance of its respective class.
private:
   CEdit             m_textArea1;       // Uneditable text area
   CButton           m_toggleButton1;   // Button to toggle visibility
   CLabel            m_textLabel1;       // Label to display Account Holder Name
   //--- (TBD)

public:
                    BasePanel(void);
                    ~BasePanel(void);
   //--- create
   virtual bool     Create(const long chart,const string name,const int subwin,const int x1,const int y1,const int x2,const int y2);
   //--- chart event handler
   virtual bool     OnEvent(const int id,const long &lparam,const double &dparam, const string &sparam);

   //--- toggle text area visibility

protected:
   CAccountInfo      m_account;
   //--- create dependent controls
   bool              CreateTextArea1(void);
   bool              CreateToggleButton1(void);
   bool              CreateTextLabel1(void);
   //--- (TBD)
   //--- handlers of the dependent controls events
   void              OnClickToggleButton1(void);
   //--- (TBD)
  };

//+------------------------------------------------------------------+
//| Event Handling                                                   |
//+------------------------------------------------------------------+
EVENT_MAP_BEGIN(BasePanel)
   ON_EVENT(ON_CLICK,m_toggleButton1,OnClickToggleButton1)
   //--- (TBD)
EVENT_MAP_END(CAppDialog)

//+------------------------------------------------------------------+
//| Constructor                                                      |
//| ................................................................ |
//+------------------------------------------------------------------+
BasePanel::BasePanel(void)
  {
    //--- The constructor is empty, as no special initialization is required beyond what is handled by the base class.
  }

//+------------------------------------------------------------------+
//| Destructor                                                       |
//| ................................................................ |
//+------------------------------------------------------------------+
BasePanel::~BasePanel(void)
  {
    //--- The destructor is empty, as no special cleanup is required beyond what is handled by the base class.
  }

//+------------------------------------------------------------------+
//| Create                                                           |
//| ................................................................ |
//+------------------------------------------------------------------+
bool BasePanel::Create(const long chart,const string name,const int subwin,const int x1,const int y1,const int x2,const int y2)
  {
   if(!CAppDialog::Create(chart,name,subwin,x1,y1,x2,y2))
      return(false);
   //--- create dependent controls
   if(!CreateTextLabel1())
      return(false);
   if(!CreateTextArea1())
      return(false);
   if(!CreateToggleButton1())
      return(false);
   //--- (TBD)

//--- succeed
   return(true);
  }

//+------------------------------------------------------------------+
//| Create the first display field (TextArea)                        |
//+------------------------------------------------------------------+
bool BasePanel::CreateTextArea1(void)
  {
//--- coordinates
   int x1=INDENT_LEFT;
   int y1=INDENT_TOP;
   int x2=ClientAreaWidth()-INDENT_RIGHT;
   int y2=y1+EDIT_HEIGHT;
//--- create
   if(!m_textArea1.Create(m_chart_id,m_name+"TextArea1",m_subwin,x1,y1,x2,y2))
      return(false);
   if(!m_textArea1.ReadOnly(true))
      return(false);
   if(!Add(m_textArea1))
      return(false);
//--- succeed
   return(true);
  }
  
//+------------------------------------------------------------------+
//| Create the "ToggleButton1" button                                      |
//+------------------------------------------------------------------+
bool BasePanel::CreateToggleButton1(void)
  {
//--- coordinates
   int x1=INDENT_LEFT;
   int y1=INDENT_TOP+(EDIT_HEIGHT+CONTROLS_GAP_Y);
   int x2=x1+BUTTON_WIDTH;
   int y2=y1+BUTTON_HEIGHT;
//--- create
   if(!m_toggleButton1.Create(m_chart_id,m_name+"ToggleButton1",m_subwin,x1,y1,x2,y2))
      return(false);
   if(!m_toggleButton1.Text("Show/Hide"))
      return(false);
   if(!Add(m_toggleButton1))
      return(false);
//--- succeed
   return(true);
  }

//+------------------------------------------------------------------+
//| Create the "Account Name" label                                  |
//+------------------------------------------------------------------+
bool BasePanel::CreateTextLabel1(void)
  {
//--- coordinates
   int x1 = INDENT_LEFT;
   int y1 = INDENT_TOP + (EDIT_HEIGHT + CONTROLS_GAP_Y) + (BUTTON_HEIGHT + CONTROLS_GAP_Y);
   int x2 = ClientAreaWidth() - INDENT_RIGHT;
   int y2 = y1 + BUTTON_HEIGHT; // Use BUTTON_HEIGHT for consistent height
//--- create
   if(!m_textLabel1.Create(m_chart_id, m_name + "TextLabel1", m_subwin, x1, y1, x2, y2))
      return(false);
   if(!m_textLabel1.Text("Name: " + m_account.Name()))
      return(false);
   if(!Add(m_textLabel1))
      return(false);
//--- succeed
   Print("CreateTextLabel1 created");
   return(true);
  }
//+------------------------------------------------------------------+
//| Event handler                                                    |
//+------------------------------------------------------------------+
void BasePanel::OnClickToggleButton1(void)
  {
   static bool is_hidden = false; // Track visibility state

   if(is_hidden)
   {
      m_textArea1.Show(); // Show the CEdit object
   }
   else
   {
      m_textArea1.Hide(); // Hide the CEdit object
   }

   is_hidden = !is_hidden; // Toggle the state
   
  }
//+------------------------------------------------------------------+
#endif // BASEPANEL_MQH