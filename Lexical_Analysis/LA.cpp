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

int line;
int column;

/**
 * Verify whether is blank char, 1 is BC, 0 is not.
 * @param ch char
 * @author TripleZ
 */
int isBC(char ch){
	if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'){
        switch (ch) {
            case ' ':
                column++;
                break;
            case '\t':
                column+=4; // A tab = 4 spaces
                break;
            case '\r':
            case '\n':
                line++;
                column = 1;
                break;
        }
		return 1;
	} else {
		return 0;
	}
}

/**
 * Add a character to strToken.
 * @param a strToken
 * @param ch add charater
 * @return new strToken string
 */
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

int main() {

    string inputFileName;

    cout << "Enter the program file name: ";
    cin >> inputFileName;
    cout << endl;

	source.open(inputFileName, ios::in); // Read file
	output.open("results", ios::out | ios::trunc); // Write file
    line = 1;
    column = 1;

	if (!source.is_open()) {
		cout << "Cannot open the source file!\a" << endl;
		exit(1);
	}
	if (!output.is_open()) {
		cout << "Cannot open the output file!\a" << endl;
	} else {
        // Header of the file

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        output << "Generate Time: " << asctime(timeinfo);
        output << "Program File Name: " << inputFileName << endl;
        output << "Language Set: PL/0" << endl;
        output << endl;
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
                column++;
				ch = source.get();
			}


            if (Reserve(strToken)){
//                cout << strToken << ", RESERVED" << endl;
                output << strToken << ", RESERVED" << endl;
            }
			else{
//                cout << strToken << ", ID" << endl;
                output << strToken << ", ID" << endl;
            }
            strToken = "";

            Retract();

        } else if (isDigit(ch)){
			while (isDigit(ch)) {
				strToken = Concat(strToken, ch);
                column++;
				ch = source.get();
			}

            if (isLetter(ch)) {
                cout << "[Program ERROR]" << " [" << line << "," << column <<"] " << "Invalid ID" << endl;
                output << "[Program ERROR]" << " [" << line << "," << column <<"] " << "Invalid ID" << endl;

                while (isLetter(ch) || isDigit(ch)){
                    column++;
                    ch = source.get();
                }

            } else {
//                cout << strToken << ", INT" << endl;
                output << strToken << ", INT" << endl;
            }

            Retract();
            strToken = "";

		} else {
			switch(ch) {
				case '=':
                    column++;
//					cout << ch << ", COP" << endl;
                    output << ch << ", COP" << endl;
					break;
				case '<':
                    column++;
					ch = source.get();
					if (ch == '>') {
                        column++;
//						cout << "<>, COP" << endl;
                        output << "<>, COP" << endl;
					} else if (ch == '='){
                        column++;
//						cout << "<=, COP" << endl;
                        output << "<=, COP" << endl;
					} else {
//						cout << "<, COP" << endl;
                        output << "<, COP" << endl;
						Retract();
					}
					break;
				case '>':
                    column++;
					ch = source.get();
					if (ch == '=') {
                        column++;
//						cout << ">=, COP" << endl;
                        output << ">=, COP" << endl;
					} else {
//						cout << ">, COP" << endl;
						output << ">, COP" << endl;
						Retract();
					}
					break;
				case ':':
                    column++;
					ch = source.get();
					if (ch == '=') {
                        column++;
//						cout << ":=, AOP" << endl;
						output << ":=, AOP" << endl;
					} else {
						cout << "[Program ERROR]" << " [" << line << "," << column <<"] " << "Missing \"=\" near the \":\" ;" << endl;
						output << "[Program ERROR]" << " [" << line << "," << column <<"] " << "Missing \"=\" near the \":\" ;" << endl;
						Retract();
					}
					break;
				case '+':
				case '-':
				case '*':
				case '/':
                    column++;
//					cout << ch << ", OOP" << endl;
					output << ch << ", OOP" << endl;
					break;
				case ';':
                    column++;
//					cout << ch << ", EOP" << endl;
					output << ch << ", EOP" << endl;
					break;
                case '(':
                case ')':
                case ',':
                    column++;
//                    cout << ch << ", SOP" << endl;
                    output << ch << ", SOP" << endl;
                    break;
				default:
                    column++;
//					cout << ch << ", UNKNOWN" << endl;
                    output << ch << ", UNKNOWN" << endl;
			}
		}
	}

	source.close();
	output.close();
    cout << endl;
    cout << "Save results successfully" << endl;
	return 0;
}