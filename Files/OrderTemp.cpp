#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<fstream>
#include"ctime"
#include"Order.h"
#include"Transaction.h"
#include"OrderTemp.h"

bool CompleteOrder(const Order& sell, const Order& buy, char*filename, unsigned flag)
{
	//1)отразяваме транзакцията в текстовия файл на продавача
	FileNameTxt(filename, sell.walletId, "IDS-");
	std::fstream f;
	f.open(filename, std::ios::out | std::ios::app);
	if (!f.is_open())
	{
		std::cout << "Error while openning orders-SELL-text file\n";
		return false;
	}
	Wallet walls, wallb;//записваме съотвентине данни за портфейлите на продавача и на купувача
	if (FindIDinWalletsFile(sell.walletId, walls) && FindIDinWalletsFile(buy.walletId, wallb))
	{
		switch (flag)
		{
		case 1:
		{
			f << "\n" << "Reciver name:" << walls.owner << "//";
			f << "Sendler name:" << wallb.owner << "//";
			f << "Transfered money:" << -buy.fmiCoins << " coins." << "/n";
			f << "Your coins are deacrease:" << buy.fmiCoins << " coins." << "\n";
			f << "But your money are increase with " << buy.fmiCoins * RAND_NUM << " levs.";
			break;
		}
		case 2:
		{
			f << "\n" << "Reciver name:" << walls.owner << "//";
			f << "Sendler name:" << wallb.owner << "//";
			f << "Transfered money:" << -sell.fmiCoins << " coins." << "\n";
			f << "Your coins are deacrease:" << sell.fmiCoins << " coins." << "\n";
			f << "But your money are increase with " << sell.fmiCoins * RAND_NUM << " levs." << "\n";
			f << "Your order is complete!Check out your wallet for the total sum!";

			break;
		}
		case 3:
		{
			f << "\n" << "Reciver name:" << walls.owner << "//";
			f << "Sendler name:" << wallb.owner << "//";
			f << "Transfered money:" << -buy.fmiCoins << " coins." << "\n";
			f << "Your coins are deacrease:" << sell.fmiCoins << " coins." << "\n";
			f << "But your money are increase with " << sell.fmiCoins * RAND_NUM << " levs." << "\n";
			f << "Your order is complete!Check out your wallet for the total sum!";
			break;
		}

		}
		f.close();
	}
	else
	{
		std::cout << "There was a problem with wallets data\n!";
		return false;
	}
	//2)Отразяваме транзакцията в текстовия файл на купувача
	FileNameTxt(filename, buy.walletId, "IDB-");
	if (!CheckThereFileExist(filename))
	{
		MakeTextFile(filename);
	}
	f.open(filename, std::ios::out | std::ios::in | std::ios::app);
	if (!f.is_open())
	{
		std::cout << "Error while opening the text file BUY-orders\n";
		return false;
	}
	switch (flag)
	{
	case 1:
	case 3:
	{
		f << "\n" << "Reciver name:" << wallb.owner << "//";
		f << "Sendler name:" << walls.owner << "//";
		f << "Transfered money:" << buy.fmiCoins << " coins." << "\n";
		f << "Your coins are increase:" << buy.fmiCoins << " coins." << "\n";
		f << "But your money are decrease with" << buy.fmiCoins * RAND_NUM << " levs." << "\n";
		f << "Your order is complete!Check out your wallet for the total sum!";
		break;
	}
	case 2:
	{
		f << "\n" << "Reciver name:" << wallb.owner << "//";
		f << "Sendler name:" << walls.owner << "//";
		f << "Transfered money:" << sell.fmiCoins << " coins." << "\n";
		f << "Your coins are increase:" << sell.fmiCoins << " coins." << "\n";
		f << "But your money are increase with" << sell.fmiCoins * RAND_NUM << " levs." << "\n";
		break;
	}
	}
	f.close();

	//3)Приспадаме в списъка с нареждания  текущата продажба или текушата покупка
	switch (flag)
	{
	case 1:
	{
		if (!DecreaseFMoneyfile(sell, buy, "orders-SELL.dat"))
		{
			std::cout << "Error while decreasing the SELL-order!\n";
			return false;
		}

		break;
	}
	case 2:
	{
		if (!DecreaseFMoneyfile(buy, sell, "orders-BUY.dat"))
		{
			std::cout << "Error while decreasing the BUY-order!\n";
			return false;
		}
		break;
	}
	case 3: {; }//both orders are complete there is nothing for decrease
	}
	//4)Премахване на нареждането от файла с нарежданията за покупка или за продажба или и за двете
	switch (flag)
	{
	case 1:
	{
		if (!RemoveOrderFromFile(buy, "orders-BUY.dat"))
		{
			std::cout << "Error while removing the buy order form file!\n";
			return false;
		}
		break;
	}
	case 2:
	{
		if (!RemoveOrderFromFile(sell, "orders-SELL.dat"))
		{
			std::cout << "Error while removing the SELL order form file!\n";
			return false;
		}
		break;
	}
	case 3:
	{
		if (!RemoveOrderFromFile(sell, "orders-SELL.dat") || !RemoveOrderFromFile(buy, "orders-BUY.dat"))
		{
			std::cout << "Error while removing the SELL and BUY order form file!\n";
			return false;
		}
		break;
	}
	}
	//5))Транзакция на купувача и продавача
	switch (flag)
	{
	case 1:
	{
		if (!MakeTransaction(sell, buy, 'b') || !MakeTransaction(buy, sell, 'o'))
		{
			std::cout << "There was a problem while making a transaction of a buyer and seller!\n ";
			return false;
		}
		break;
	}
	case 2:
	{
		if (!MakeTransaction(buy, sell, 's') || !MakeTransaction(sell, buy, 'p'))
		{
			std::cout << "There was a problem while making a transaction of a buyer and seller!\n ";
			return false;
		}
		break;
	}
	case 3:
	{
		if (!MakeTransaction(buy, sell, 's') || !MakeTransaction(sell, buy, 'b'))
		{
			std::cout << "There was a problem while making a transaction of a buyer and seller!\n ";
			return false;
		}
		break;
	}
	}
	//6 Промяна на истинките пари
	switch (flag)
	{
	case 1:
	{
		if (!ChangeWalletMoney(sell, buy, '+', 1) || (!ChangeWalletMoney(sell, buy, '-', 1)))
		{
			std::cout << "Error while changing money of SELLER and BUYER\n";
			return false;
		}
		break;
	}
	case 2:
	{
		if (!ChangeWalletMoney(sell, buy, '+', 2) || (!ChangeWalletMoney(sell, buy, '-', 2)))
		{
			std::cout << "Error while changing money of SELLER and BUYER\n";
			return false;
		}
		break;
	}
	case 3:
	{
		if (!ChangeWalletMoney(sell, buy, '+', 3) || !(ChangeWalletMoney(sell, buy, '-', 3)))
		{
			std::cout << "Error while changing money of SELLER and BUYER\n";
			return false;
		}
		break;
	}
	}
	return true;

}
size_t CntDigit(size_t num)
{
	size_t cnt = 0;
	while (num)
	{
		++cnt;
		num /= 10;
	}
	return cnt;
}
void ConvertNumToStr(char*str, unsigned int num)
{
	size_t length = CntDigit(num);
	str[length] = '\0';
	for (int i = length - 1; i >= 0; i--)
	{
		char curNum = (num % 10) + '0';
		str[i] = curNum;
		num /= 10;
	}
}
void FileNameTxt(char*filename, unsigned walletID, const char*str)
{
	char convNum[MAX_FILENAME];
	ConvertNumToStr(convNum, walletID);
	strcpy(filename, str);
	strcat(filename, convNum);
	strcat(filename, ".txt");
}
bool MakeTextFile(const char*filename)
{
	std::fstream f;
	f.open(filename, std::ios::out);
	if (!f.is_open())
		return false;
	std::time_t since_1970 = std::time(nullptr);
	const char*str = std::asctime(std::localtime(&since_1970));
	f << str;
	if (!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}

bool CheckThereFileExist(const char*fname)
{
	std::fstream file;
	file.open(fname, std::ios::in, std::ios::binary);
	if (!file.is_open())
		return false;
	else
		return true;
}

bool SaveOrderToFile(const char*filename, const Order& sell)
{
	std::fstream f;
	f.open(filename, std::ios::out | std::ios::binary | std::ios::app);
	if (!f.is_open())
	{
		std::cout << "Error while opening the file\n";
		return false;
	}
	f.write((const char*)&sell, sizeof(sell));
	if (!f.good())
	{
		f.close();
		std::cout << "Error while writting on file!\n";
		return false;
	}
	f.close();
	return true;
}

bool DecreaseFMoneyfile(const Order& order1, const Order& order2, const char*filename)
{
	std::fstream f;
	f.open(filename, std::ios::out | std::ios::in | std::ios::binary);
	if (!f.is_open())
		return false;
	while (f.good())
	{
		Order cur;
		f.read((char*)&cur, sizeof(cur));
		if (cur.walletId == order1.walletId && f.good())
		{
			/*f.seekp((f.tellg()), std::ios::beg);*/ //the rigth way to do this is with this line
													 //but in this case the buffer is one by default,and it not necessary :)
			f.seekp(-1 * (int)sizeof(Order), std::ios::cur);
			cur.fmiCoins = order1.fmiCoins - order2.fmiCoins;
			f.write((const char*)&cur, sizeof(cur));
			f.clear();
			f.close();
			return true;
		}
	}
	return false;//we should not enter here
}

size_t FileSize(std::fstream& f)
{
	f.seekg(0, std::ios::end);
	size_t sizef = (size_t)f.tellg();
	f.seekg(0, std::ios::beg);
	return sizef;
}
bool RemoveOrderFromFile(const Order& orderer, const char*filename)
{
	std::fstream f;
	f.open(filename, std::ios::binary | std::ios::in);
	if (!f.is_open())
		return false;
	size_t sizef = FileSize(f);
	size_t length = sizef / sizeof(Order);
	if (!(length - 1) || !length)
	{
		f.close();
		remove(filename);
		return true;
	}
	else
	{
		Order*orders = new(std::nothrow)Order[length - 1];
		if (!orders)
		{
			std::cout << "Error while deleting the order\n";
			return false;
		}
		for (size_t i = 0; f.good();)
		{
			Order temp;
			f.read((char*)&temp, sizeof(temp));
			if (temp.walletId != orderer.walletId && f.good())
			{
				orders[i] = temp;
				++i;
			}
		}
		f.close();
		f.open(filename, std::ios::binary | std::ios::out);
		for (size_t i = 0; i < length - 1 && f.good(); i++)
		{
			f.write((const char*)&orders[i], sizeof(orders[i]));
		}
		delete orders;
		f.close();
		return true;
	}
}

bool MakeTransaction(const Order& order1, const Order& order2, char type)
{
	std::fstream f;
	f.open("transactions.dat", std::ios::binary | std::ios::app | std::ios::out);
	if (!f.is_open())
		return false;
	Transaction tran;
	if (type == 'b')
		tran.fmiCoins = order2.fmiCoins;
	else if (type == 's')
		tran.fmiCoins = -order2.fmiCoins;
	else if (type == 'o')
		tran.fmiCoins = -order1.fmiCoins;
	else
		tran.fmiCoins = order1.fmiCoins;
	tran.receiverId = order2.walletId;
	tran.senderId = order1.walletId;
	time_t seconds_1970 = time(0);
	tran.time = seconds_1970;
	f.write((const char*)&tran, sizeof(tran));
	if (!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}

bool ChangeWalletMoney(const Order& order1, const Order& order2, char operation, size_t flag)
{
	std::fstream f;
	f.open("wallets.dat", std::ios::binary | std::ios::in | std::ios::out);
	if (!f.is_open())
		return false;
	while (f.good())
	{
		Wallet wall;
		f.read((char*)&wall, sizeof(wall));
		if (operation == '+' && flag >= 2 && wall.id == order1.walletId)
		{
			f.seekp(-1 * (int)sizeof(Wallet), std::ios::cur);
			wall.fiatMoney += order1.fmiCoins * RAND_NUM;
			f.write((const char*)&wall, sizeof(wall));
			f.close();
			return true;
		}
		if (operation == '-' && flag >= 2 && wall.id == order2.walletId)
		{
			f.seekp(-1 * (int)sizeof(Wallet), std::ios::cur);
			wall.fiatMoney -= order1.fmiCoins * RAND_NUM;
			f.write((const char*)&wall, sizeof(wall));
			f.close();
			return true;
		}
		if (operation == '+' && flag == 1 && wall.id == order1.walletId)
		{
			f.seekp(-1 * (int)sizeof(Wallet), std::ios::cur);
			wall.fiatMoney += order2.fmiCoins * RAND_NUM;
			f.write((const char*)&wall, sizeof(wall));
			f.close();
			return true;
		}
		if (operation == '-' && flag == 1 && wall.id == order2.walletId)
		{
			f.seekp(-1 * (int)sizeof(Wallet), std::ios::cur);
			wall.fiatMoney -= order2.fmiCoins * RAND_NUM;
			f.write((const char*)&wall, sizeof(wall));
			f.close();
			return true;
		}
	}
	return false;
}
