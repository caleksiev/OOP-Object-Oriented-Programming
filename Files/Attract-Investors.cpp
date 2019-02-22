#define _CRT_SECURE_NO_WARNINGS 1
#include"Attract-Investors.h"
#include"Transaction.h"
#include<ctime>
#include<fstream>
#include<iostream>
//temp functions

//1)
//the function become the ID of the wallets and open the file transaction.dat
//and for every ID in this tranasaction is calculate the total sum of coins
//the number of transaction and the first and the last date of the firrt and the last trans
//the result is return as struct Top10
Top10 ExtractInfoTop10(size_t ID);

//2)
///this is the standart SELECTION SORT algorithm///
//swap two structs
void swap(Top10& t1, Top10& t2);

//3)
//search the index of the max struct,that contains the max coins
size_t IndexOfMaxCoins(const Top10*top, size_t beg, size_t end);


void WriteDataInStruct(Top10*arr, size_t ID)
{
	for (size_t i = 1; i <= ID; i++)
	{
		Top10 temp = ExtractInfoTop10(i);
		arr[i - 1] = temp;
	}
}

void Sort(Top10*top, size_t length)
{
	size_t conditon = ((length < 10) ? length : 10);
	for (size_t i = 0; i < conditon; i++)//the fisrt 10
	{
		swap(top[i], top[IndexOfMaxCoins(top, i, length)]);
	}
}
void PrintInformation(const Top10*top, size_t length)
{
	std::cout << "The list of the top 10 richers:\n";
	size_t conditon = ((length < 10) ? length : 10);
	for (size_t i = 0; i < conditon; i++)
	{
		const char*time1 = std::asctime(std::localtime(&top[i].firtsTime));
		const char*time2 = std::asctime(std::localtime(&top[i].secTime));
		std::cout << i + 1 << ":"
			<< "Coins: " << top[i].coins
			<< "//Transactions: " << top[i].cntTrans
			<< "//Firts tran: " << time1
			<< "//Last tran: " << time2 << ".\n";
	}
}

Top10 ExtractInfoTop10(size_t ID)
{
	Top10 top;
	time_t since_1970 = time(0);
	Transaction tran;
	top.coins = 0;
	top.cntTrans = 0;
	std::fstream f;
	f.open("transactions.dat", std::ios::in | std::ios::binary);
	while (f.good())
	{
		f.read((char*)&tran, sizeof(tran));
		if (tran.receiverId == ID && f.good())
		{
			if (tran.senderId == INVALID_ID)
				top.firtsTime = tran.time;//the firts transaction is when the wallet is created
			if (tran.senderId != INVALID_ID)
				++top.cntTrans;
			top.coins += tran.fmiCoins;
			top.secTime = tran.time;
		}
	}
	f.close();
	return top;
}

void swap(Top10& t1, Top10& t2)
{
	Top10 temp = t1;
	t1 = t2;
	t2 = temp;
}

size_t IndexOfMaxCoins(const Top10*top, size_t beg, size_t end)
{
	size_t max = beg;
	for (size_t i = beg + 1; i < end; i++)
	{
		if (top[max].coins < top[i].coins)
			max = i;
	}
	return max;
}