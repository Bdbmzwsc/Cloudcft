#include <iostream>
#include <string>
#include <vector>
using namespace std;
#ifndef tree.hpp
#define tree .hpp
class treestm{
public:
    struct AssignmentVar
    {
        int type;
        string name;
        string value;
    };
    
    struct Statement
    {
        int type;
    };
    struct Function
    {
        string name;
        int type;
        vector<Statement> Statements;
    };
    
    struct Class
    {
        string name;
        vector<Function> Functions;
    };
    struct Namespace
    {
        string name;
        vector<Class> classes;
    };
    
    struct SourceCode
    {
        Namespace Namespaces;
    };
};
#endif