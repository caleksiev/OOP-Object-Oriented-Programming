#ifndef _INCLUDED_INVENTORS_
#define _INCLUDED_INVENTORS_
struct Top10
{
	long long firtsTime;
	long long secTime;
	unsigned cntTrans;
	double coins;
};
/*
in dynamic array of structs with exact size 
are write all of the until registrated users
with the respective one data of the struct Top10
*/
void WriteDataInStruct(Top10*arr, size_t ID);

/*
Using Selection Sort the function find the firts 10 structs 
with the biggest value of coins
*/
void Sort(Top10*top, size_t length);

//Print to the console  the respective one sorted data
void PrintInformation(const Top10*top, size_t length);
#endif