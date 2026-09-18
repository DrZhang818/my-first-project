// Broker execution checks. All distances are MT4 points; money stays in account currency.
extern int PendingFloorPoints=1000; // XAUUSD three-digit diagnostic distance floor
extern int BrokerSafetyBufferPoints=50;
extern int TradeRetrySeconds=10;
extern double MaxTotalLots=0; // 0 disables extra cap; includes pending orders
extern bool StopAfterLoss=true;
bool BrokerLossHalted=false;
datetime BrokerNextAttempt[2];
datetime BrokerNextModify[2];
string BrokerLastMessage="";
datetime BrokerLastMessageTime=0;

void BrokerNote(string message)
{
   if(message!=BrokerLastMessage || TimeCurrent()-BrokerLastMessageTime>=60)
   {
      Print("[Amazing broker check] ",message);
      BrokerLastMessage=message;
      BrokerLastMessageTime=TimeCurrent();
   }
}

double BrokerDistance(int configured)
{
   double required=MathMax(MarketInfo(Symbol(),MODE_STOPLEVEL),MarketInfo(Symbol(),MODE_FREEZELEVEL));
   return MathMax(configured,MathMax(PendingFloorPoints,required+MathMax(1,BrokerSafetyBufferPoints)));
}

string BrokerBlockReason(int count)
{
   string why="";
   if(!IsConnected() && !IsTesting()) why+="Disconnected; ";
   if(!IsExpertEnabled()) why+="AutoTrading OFF; ";
   if(!IsTradeAllowed()) why+="EA trading permission OFF or trade context busy; ";
   if(MarketInfo(Symbol(),MODE_TRADEALLOWED)==0) why+="Symbol trading disabled; ";
   if(AccountLeverage()<Leverage) why+="Leverage below configured minimum; ";
   if(count>=Totals) why+="Order limit (including pending); ";
   if(MarketInfo(Symbol(),MODE_SPREAD)>MaxSpread)
      why+="Spread "+DoubleToString(MarketInfo(Symbol(),MODE_SPREAD),0)+">"+IntegerToString(MaxSpread)+" points; ";
   if(IsStopped()) why+="EA stopping; ";
   return why;
}

double BrokerVolume(double requested)
{
   double step=MarketInfo(Symbol(),MODE_LOTSTEP);
   double minimum=MarketInfo(Symbol(),MODE_MINLOT);
   double maximum=MathMin(Maxlot,MarketInfo(Symbol(),MODE_MAXLOT));
   if(step<=0 || minimum<=0 || requested<minimum-1e-9 || maximum<minimum-1e-9) return 0;
   double volume=NormalizeDouble(MathFloor((MathMin(requested,maximum)+1e-9)/step)*step,8);
   if(volume<minimum-1e-9 || volume>requested+1e-9) return 0;
   return volume; // Never increase a small requested order to the broker minimum.
}

double BrokerPendingPrice(int type,double price)
{
   double tick=SymbolInfoDouble(Symbol(),SYMBOL_TRADE_TICK_SIZE);
   if(tick<=0) tick=Point;
   if(type==OP_BUYSTOP) return NormalizeDouble(MathCeil(price/tick-1e-9)*tick,Digits);
   return NormalizeDouble(MathFloor(price/tick+1e-9)*tick,Digits);
}

bool BrokerPriceValid(int type,double price)
{
   double distance=(type==OP_BUYSTOP ? price-Ask : Bid-price)/Point;
   return distance+1e-6>=MarketInfo(Symbol(),MODE_STOPLEVEL)+MathMax(1,BrokerSafetyBufferPoints);
}

string BrokerErrorText(int error)
{
   if(error==130) return "Invalid pending distance/stops: inspect StopLevel; increase PendingFloorPoints if dynamic limit persists";
   if(error==131) return "Invalid volume: inspect min lot and lot step";
   if(error==134) return "Insufficient margin";
   if(error==132) return "Market closed";
   if(error==133 || error==4109) return "Trading disabled or EA permission denied";
   if(error==146) return "Trade context busy";
   if(error==128) return "Timeout: inspect live orders before any manual retry";
   return "See MT4 Journal";
}

void BrokerFailure(string operation,int error,int type,double volume,double price)
{
   BrokerNote(operation+" error="+IntegerToString(error)+" "+BrokerErrorText(error)+
      " type="+IntegerToString(type)+" lots="+DoubleToString(volume,8)+
      " price="+DoubleToString(price,Digits)+" bid="+DoubleToString(Bid,Digits)+" ask="+DoubleToString(Ask,Digits)+
      " stop="+DoubleToString(MarketInfo(Symbol(),MODE_STOPLEVEL),0)+
      " freeze="+DoubleToString(MarketInfo(Symbol(),MODE_FREEZELEVEL),0)+
      " spread="+DoubleToString(MarketInfo(Symbol(),MODE_SPREAD),0)+" points");
}

int BrokerSendPending(int type,double requested,double price,string comment,color arrow)
{
   int side=(type==OP_BUYSTOP ? 0 : 1);
   if(TimeCurrent()<BrokerNextAttempt[side]) return -1;
   BrokerNextAttempt[side]=TimeCurrent()+MathMax(1,TradeRetrySeconds);
   RefreshRates();
   int count=0;
   double exposure=0;
   for(int n=OrdersTotal()-1;n>=0;n--)
      if(OrderSelect(n,SELECT_BY_POS,MODE_TRADES) && OrderSymbol()==Symbol() && OrderMagicNumber()==Magic)
      {
         count++;
         exposure+=OrderLots();
         if(OrderType()==type) { BrokerNote("Pending order already exists for this direction"); return -1; }
      }
   string blocked=BrokerBlockReason(count);
   if(blocked!="") { BrokerNote(blocked); return -1; }
   double volume=BrokerVolume(requested);
   if(volume<=0) { BrokerNote("Requested lot below minimum or invalid lot settings; no upward resizing"); return -1; }
   if(MaxTotalLots>0 && exposure+volume>MaxTotalLots+1e-9)
      { BrokerNote("Total lot cap including pending orders reached"); return -1; }
   price=BrokerPendingPrice(type,price);
   if(!BrokerPriceValid(type,price))
      { BrokerNote("Quote moved or pending distance too small; recompute on next attempt"); return -1; }
   ResetLastError();
   double remaining=AccountFreeMarginCheck(Symbol(),side,volume);
   int marginError=GetLastError();
   if(remaining<=0 || marginError!=0)
      { BrokerFailure("Margin check",marginError==0 ? 134 : marginError,type,volume,price); return -1; }
   ResetLastError();
   int ticket=OrderSend(Symbol(),type,volume,price,总_in_22,0,0,comment,Magic,0,arrow);
   int error=GetLastError();
   if(ticket<0)
   {
      BrokerFailure("OrderSend",error,type,volume,price);
      if(error==128) BrokerNextAttempt[side]=TimeCurrent()+120;
   }
   return ticket;
}

bool BrokerModifyPending(int ticket,double price)
{
   if(!OrderSelect(ticket,SELECT_BY_TICKET) || OrderCloseTime()!=0 || OrderSymbol()!=Symbol() || OrderMagicNumber()!=Magic) return false;
   int type=OrderType();
   if(type!=OP_BUYSTOP && type!=OP_SELLSTOP) return false;
   int side=(type==OP_BUYSTOP ? 0 : 1);
   if(TimeCurrent()<BrokerNextModify[side]) return false;
   RefreshRates();
   double old=OrderOpenPrice();
   double freeze=MarketInfo(Symbol(),MODE_FREEZELEVEL);
   double oldDistance=(type==OP_BUYSTOP ? old-Ask : Bid-old)/Point;
   price=BrokerPendingPrice(type,price);
   if(!BrokerPriceValid(type,price) || (freeze>0 && oldDistance<=freeze)) return false;
   if(MathAbs(price-old)<Point/2) return false;
   BrokerNextModify[side]=TimeCurrent()+MathMax(1,TradeRetrySeconds);
   double volume=OrderLots();
   ResetLastError();
   bool ok=OrderModify(ticket,price,OrderStopLoss(),OrderTakeProfit(),OrderExpiration(),clrWhite);
   int error=GetLastError();
   if(!ok) BrokerFailure("OrderModify",error,type,volume,price);
   return ok;
}

void BrokerPrintSpecs()
{
   Print("[Amazing specs] currency=",AccountCurrency()," symbol=",Symbol()," digits=",Digits,
      " point=",DoubleToString(Point,Digits)," contract=",MarketInfo(Symbol(),MODE_LOTSIZE),
      " minlot=",MarketInfo(Symbol(),MODE_MINLOT)," lotstep=",MarketInfo(Symbol(),MODE_LOTSTEP),
      " ticksize=",SymbolInfoDouble(Symbol(),SYMBOL_TRADE_TICK_SIZE),
      " tickvalue=",MarketInfo(Symbol(),MODE_TICKVALUE),
      " stop=",MarketInfo(Symbol(),MODE_STOPLEVEL)," freeze=",MarketInfo(Symbol(),MODE_FREEZELEVEL),
      " pendingFloor=",PendingFloorPoints," money thresholds are in ACCOUNT CURRENCY");
}
