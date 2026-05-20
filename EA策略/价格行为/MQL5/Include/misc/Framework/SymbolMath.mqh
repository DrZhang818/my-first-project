/**
 * @file SymbolMath.mqh
 * @brief Utility helpers for symbol-specific price, pip, and volume calculations.
 */

#ifndef __THIVYAM_SYMBOL_MATH_MQH__
#define __THIVYAM_SYMBOL_MATH_MQH__

/**
 * Provides static helper methods for symbol-specific calculations.
 */
class CSymbolMath
  {
public:
   /**
    * Converts pips to price points for the provided symbol.
    * @param symbol Trading symbol, defaults to _Symbol.
    * @param pips Pip distance to convert.
    * @return Price distance equivalent for the supplied pips.
    */
   static double     PipsToPrice(const string symbol, const double pips)
     {
      const double point      = SymbolInfoDouble(symbol, SYMBOL_POINT);
      const int    digits     = (int)SymbolInfoInteger(symbol, SYMBOL_DIGITS);
      const double pipFactor  = (digits == 3 || digits == 5) ? 10.0 : 1.0;
      return pips * point * pipFactor;
     }

   /**
    * Converts a raw price distance into pips.
    * @param symbol Trading symbol.
    * @param priceDistance Absolute price distance to convert.
    * @return Distance in pips.
    */
   static double     PriceToPips(const string symbol, const double priceDistance)
     {
      const double point      = SymbolInfoDouble(symbol, SYMBOL_POINT);
      const int    digits     = (int)SymbolInfoInteger(symbol, SYMBOL_DIGITS);
      const double pipFactor  = (digits == 3 || digits == 5) ? 10.0 : 1.0;
      if(point == 0.0)
         return 0.0;
      return priceDistance / (point * pipFactor);
     }

   /**
    * Normalises a user-provided lot size to the broker's constraints.
    * @param symbol Trading symbol.
    * @param lots Requested lot size.
    * @return Broker-compliant lot size.
    */
   static double     NormalizeLots(const string symbol, const double lots)
     {
      const double minLot = SymbolInfoDouble(symbol, SYMBOL_VOLUME_MIN);
      const double maxLot = SymbolInfoDouble(symbol, SYMBOL_VOLUME_MAX);
      const double step   = SymbolInfoDouble(symbol, SYMBOL_VOLUME_STEP);
      double       value  = MathMax(minLot, MathMin(maxLot, lots));
      return NormalizeDouble(value / step, 0) * step;
     }
  };

#endif // __THIVYAM_SYMBOL_MATH_MQH__
