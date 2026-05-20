#ifndef __EMA_HELPER_MQH__
#define __EMA_HELPER_MQH__

// Function to calculate EMA
double GetEMA(string symbol, ENUM_TIMEFRAMES timeframe, int period)
{
    int handle = iMA(symbol, timeframe, period, 0, MODE_EMA, PRICE_CLOSE);
    if (handle == INVALID_HANDLE)
    {
        Print("Error creating EMA handle: ", GetLastError());
        return 0.0;
    }

    double emaBuffer[];
    if (CopyBuffer(handle, 0, 0, 1, emaBuffer) <= 0)
    {
        Print("Error copying EMA buffer: ", GetLastError());
        return 0.0;
    }

    return emaBuffer[0];
}

#endif // __EMA_HELPER_MQH__