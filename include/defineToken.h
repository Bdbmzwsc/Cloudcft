#define C const int
#include <map>
using namespace std;
#ifndef defineToken.h
#define defineToken .h
extern C TOKEN_NUM = 0;
extern C TOKEN_EOF = 1;
extern C TOKEN_VAR = 2; // [_A-Za-z][_0-9A-Za-z]*
extern C TOKEN_DENG = 3;
extern C TOKEN_NUMBER = 4; //^[0-9]*$
extern C KUO = 5;
extern C KONG_GE = 6;
extern C TOKEN_YINHAO = 7;
extern C TOKEN_STR = 8;
extern C TOKEN_DUOYINHAO = 9;
extern C TOKEN_RIGHT_KUOHAO = 10;
extern C TOKEN_SMT_END = 11;
extern C TOKEN_STR_TYPE = 12;
extern map<int, string> tokenNameMap = {
	{TOKEN_NUM, "num"},
	{TOKEN_EOF, "EOF"},
	{TOKEN_VAR, "var"},
	{TOKEN_DENG, "="},
	{TOKEN_NUMBER, "number"},
	{KUO, "("},
	{KONG_GE, " "},
	{TOKEN_YINHAO, "\""},
	{TOKEN_STR, "str"},
	{TOKEN_DUOYINHAO, "\"\""},
	{TOKEN_STR_TYPE, "string"}};
extern map<string, int> tokenwordmap = {
	{"num", TOKEN_NUM},
	{"string", TOKEN_STR_TYPE}};
#endif