#ifndef _HEADER_INCLUDED_
#define _HEADER_INCLUDED_
#include"Constants.h"
struct Wallet 
{
	char owner[MAX_NAMELEN+1];
	unsigned id;
	double fiatMoney;
};

/*
this function generate the UNIQUE ID as follows:
if the file with WALLETS is still not created the id began from - 0
and when the user add new wallet this value is increment
else find the last wrote struct in the file and extract its ID value
*/
void CheckTheCurrWalletID(size_t& id, Wallet& wall);

/*
by the command ADD-WALLET *FIATMONEY* *NAME*
the function wrote from the given command in Wallet-struct
respective money and name
*/
void ExtractDataFromInput(Wallet& wall, size_t& id, char*command);



//add new wallets to the wallets file after the wrote data
void AddWallets(const Wallet&wall);

/*
by the command WALLET-INFO *IDWALLET*
the funtion open the WALLETS file and searched 
the id,that is sequence,that is why we go directly from the beggining
of the file to the serched postion 
if the id is bigger then the pos of the EOF the program 
indicates that such ID does not exist
*/
bool FindIDinWalletsFile(size_t search, Wallet&wall);

//check or owner have enought money to do the order
bool EnoughMoney(double coins, size_t ID);

#endif