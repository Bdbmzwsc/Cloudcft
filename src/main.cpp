#include <iostream>
#include <defineToken.h>
#include <parser.hpp>
#include <tree.hpp>
using namespace std;
int main()
{
    cout << "helloworld" << endl;
    string c = "namespace abcd    {}";
    parser p;
    pair<treestm::SourceCode, string> ast = p.parse(c);
    cout << ast.first.Namespaces.name << endl;

    return 0;
}