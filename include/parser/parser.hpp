#include <defineToken.h>
#include <iostream>
#include <string>
#include <vector>
#include <lexer.hpp>
#include <tree.hpp>
#include <Namespace.hpp>
using namespace std;
class parser{
public:
    pair<treestm::SourceCode,string> parse(string code){
        lexer Lexer(code);
        pair<treestm::Namespace,string> src=parseNamespace(&Lexer);
        treestm::SourceCode sourcec;
        sourcec.Namespaces=src.first;
        
        Lexer.nexttokenIs(TOKEN_EOF);
        return make_pair(sourcec,"");
    }
    
    
};