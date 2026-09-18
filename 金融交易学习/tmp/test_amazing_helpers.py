from pathlib import Path
import re

root=Path(__file__).parent
actual=(root/'amazing_broker_helpers.mqh').read_text(encoding='utf-8')
actual=re.sub(r'\bextern\s+', '', actual)
prefix=r'''
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
'''
tests=r'''
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
'''
(root/'amazing_helpers_test.cpp').write_text(prefix+actual+tests,encoding='utf-8')
