//+------------------------------------------------------------------+
//|                                          MiscFunctionsHelper.mq5 |
//|                                    Copyright 2025, bill |
//|                                     bill |
//+------------------------------------------------------------------+
#property library
#property copyright "Copyright 2025, bill"
#property link      "bill"
#property version   "3.00"


//+------------------------------------------------------------------+
//| Helper: Round double to 5 digits                                 |
//+------------------------------------------------------------------+
double Round5(double value) {
   return NormalizeDouble(value, _Digits);
}

//+------------------------------------------------------------------+
//| v1.03: Helper: Generate a unique batch ID (use time of signal)   |
//+------------------------------------------------------------------+
string GenerateBatchID(datetime signalTime) {
   return IntegerToString((int)signalTime);
}

//+------------------------------------------------------------------+
//| Enable trailing for a batch (store batch_id in a list)           |
//+------------------------------------------------------------------+
void EnableTrailingForBatch(string batch_id)
{
   if (debugging) { Print("🔼(EnableTrailingForBatch) ********"); PrintTrailingBatches(); }

   // Only add if not already present (case-sensitive, but batch_id is numeric string)
   for(int i = 0; i < trailingBatches.Total(); i++)
   {
      if(trailingBatches.At(i) == batch_id)
      {
         if (debugging) { Print("🔼(EnableTrailingForBatch) |>>> Batch ID ", batch_id, " already in trailingBatches."); }
         return;
      }
   }
   trailingBatches.Add(batch_id);
}

//+------------------------------------------------------------------+
//| Print all batch IDs in trailingBatches                           |
//+------------------------------------------------------------------+
void PrintTrailingBatches()
{
    string msg = "trailingBatches: [";
    for(int i = 0; i < trailingBatches.Total(); i++)
    {
        if(i > 0) msg += ", ";
        msg += trailingBatches.At(i);
    }
    msg += "]";
    Print(msg);
}

//+------------------------------------------------------------------+