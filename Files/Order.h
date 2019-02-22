#ifndef _ORDER_INLUCDED_
#define _ORDER_INCLUDED_
struct Order {
	enum Type { INVALID = -1, SELL, BUY } type;
	unsigned walletId;
	double fmiCoins;
};

//check if the orderer have other order
bool isOrdererHasAlreadyOrder(size_t walletId, const char*fname);

/*
the function take the order and if there is no text file for it, such is created
if there is no other appropriate SELL (BUY )order for the current BUY(SELL) order 
the current order is just save to the file
else there is a appropriate orders,then the function enter in loop while the current order
is complete or there is no more proper orders
The following 6 situations are possible:
1)The both order are complete-The value of SELL order is equal of value of BUY order and the last enter order is BUY order
2)The both order are complete-The value of SELL order is equal of value of BUY order and the last enter order is SELL order
3)BUY order is copmlete:The value of SELL order is bigger then the value of BUY order and the last enter order is SELL order
4)BUY order is completeThe value of SELL order is bigger then the value of BUY order and the last enter order is BUY order
5)SELL order is copmlete:The value of BUY order is bigger then the value of SELL order and the last enter order is BUY order
6)SELL order is copmlete:The value of BUY order is bigger then the value of SELL order and the last enter order is SELL order
*/
void CompletingOrder( Order&order1, const char*fisrtnamefile, const char*secondnamefile, const char*modif);



#endif

