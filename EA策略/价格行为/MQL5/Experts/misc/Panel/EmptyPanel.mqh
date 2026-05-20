//+------------------------------------------------------------------+
//|                             misc/Panel/EmptyPanel.mqh |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+

// header guards to prevent multiple inclusions of the same header file during compilation.
#ifndef EMPTYPANEL_MQH        // preprocessor directive that checks if the macro EMPTYPANEL_MQH has already been defined.
#define EMPTYPANEL_MQH        // This defines the macro EMPTYPANEL_MQH. Once this macro is defined, any subsequent inclusion of this file will skip its contents because the #ifndef condition will fail.

//+------------------------------------------------------------------+
//| includes                                                         |
//| ................................................................ |
//+------------------------------------------------------------------+
#include <Controls/Dialog.mqh>

//+------------------------------------------------------------------+
//| Class EmptyPanel                                                 |
//| Usage: create an empty dialog of the Controls application        |
//| ................................................................ |
//| EmptyPanel inherits from CAppDialog, which provides the base     |
//| functionality for creating and managing dialog windows.          |
//+------------------------------------------------------------------+
class EmptyPanel : public CAppDialog
  {

    public:
                    EmptyPanel(void);
                    ~EmptyPanel(void);
    //--- create
    virtual bool     Create(const long chart,const string name,const int subwin,const int x1,const int y1,const int x2,const int y2);
  };

//+------------------------------------------------------------------+
//| Constructor                                                      |
//| ................................................................ |
//+------------------------------------------------------------------+
EmptyPanel::EmptyPanel(void)
  {
    //--- The constructor is empty, as no special initialization is required beyond what is handled by the base class.
  }

//+------------------------------------------------------------------+
//| Destructor                                                       |
//| ................................................................ |
//+------------------------------------------------------------------+
EmptyPanel::~EmptyPanel(void)
  {
    //--- The destructor is empty, as no special cleanup is required beyond what is handled by the base class.
  }

//+------------------------------------------------------------------+
//| Create                                                           |
//| ................................................................ |
//| This method initializes the empty dialog.                        |
//+------------------------------------------------------------------+
bool EmptyPanel::Create(const long chart,const string name,const int subwin,const int x1,const int y1,const int x2,const int y2)
  {
   if(!CAppDialog::Create(chart,name,subwin,x1,y1,x2,y2))
      return(false);
//--- succeed
   return(true);
  }

//+------------------------------------------------------------------+
#endif // EMPTYPANEL_MQH