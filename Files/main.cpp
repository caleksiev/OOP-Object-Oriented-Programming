#include"Wallet.h"
#include"Transaction.h"
#include"Order.h"
#include"Attract-Investors.h"
#include<iostream>
//съжалявам за лошия английски по коментарите :(
int main()
{
	char command[MAX_COMMAND];
	Wallet wall = { 0, };
	Transaction tran = { 0, };
	Order ord{ Order::INVALID,0,0 };
	size_t id;
	CheckTheCurrWalletID(id, wall);
	std::cout << "The program expected correct input!\n";
	std::cout <<"Registeres users:"<< id<<std::endl;

	while (true)
	{
		std::cout << "Enter command:";
		std::cin >> command;
		if (!strcmp(command, "add-wallet"))
		{
			ExtractDataFromInput(wall, id, command);
			AddWallets(wall);
			AddTrans(tran,wall);
			std::cout << "Your wallet was added to the system!\n";
		}
		else if (!strcmp(command, "wallet-info"))
		{
			size_t walletID;
			std::cin >> walletID;
			if (FindIDinWalletsFile(walletID, wall))
			{
				double totalFMIcoin = FindFmiCoinTransFile(walletID);
				if (totalFMIcoin >= 0) //there is no problem with file
				{
					std::cout << "Information about wallet with id " << walletID << "\n";
					std::cout << "Name: " << wall.owner << std::endl;
					std::cout << "Real money: " << wall.fiatMoney << std::endl;
					std::cout << "FMI:Coins: " << totalFMIcoin << std::endl;
				}
			}
			else
				std::cout << "There is no a wallet with this ID!\n";
		}
		else if (!strcmp(command, "make-order"))
		{
			char tcomand[MAX_TYPELEN + 1];
			std::cin >> tcomand;
			if (!strcmp(tcomand, "SELL"))
			{
				double coins; std::cin >> coins;
				size_t ID; std::cin >> ID;
				if (FindIDinWalletsFile(ID, wall) && isOrdererHasAlreadyOrder(ID,"orders-SELL.dat"))//if the wallet exist
				{
					double availCoins = FindFmiCoinTransFile(ID);
					if (availCoins >= 0 && availCoins - coins >= EPS)
					{
						ord.fmiCoins = coins;
						ord.walletId = ID;
						ord.type = Order::SELL;
						CompletingOrder(ord, "orders-BUY.dat", "orders-SELL.dat","IDS-");
					}
					else
						std::cout << "The owner not have enough coins to do the operation\n";
				}
				else
					std::cout << "The wallet not exist or the orderer have already other uncomplete order!\n";
			}
			else if (!strcmp(tcomand, "BUY"))
			{
				double coins; std::cin >> coins;
				size_t ID; std::cin >> ID;
				if (FindIDinWalletsFile(ID, wall) && isOrdererHasAlreadyOrder(ID, "orders-SELL.dat"))//if the wallet exist
				{
					if (EnoughMoney(coins,ID))
					{
						ord.fmiCoins = coins;
						ord.walletId = ID;
						ord.type = Order::BUY;
						CompletingOrder(ord,"orders-SELL.dat","orders-BUY.dat" ,"IDB-");
					}
					else
						std::cout << "The owner not have enough money to do the operation\n";
				}
				else
					std::cout << "The wallet not exist or the orderer have already other uncomplete order!\n";
			}
			else
			{
				std::cin.clear();
				std::cin.sync();
			}
		}
		else if (!strcmp(command, "attract-investors"))
		{
			Top10*arr = new(std::nothrow)Top10[id];
			if (!arr)
			{
				std::cout << "No memmory for save the attract-investors!\n";
				return -1;
			}
			WriteDataInStruct(arr, id);
			Sort(arr, id);
			PrintInformation(arr, id);
			delete arr;
		}
		else if (!strcmp(command, "quit"))
		{
			std::cout << "You quit the program!!\n";
			break;
		}
		else 
		{
			std::cin.clear();
			std::cin.sync();
			std::cout << "Unknwon command!Try again!\n";
		}
	}
	return 0;
}