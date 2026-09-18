
#include <cmath>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
using string=std::string; using datetime=long long; using color=int;
enum {MODE_STOPLEVEL,MODE_FREEZELEVEL,MODE_TRADEALLOWED,MODE_SPREAD,MODE_LOTSTEP,MODE_MINLOT,MODE_MAXLOT,MODE_LOTSIZE,MODE_TICKVALUE,SYMBOL_TRADE_TICK_SIZE};
enum {OP_BUY=0,OP_SELL=1,OP_BUYSTOP=4,OP_SELLSTOP=5,SELECT_BY_POS=0,SELECT_BY_TICKET=1,MODE_TRADES=0,clrWhite=0};
double props[10],Ask=4347.260,Bid=4347,Point=.001,Maxlot=10,freeMargin=1000;
int Digits=3,Leverage=100,Totals=4,MaxSpread=400,Magic=9453,总_in_22=30;
datetime now=1000; bool allowed=true; int errorCode=0,sendError=0,sends=0,modifies=0;
struct Order {int ticket,type; double volume,price;};
std::vector<Order> orders; int selected=-1;
double MathMax(double a,double b){return std::fmax(a,b);} double MathMin(double a,double b){return std::fmin(a,b);}
double MathFloor(double a){return std::floor(a);} double MathCeil(double a){return std::ceil(a);} double MathAbs(double a){return std::fabs(a);}
double NormalizeDouble(double a,int digits){double k=std::pow(10.,digits); return std::round(a*k)/k;}
string Symbol(){return "XAUUSDc";} double MarketInfo(string,int k){return props[k];} double SymbolInfoDouble(string,int k){return props[k];}
template<class...T> void Print(T...args){} string DoubleToString(double d,int n){return std::to_string(d);} string IntegerToString(int n){return std::to_string(n);}
datetime TimeCurrent(){return now;} bool IsConnected(){return true;} bool IsTesting(){return false;} bool IsExpertEnabled(){return allowed;} bool IsTradeAllowed(){return allowed;}
bool IsStopped(){return false;} int AccountLeverage(){return 2000;} void RefreshRates(){} string AccountCurrency(){return "USC";}
void ResetLastError(){errorCode=0;} int GetLastError(){int e=errorCode;errorCode=0;return e;}
double AccountFreeMarginCheck(string,int,double){return freeMargin;}
int OrdersTotal(){return orders.size();}
bool OrderSelect(int id,int mode,int pool=0){ if(mode==SELECT_BY_POS){selected=id;return id>=0 && id<(int)orders.size();} for(int i=0;i<(int)orders.size();i++)if(orders[i].ticket==id){selected=i;return true;} return false;}
string OrderSymbol(){return "XAUUSDc";} int OrderMagicNumber(){return Magic;} int OrderType(){return orders[selected].type;} double OrderLots(){return orders[selected].volume;}
double OrderOpenPrice(){return orders[selected].price;} datetime OrderCloseTime(){return 0;} datetime OrderExpiration(){return 0;} double OrderStopLoss(){return 0;} double OrderTakeProfit(){return 0;}
int OrderSend(string,int t,double v,double p,int,double,double,string,int,int,color){sends++;if(sendError){errorCode=sendError;return -1;}int ticket=orders.size()+1;orders.push_back({ticket,t,v,p});return ticket;}
bool OrderModify(int,double p,double,double,datetime,color){modifies++;orders[selected].price=p;return true;}
// Broker execution checks. All distances are MT4 points; money stays in account currency.
int PendingFloorPoints=1000; // XAUUSD three-digit diagnostic distance floor
int BrokerSafetyBufferPoints=50;
int TradeRetrySeconds=10;
double MaxTotalLots=0; // 0 disables extra cap; includes pending orders
bool StopAfterLoss=true;
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

void reset(){
 orders.clear(); selected=-1; sends=modifies=sendError=errorCode=0; allowed=true;freeMargin=1000; now+=1000;
 props[MODE_STOPLEVEL]=0; props[MODE_FREEZELEVEL]=0;props[MODE_TRADEALLOWED]=1;props[MODE_SPREAD]=260;
 props[MODE_LOTSTEP]=.01;props[MODE_MINLOT]=.01;props[MODE_MAXLOT]=100;props[SYMBOL_TRADE_TICK_SIZE]=.001;
 Maxlot=10;MaxTotalLots=0;BrokerNextAttempt[0]=BrokerNextAttempt[1]=0;BrokerNextModify[0]=BrokerNextModify[1]=0;
}
int main(){
 reset();assert(BrokerDistance(30)==1000);props[MODE_STOPLEVEL]=2000;assert(BrokerDistance(30)==2050);
 props[MODE_STOPLEVEL]=0;props[MODE_FREEZELEVEL]=2500;assert(BrokerDistance(30)==2550);
 reset();assert(BrokerVolume(.005)==0);assert(std::abs(BrokerVolume(.019)-.01)<1e-10);Maxlot=.025;assert(std::abs(BrokerVolume(.1)-.02)<1e-10);
 props[MODE_MINLOT]=.1;assert(BrokerVolume(.01)==0);
 reset();props[SYMBOL_TRADE_TICK_SIZE]=.01;assert(std::abs(BrokerPendingPrice(OP_BUYSTOP,4348.263)-4348.27)<1e-7);assert(std::abs(BrokerPendingPrice(OP_SELLSTOP,4345.999)-4345.99)<1e-7);
 reset();assert(!BrokerPriceValid(OP_BUYSTOP,Ask+.01));assert(BrokerPriceValid(OP_BUYSTOP,Ask+1));assert(BrokerPriceValid(OP_SELLSTOP,Bid-1));
 reset();assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)>0);assert(sends==1);now+=20;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(sends==1);
 reset();MaxTotalLots=.01;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)>0);assert(BrokerSendPending(OP_SELLSTOP,.01,Bid-1,"NN",0)<0);assert(sends==1);
 reset();for(int i=0;i<4;i++)orders.push_back({i+1,OP_BUY,.01,Bid});assert(BrokerSendPending(OP_SELLSTOP,.01,Bid-1,"NN",0)<0);assert(sends==0);
 reset();freeMargin=-1;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(sends==0);
 reset();props[MODE_SPREAD]=500;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(sends==0);
 reset();allowed=false;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(sends==0);
 reset();sendError=130;assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0)<0);assert(sends==1);
 reset();sendError=128;BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0);now+=30;BrokerSendPending(OP_BUYSTOP,.01,Ask+1,"NN",0);assert(sends==1);
 reset();orders.push_back({1,OP_BUYSTOP,.01,Ask+.5});props[MODE_FREEZELEVEL]=600;assert(!BrokerModifyPending(1,Ask+1));assert(modifies==0);
 reset();orders.push_back({1,OP_BUYSTOP,.01,Ask+2});assert(BrokerModifyPending(1,Ask+1));assert(modifies==1);
 std::cout<<"PASS: broker distance, volume, tick rounding, stale price, duplicates, pending-inclusive caps, margin, spread, permissions, retry cooldown, timeout and freeze checks\n";
}
