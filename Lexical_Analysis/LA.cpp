/**
 * @author TripleZ
 * @date 2017-09-19
 * @brief A simple lexical analysis program written by c++.
 */

#include "LA.h"
using namespace std;

fstream source;
fstream output;

const string key[15] = {"program", "const", "var", "procedure", "begin", "if", "end", "while", "call", "read", "write", "then", "odd", "do"};

/**
 * Verify whether is blank char, 1 is BC, 0 is not.
 * @param ch char
 * @author TripleZ
 */
int isBC(char ch){
	if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'){
		return 1;
	} else {
		return 0;
	}
}

string Concat(string a, char ch) {
	a.push_back(ch);
	return a;
}

int isDigit(char ch) {
	if (ch >= '0' && ch <= '9'){
		return 1;
	} else {
		return 0;
	}
}

int isLetter(char ch){
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
		return 1;
	} else {
		return 0;
	}
}

int Reserve(string strToken) {
	int i;
	for(i = 0; i< 15; i++) {
		if (strToken.compare(key[i]) == 0) {
			return 1;// is reserved;
		}
	}
	return 0;
}

void Retract(){
    if (!source.eof()){
        source.seekg(-1, ios::cur);
    }
}

int main()
{
	source.open("input", ios::in); // Read file;
	output.open("results", ios::out | ios::app); // W

	if (!source.is_open())
	{
		cout << "Cannot open the source file!\a" << endl;
		exit(1);
	}
	if (!output.is_open())
	{
		cout << "Cannot open the output file!\a" << endl;
	}


	string strToken;
	char ch;
	while (!source.eof())
	{
		ch = source.get();

        if (isBC(ch)){
            strToken = "";
        } else if (isLetter(ch)){

			while (isLetter(ch) || isDigit(ch)){
				strToken = Concat(strToken, ch);
				ch = source.get();
			}


            if (Reserve(strToken)){
                cout << strToken << ", RESERVED" << endl;
            }
			else{
                cout << strToken << ", ID" << endl;
            }
            strToken = "";

            Retract();

        } else if (isDigit(ch)){
			while (isDigit(ch)) {
				strToken = Concat(strToken, ch);
				source.get(ch);
			}

			Retract();

			cout << strToken << ", INT" << endl;
		} else {
			switch(ch) {
				case '=':
					cout << ch << ", COP" << endl;
					break;
				case '<':
					ch = source.get();
					if (ch == '>') {
						cout << "<>, COP" << endl;
					} else if (ch == '='){
						cout << "<=, COP" << endl;
					} else {
						cout << "<, COP" << endl;
						Retract();
					}
					break;
				case '>':
					ch = source.get();
					if (ch == '=') {
						cout << ">=, COP" << endl;
					} else {
						cout << ">, COP" << endl;
						Retract();
					}
					break;
				case ':':
					ch = source.get();
					if (ch == '=') {
						cout << ":=, AOP" << endl;
					} else {
						cout << "[Program ERROR] Missing \"=\" near the \":\" ;" << endl;
						Retract();
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
					cout << ch << ", OOP" << endl;
					break;
				case ';':
					cout << ch << ", EOP" << endl;
					break;
                case '(':
                case ')':
                    cout << ch << ", POP" << endl;
                    break;
				default:
					cout << ch << ", UNKNOWN" << endl;
			}
		}
	}

	source.close();
	output.close();
	return 0;
}