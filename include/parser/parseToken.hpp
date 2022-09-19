#include <defineToken.h>
#include <iostream>
#include <string>
#include <vector>
#include <lexer.hpp>
#include <tree.hpp>
using namespace std;
string parseName(lexer *Lexer){
    pair<int,string> name=Lexer->nexttokenIs(TOKEN_VAR);
    return name.second;
}


