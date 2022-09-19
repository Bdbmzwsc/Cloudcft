#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <defineToken.h>
using namespace std;
#ifndef ler.hpp
#define ler.hpp
class lexer
{
private:
	string src;
	int line;
	int nexttokentype;
	int nexttokenline;
	string nexttoken;

public:
	lexer(string code)
{
	src = code;
	line = 1;
	nexttokenline = 0;
	nexttokentype = 1;
}
	//~lexer();

public:
	// assert what the  token is,and skip this token
	pair<int, string> nexttokenIs(int TokenType)
	{
		tuple<int, int, string> res = Getnexttoken();
		int nowline, nowTokenType;
		string nowToken;
		tie(nowline, nowTokenType, nowToken) = res;
		// syntax error
		if (TokenType != nowTokenType)
		{
			cout << "error at nexttokenIs" << nowTokenType << endl;
			throw "error at nexttokenIs";
		}
		return make_pair(nowline, nowToken);
	}
	// get what the token is,dont skip this token.
	int LookAhead()
	{
		// lexer.nexttoken* already setted
		if (nexttokenline > 0)
			return nexttokentype;
		// set it
		int nowline = line;
		tuple<int, int, string> res = Getnexttoken();
		int ln, tokenType;
		string token;
		tie(ln, tokenType, token) = res;
		line = nowline;
		nexttokenline = ln;
		nexttokentype = tokenType;
		nexttoken = token;
		return tokenType;
	}
	// if the token is expectedType,skip the token,or dont
	void LookAheadAndSkip(int expectedType)

	{
		// get next token
		int nowline = line;
		tuple<int, int, string> res = Getnexttoken();
		int ln, tokenType;
		string token;
		std::tie(ln, tokenType, token) = res;
		//	cout<<token<<endl;
		// not is expected type, reverse cursor
		if (tokenType != expectedType)
		{
			line = nowline;
			nexttokenline = ln;
			nexttokentype = tokenType;
			nexttoken = token;
		}
	}
	// get token
	tuple<int, int, string> Getnexttoken()
	{
		if (nexttokenline > 0)
		{
			int ln = nexttokenline;
			line = nexttokenline;
			nexttokenline = 0;
			//cout<<nexttoken<<endl;
			return make_tuple(ln, nexttokentype, nexttoken);
		}
		return MatchToken();
	}
	tuple<int, int, string> MatchToken()
	{

		//	cout<<src[0]<<endl;
		// check ignored
	//	cout<<nexttokentype<<endl;
		if (isIgnored())
			return make_tuple(line, KONG_GE, tokenNameMap[KONG_GE]);
		// finish
		if (src.length() == 0)
			return make_tuple(line, TOKEN_EOF, tokenNameMap[TOKEN_EOF]);
		// cout<<src[0]<<endl;
		//  check token
		switch (src[0])
		{
			/*	case '%':
					skipsrc(1);
					return make_tuple(line, TOKEN_NUM, "%");*/
		case '(':
			skipsrc(1);
			return make_tuple(line, KUO, tokenNameMap[KUO]);
		case ')':
			skipsrc(1);
			return make_tuple(line, TOKEN_RIGHT_KUOHAO, tokenNameMap[TOKEN_RIGHT_KUOHAO]);
		case '=':
			skipsrc(1);
			return make_tuple(line, TOKEN_DENG, tokenNameMap[TOKEN_DENG]);
		case '"':
			if (next_code(tokenNameMap[TOKEN_DUOYINHAO]))
			{
				skipsrc(2);
				return make_tuple(line, TOKEN_DUOYINHAO, tokenNameMap[TOKEN_DUOYINHAO]);
			}
			skipsrc(1);
			return make_tuple(line, TOKEN_YINHAO, "\"");
		case ';':
			skipsrc(1);
			return make_tuple(line, TOKEN_SMT_END, ";");
		case 'n':
			
			if (src[1] == 'u' && src[2] == 'm')
			{
				skipsrc(3);
				cout << src;
				return make_tuple(line, TOKEN_NUM, "num");
			}	
			
			if (next_code("namespace"))
			{
				skipsrc(9);
				return make_tuple(line, TOKEN_NAMESPACE, tokenNameMap[TOKEN_NAMESPACE]);
			}
		case 'c':
			if (next_code("class"))
			{
				skipsrc(5);
				return make_tuple(line, TOKEN_CLASS, tokenNameMap[TOKEN_CLASS]);
			}
		case '{':
			skipsrc(1);
			return make_tuple(line, TOKEN_ZUOHUAKUO, tokenNameMap[TOKEN_ZUOHUAKUO]);
		case '}':
			skipsrc(1);
			return make_tuple(line, TOKEN_RIGHTHUAKUO, tokenNameMap[TOKEN_RIGHTHUAKUO]);
		}

		// check multiple character token
		if (src[0] == '_' ||

			isletter(src[0]))
		{
			string token = scan_name();
			// cout<<token<<endl;
			return make_tuple(line, TOKEN_VAR, token);
		}
		if (src[0] >= '0' && src[0] <= '9')
		{
			// cout<<src[0]<<endl;
			string n = scan_number();
			//	cout<<"num: "<<n<<endl;
			//	string a=n+"123";
			//	cout<<a<<endl;
			return make_tuple(line, TOKEN_NUMBER, n);
		}

		// unexpected symbol
		cout << "error at matchtoken" << endl;
		throw "error at matchtoken";
	}

public:
	bool next_code(string str)
	{
		int len = str.length() - 1;

		if (str.length() < src.length() && str.compare(src.substr(0,str.length())) == 0)
		{
			//	src.erase(0, 2);
			return true;
		}
		else
		{
			if (str == src)
				return true;
		}
		return false;
	}
	string scan_before_token(string token)
	{
		vector<string> s = split(src, token);
		if (s.size() < 2)
		{
			cout << "unreachable!";
			throw "Exception";
		}
		skipsrc(s[0].length());
		return s[0];
	}
	void skipsrc(int n)
	{
		src = src.substr(n);
	}
	string scan_name()
	{
		string name = "";
		name = src[0];
		skipsrc(1);
		while (src[0] == '_' || isletter(src[0]))
		{
			name = name + src[0];
			skipsrc(1);
		}
		return name;
	}
	string scan_number()
	{

		string name = "";
		name = src[0];
		skipsrc(1);
		while (src[0] >= '0' && src[0] <= '9')
		{
			name = name + src[0];
			skipsrc(1);
		}
		return name;
	}
	string regexscantoken(regex regx)
	{
		std::smatch res;
		if (std::regex_match(src, res, regx))
		{
			skipsrc(res.length());
			return res[0];
		}
		cout << "error at regexscantoken" << endl;
		cout << "at " << line << endl;
		throw "Error at regexscantoken";
	}
	int Getline()
	{
		return line;
	}
	bool isIgnored()
	{
		bool iskong = false;
		auto isWhiteSpace = [](char c) -> bool
		{
			switch (c)
			{
			case '\t':
				return true;
			case '\n':
				return true;
			case '\v':
				return true;
			case '\f':
				return true;
			case '\r':
				return true;
			case ' ':
				return true;
			}
			return false;
		};
		// matching
		int i = 0;
		while (src.length() > 0)
		{

			// i++;
			// isNewLine
			if (next_code("\n\r") || next_code("\r\n"))
			{
				//	cout<<"1231"<<endl;
				skipsrc(2);
				line++;
				iskong = true;
			}
			if (src[0] == '\r' || src[0] == '\n')
			{
				//	cout<<"1232"<<endl;
				skipsrc(1);
				line++;
				iskong = true;
			}
			// isWhiteSpace
			else if (isWhiteSpace(src[0]))
			{
				//	cout<<"1233"<<endl;
				skipsrc(1);
				iskong = true;
			}
			else
			{
				break;
			}
		}
		// cout<<"123123"<<i<<endl;
		return iskong;
	}

private:
	static bool isletter(char ch)
	{
		if (ch <= 'z' && ch >= 'a' || ch <= 'Z' && ch >= 'a')
			return true;
		return false;
	}
	static vector<string> split(string &str, string &pattern)
	{
		vector<string> res;
		if (str == "")
			return res;
		//���ַ���ĩβҲ����ָ����������ȡ���һ��
		string strs = str + pattern;
		size_t pos = strs.find(pattern);

		while (pos != strs.npos)
		{
			string temp = strs.substr(0, pos);
			res.push_back(temp);
			//ȥ���ѷָ���ַ���,��ʣ�µ��ַ����н��зָ�
			strs = strs.substr(pos + 1, strs.size());
			pos = strs.find(pattern);
		}

		return res;
	}
};





/*lexer::~lexer()
{
}*/
#endif