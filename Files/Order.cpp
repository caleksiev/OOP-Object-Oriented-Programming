#define _CRT_SECURE_NO_WARNINGS 1
#include"Order.h"
#include"Constants.h"
#include<fstream>
#include<iostream>
#include"OrderTemp.h"
//the temp function are in in OrderTemp.cpp
bool isOrdererHasAlreadyOrder(size_t walletId, const char*fname)
{
	Order ord;
	std::fstream f;
	f.open(fname, std::ios::in | std::ios::binary);
	if (!f.is_open())
		return true;
	while (f.good())
	{
		f.read((char*)&ord, sizeof(ord));
		if (f.good() && ord.walletId == walletId)
			return false;
	}
	return true;
}

void CompletingOrder( Order&order1,const char*fisrtnamefile,const char*secondnamefile,const char*modif)
{
	bool NotComplete = true;
	char filename[MAX_FILENAME+1];
	FileNameTxt(filename, order1.walletId,modif);
	if (!CheckThereFileExist(filename))
	{
		MakeTextFile(filename);
	}
	if (!CheckThereFileExist(fisrtnamefile))
	{
		if (SaveOrderToFile(secondnamefile, order1))
		{
			std::cout << "Unfortunately at the momment there is no a proper order for completing the yours!\n";
			std::cout << "When your order is fully complete you will be informed\n";
		}
		else
			std::cout << "There was a problem while operating with orders!\n";
		return;
	}
	else
	{
		if (!SaveOrderToFile(secondnamefile, order1))
		{
			std::cout << "There was a problem while operating with orders!\n";
			return;
		}

		////////////////////////////
		for (size_t i = 0; CheckThereFileExist(fisrtnamefile) && NotComplete; i++)
		{
			std::fstream f;
			f.open(fisrtnamefile, std::ios::out | std::ios::in | std::ios::binary);
			//щом сме стигнали до тук то със сигруност има нареждане за покупка
			if (!f.is_open())
			{
				std::cout << "Error while openning orders-BUY file\n";
				return;
			}
			Order order2;
			f.read((char*)&order2, sizeof(order2));//записваме го
			f.close();
			//очертават се 6 възможни ситуации
			if (abs(order1.fmiCoins - order2.fmiCoins) < EPS && !strcmp(modif, "IDB-"))//the both orders will be complete
			{
				if (!CompleteOrder(order2, order1, filename, 3))
				{
					std::cout << "Closing the procedure!\n";
					return;
				}
				NotComplete = false;
			}
			else if (abs(order1.fmiCoins - order2.fmiCoins) < EPS && !strcmp(modif, "IDS-"))
			{
				if (!CompleteOrder(order1, order2, filename, 3))
				{
					std::cout << "Closing the procedure!\n";
					return;
				}
				NotComplete = false;

			}
			else if (order1.fmiCoins > order2.fmiCoins && strcmp(modif,"IDB-"))//BUY < SELL and is ENTER SELL order
			{
			
				if (!CompleteOrder(order1, order2, filename, 1))
				{
					std::cout << "Closing the procedure\n!";
					return;
				}
				order1.fmiCoins -= order2.fmiCoins;//the SELL order is decrease

			}
			else if (order1.fmiCoins < order2.fmiCoins && strcmp(modif, "IDS-"))///BUY < SELL and is ENTER BUY order
			{

				if (!CompleteOrder(order2, order1, filename, 1))
				{
					std::cout << "Closing the procedure!\n";
					return;					
				}
				NotComplete = false;
			}
			else if (order1.fmiCoins < order2.fmiCoins &&!strcmp(modif, "IDS-"))//BUY > SELL and is ENTER SELL order
			{

				if (!CompleteOrder(order1, order2, filename, 2))
				{
					std::cout << "Closing the procedure!\n";
					return;
				}
				NotComplete = false;
				
			 }
			else if (order1.fmiCoins > order2.fmiCoins &&!strcmp(modif, "IDB-"))//BUY > SELL and is ENTER BYU order
			{

				if (!CompleteOrder(order2, order1, filename, 2))
				{
					std::cout << "Closing the procedure!\n";
					return;
				}
				order1.fmiCoins -= order2.fmiCoins;//the BUY order is decrease
			}
			else
				std::cout << "Something wrong!/n";
		}
	}
	if (!NotComplete)
		std::cout << "You order is entirely complete!\n";
	else
		std::cout << "You order is partially complete!\n";
}