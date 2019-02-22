#include"Wallet.h"
#include"fstream"
#include<iostream>


void CheckTheCurrWalletID(size_t& id, Wallet& wall)
{
	std::fstream f;
	f.open("wallets.dat", std::ios::in | std::ios::binary);
	if (!f.is_open())//the file does not exist
	{
		id = 0;
		f.close();
	}
	else
	{
		f.seekg(0, std::ios::end);//we go to the end of the file
		f.seekg((-1 * (int)sizeof(wall)), std::ios::end);//and move back to the last stored struct
		f.read((char*)&wall, sizeof(wall));//we write the data into the new one struct and extract the id
		id = wall.id;
		f.close();
	}
}

void ExtractDataFromInput(Wallet& wall, size_t& id, char*command)
{
	wall.id = ++id;
	std::cin >> wall.fiatMoney;
	char x = std::cin.get();
	while (x == ' ')
		x = std::cin.get();
	std::cin.unget();
	std::cin.getline(wall.owner, MAX_NAMELEN);
}

void AddWallets(const Wallet&wall)
{
	std::fstream wallets;
	wallets.open("wallets.dat", std::ios::out | std::ios::binary | std::ios::app);
	if (!wallets.is_open())//we should not enter here,because the flag ios::out is set
	{
		std::cerr << "A problem while opening the file wallets.dat";
		return;
	}
	wallets.write((const char*)&wall, sizeof(wall));
	if (!wallets.good())
	{
		return;
		std::cout << "Error while writting on file";
	}
	wallets.close();
}
bool FindIDinWalletsFile(size_t search, Wallet&wall)
{
	std::fstream f;
	f.open("wallets.dat", std::ios::in | std::ios::binary);
	if (!f.is_open())
		return false;
	f.seekg(0, std::ios::end);//return file pointer to the end of file
	f.seekg(-1 * (int)sizeof(wall), std::ios::end);//and to the last struct
	size_t size = (size_t)f.tellg();//we save the position of the index
	size /= sizeof(wall);//and calculet the strict value
	if (search > size + 1)//the is si still not generated,not exist
	{
		f.close();
		return false;
	}
	f.seekg(0, std::ios::beg);
	f.seekg((search - 1) * sizeof(wall), std::ios::beg);
	f.read((char*)&wall, sizeof(wall));
	if (!f)
	{
		f.close();
		return false;
	}
	f.close();
	return true;
}
bool EnoughMoney(double coins, size_t ID)
{
	Wallet wall;
	std::fstream f;
	f.open("wallets.dat", std::ios::binary | std::ios::in);
	f.seekg((ID - 1) * sizeof(wall), std::ios::beg);
	f.read((char*)&wall, sizeof(wall));
	if (wall.fiatMoney - coins*375 >= EPS)
		return true;
	return false;
}