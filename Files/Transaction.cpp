#include"Transaction.h"
#include<iostream>
#include<fstream>
#include<ctime>
void AddTrans(Transaction& tran, const Wallet& wall)
{
	time_t seconds_1970 = time(0);
	std::fstream transactions;
	transactions.open("transactions.dat", std::ios::out | std::ios::binary | std::ios::app);
	if (!transactions.is_open())//we should not enter here,because the flag ios::out is set
	{
		std::cerr << "A problem while opening the file wallets.dat";
		return;
	}

	tran.receiverId = wall.id;
	tran.senderId = INVALID_ID;
	tran.time = seconds_1970;
	tran.fmiCoins = wall.fiatMoney / RAND_NUM;
	transactions.write((const char*)&tran, sizeof(tran));
	if (!transactions.good())
	{
		return;
		std::cout << "Error while writting on file";
	}
	transactions.close();
}
double FindFmiCoinTransFile(size_t search)
{
	Transaction tran;
	double sumCoin = 0;
	std::fstream f;
	f.open("transactions.dat", std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cout << "Error while opening the sile\n";
		return -1;
	}
	while (f.good())
	{
		f.read((char*)&tran, sizeof(tran));
		if (tran.receiverId == search && f.good())
		{
			sumCoin += tran.fmiCoins;
		}
	} 
	f.close();
	return sumCoin;
}
