//+------------------------------------------------------------------+
//|                                                 Panel.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "1.00"
#include "BasePanel.mqh"
//+------------------------------------------------------------------+
//| Global Variables                                                 |
//+------------------------------------------------------------------+
BasePanel Panel;
//+------------------------------------------------------------------+
//| Expert initialization function                                   |
//+------------------------------------------------------------------+
int OnInit()
  {
//--- create application dialog
   if(!Panel.Create(0,"...::| Panel |::...",0,20,20,360,324))
     return(INIT_FAILED);
//--- run application
   Panel.Run();
//--- show the dialog
Panel.Show();
//--- succeed
   return(INIT_SUCCEEDED);
  }
//+------------------------------------------------------------------+
//| Expert deinitialization function                                 |
//+------------------------------------------------------------------+
void OnDeinit(const int reason)
  {
//--- destroy dialog
   Panel.Destroy(reason);
  }
//+------------------------------------------------------------------+
//| Expert chart event function                                      |
//+------------------------------------------------------------------+
void OnChartEvent(const int id,         // event ID  
                  const long& lparam,   // event parameter of the long type
                  const double& dparam, // event parameter of the double type
                  const string& sparam) // event parameter of the string type
  {
   Panel.ChartEvent(id,lparam,dparam,sparam);
  }
//+------------------------------------------------------------------+
