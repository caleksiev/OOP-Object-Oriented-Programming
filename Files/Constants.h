#ifndef _HEADER_CONST_INCLUDED_
#define _HEADER_CONST_INCLUDED_
//åxpected only 5 commands-"make-order","add-wallet","wallet-info","quit","attract-investors"
const unsigned int MAX_COMMAND = 18;

//for commands "SELL","BUY"
const unsigned int MAX_TYPELEN = 4;

//for cmp double numbers
const  double EPS = 0.00001;

//max len of the wallet owner
const unsigned int MAX_NAMELEN = 256;

//for created file's name
const unsigned MAX_FILENAME = 15;

//by condition
const unsigned int RAND_NUM = 375;

//invalid ID of transaction
const unsigned long INVALID_ID = 4294967295;

#endif 

