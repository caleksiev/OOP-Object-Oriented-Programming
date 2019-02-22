#ifndef _HEADER_TRAN_INCLUDED
#define _HEADER_TRAN_INCLUDED
#include"Wallet.h"
struct Transaction {
	long long time;
	unsigned senderId;
	unsigned receiverId;
	double fmiCoins;
};

//after every created wallet is ctreated one transaction
void AddTrans(Transaction& tran, const Wallet& wall);

/*
by the command WALLET-INFO *IDWALLET*
the funtion open the TRAN file and searched 
the id, checking all of the struct
if the id is the searched one -extract the coins value
while there is no more to read
if occurs a error while operating the file the result is -1
*/
double FindFmiCoinTransFile(size_t search);

#endif 



