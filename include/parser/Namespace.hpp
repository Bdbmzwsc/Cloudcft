#include <defineToken.h>
#include <iostream>
#include <string>
#include <vector>
#include <lexer.hpp>
#include <tree.hpp>
#include <parseToken.hpp>
using namespace std;
#ifndef parseNamesp
#define parseNamesp
pair<treestm::Namespace,string> parseNamespace(lexer *Lexer){
         
    Lexer->LookAheadAndSkip(KONG_GE);

    Lexer->nexttokenIs(TOKEN_NAMESPACE);
    Lexer->nexttokenIs(KONG_GE);
    //cout<<"123123123"<<endl;
    string name=parseName(Lexer);
    Lexer->LookAheadAndSkip(KONG_GE);
    Lexer->nexttokenIs(TOKEN_ZUOHUAKUO);
    Lexer->LookAheadAndSkip(KONG_GE);

    Lexer->LookAheadAndSkip(KONG_GE);
    Lexer->nexttokenIs(TOKEN_RIGHTHUAKUO);
    treestm::Namespace namesp;
    namesp.name=name;
    return make_pair(namesp,"");
}
#endif


