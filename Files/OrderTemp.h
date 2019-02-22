#ifndef _ORDERTEMP_INCLUDED_
#define _ORDERTEMP_INCLUDED_
//temp functions for making OREDER

/*
THIS IS THE "MAIN" FUNCTION that connect all process using the funtion below!
1)Reflects the transaction of SELLER in his file
2)Reflects the transaction of BUY in his file
3)Deduct the current order from "SELL-orders" or ("BUY-orders"),if one of them is still not complete
4)Remove from "SELL-orders" or ("BUY-orders") the current complete order,or the both order is they are complete
5)Make a transaction of BUYER or SELLER,according of their status
6)Reflects the change of real money of both sides,according of the order's status
IN EVERY OF THIS 6 STEPS THE FUNCTION taka and one parametes -flag,to can understand what to do in every situations:
flag-1:the BUY order is completing,SELL not
flad-2:the SELL order is completing,BUY not
flag-3:the boths orders of SELLER and BUYER are completing
*/
bool CompleteOrder(const Order& sell, const Order& buy, char*filename, unsigned flag);

/*
1)Text Files
the text files for orderer are created in the following format:
IDB-*id* - for buyer with his *id*
IDS-*is* - for seller with his *id*
to create the file the program use the following 4 functions:
*/

size_t CntDigit(size_t num);
/*
the functions convert the ID in string and save it in the array
as in advance count the ID digits
*/
void ConvertNumToStr(char*str, unsigned int num);

/*
in the array-filename is write the name of the text file
first is wtite the "IDS-" or "IDB-" according for who is opening the file(buyer or seller)
then concatenatå the already converted string ,that contain ID
and at lats the file extension ".txt"
*/
void FileNameTxt(char*filename, unsigned walletID, const char*str);

/*
Once it's created the name of file,then is creating the text file,
in which is writting the data of the file's creation
if the process is not complete the nuction return false
else true
*/
bool MakeTextFile(const char*filename);

//the standart funtion that check or one file is exist
bool CheckThereFileExist(const char*fname);

/*
in file "SELL-orders" or in file "BUY-orders"
are store the current order at the end of file
if a errors occurs while operatig the file the function
return false,else true
*/
bool SaveOrderToFile(const char*filename, const Order& sell);

/*
the function open the dat file- "SELL-orders" or ("BUY-orders")
and searched the order of SELLER or (BUYER)
when it's find the order,the current coins there are decrease and
write to the file/if there was a problems with file the returned value is false
*/
bool DecreaseFMoneyfile(const Order& order1, const Order& order2, const char*filename);

size_t FileSize(std::fstream& f);
/*
the function open the dat file- "SELL-orders" or ("BUY-orders")
and find how many orders of type SELL or (BUY) are strored in file
if the cnt of them is 1 or 0 the file is deleted,couse the only one order is already complete
else it is created a dynamic array of structs where it's stored the information of the other
orders without the complete one and then this orders are save to the file
if the file is not open or the memmory alocation is failed,its is returned false
*/
bool RemoveOrderFromFile(const Order& orderer, const char*filename);

/*
after every change by order, completed or not,is making a transaction in transactions.dat file
the feature is at coins,according of the type of order and or is completed or not/
one of the argument is a char,there are 4 opportunities:
1) char=='b',the order of buyer is complete and receive all coins of the order
2) char=='s',the order of seller is complete and his coins are decrese with the value of whole order
3) char=='o',the order of seller is NOT complete and and his coins are decrease with the value of a PART of order
4) char== else,the order of buyer is NOT complete and receive a PART of coins of the order
if occurs a error the functin return false
*/
bool MakeTransaction(const Order& order1, const Order& order2, char type);

/*
after every order,completed or not are changing the real money of both sides(SELLER,BUYER)
to understand the function,how much to decrease or increase to orderer,it take two temp parametårs-
1)operations:
-a)"+",that means  it will increase money
-b)"-",that means it will decrease money
2)flag:
-a)"1",that means that the BUY order is complete,but SELL is not,BUYER receive all money,SELLER a part
-b)"2",that means that the SELL order is complete,but BUY is not,SELLER receive all money,BUYER a part
-c)"3",that means that the both orders are complete and the orderer receive all of the money
if occurs a error the function return false
*/
bool ChangeWalletMoney(const Order& order1, const Order& order2, char operation, size_t flag);

#endif 
