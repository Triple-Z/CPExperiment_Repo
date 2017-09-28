/**
 * @author TripleZ
 * @date 2017-09-28
 * @brief A simple lexical analysis program written by c++.
 */

#include "LA.h"
using namespace std;

fstream laSource;
fstream laOutput;

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

/**
 * Check a character whether is a digit.
 * @param ch A character
 * @return 1 is true, 0 is false.
 */
int isDigit(char ch) {
    if (ch >= '0' && ch <= '9'){
        return 1;
    } else {
        return 0;
    }
}

/**
 * Check a character whether is a letter.
 * @param ch A character
 * @return 1 is true, 0 is false.
 */
int isLetter(char ch){
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
        return 1;
    } else {
        return 0;
    }
}

/**
 * Check strToken whether is a reserved word.
 * @param strToken search-forward string.
 * @return 1 is reserved, 0 is not.
 */
int Reserve(string strToken) {
    int i;
    for(i = 0; i< 15; i++) {
        if (strToken.compare(key[i]) == 0) {
            return 1;// is reserved;
        }
    }
    return 0;
}


/**
 * Move the cursor back a character.
 */
void Retract(){
    if (!laSource.eof()){
        laSource.seekg(-1, ios::cur);
    }
}

/**
 * Main function.
 * @return 0
 */
int LA() {

    string inputFileName;

    cout << "Enter the program file name: ";
    cin >> inputFileName;
    cout << endl;

    laSource.open(inputFileName, ios::in); // Read file
    laOutput.open("la_output", ios::out | ios::trunc); // Write file
    line = 1;
    column = 1;

    if (!laSource.is_open()) {
        cout << "Cannot open the laSource file!\a" << endl;
        exit(1);
    }
    if (!laOutput.is_open()) {
        cout << "Cannot open the laOutput file!\a" << endl;
    } else {
        // Header of the file (DateTime & File name & Lang set)

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        laOutput << "# Lexical Analysis Result" << endl;
        laOutput << "# Generate Time: " << asctime(timeinfo);
        laOutput << "# Program File Name: " << inputFileName << endl;
        laOutput << "# Language Set: PL/0" << endl;
        laOutput << endl;
    }

    string strToken;
    char ch;
    while (!laSource.eof())
    {
        ch = laSource.get();

        if (isBC(ch)){ // Blank character check
            strToken = "";
        } else if (isLetter(ch)){ // Letter check

            while (isLetter(ch) || isDigit(ch)){ // ID check loop
                strToken = Concat(strToken, ch);
                column++;
                ch = laSource.get();
            }


            if (Reserve(strToken)){ // Reserved word check
//                cout << strToken << ", RESERVED" << endl;
                laOutput << strToken << " RESERVED" << " " << line << " " << column << endl;
            }
            else{
//                cout << strToken << ", ID" << endl;
                laOutput << strToken << " ID" << " " << line << " " << column << endl;
            }
            strToken = "";

            Retract();

        } else if (isDigit(ch)){ // Digit check
            while (isDigit(ch)) {
                strToken = Concat(strToken, ch);
                column++;
                ch = laSource.get();
            }

            if (isLetter(ch)) {
                cout << "[Lexical ERROR]" << " [" << line << "," << column <<"] " << "Invalid ID: " ;
                laOutput << "[Lexical ERROR]" << " [" << line << "," << column <<"] " << "Invalid ID: " ;

                while (isLetter(ch) || isDigit(ch)){
                    strToken = Concat(strToken, ch);
                    column++;
                    ch = laSource.get();
                }

                cout << "\"" << strToken << "\"" << endl;
                laOutput << "\"" << strToken << "\"" << endl;

            } else {
//                cout << strToken << ", INT" << endl;
                laOutput << strToken << " INT" << " " << line << " " << column << endl;
            }

            Retract();
            strToken = "";

        } else {
            switch(ch) { // Other characters check
                case '=':
                    column++;
//					cout << ch << ", COP" << endl;
                    laOutput << ch << " COP" << " " << line << " " << column << endl;
                    break;
                case '<':
                    column++;
                    ch = laSource.get();
                    if (ch == '>') {
                        column++;
//						cout << "<>, COP" << endl;
                        laOutput << "<> COP" << " " << line << " " << column << endl;
                    } else if (ch == '='){
                        column++;
//						cout << "<=, COP" << endl;
                        laOutput << "<= COP" << " " << line << " " << column << endl;
                    } else {
//						cout << "<, COP" << endl;
                        laOutput << "< COP" << " " << line << " " << column << endl;
                        Retract();
                    }
                    break;
                case '>':
                    column++;
                    ch = laSource.get();
                    if (ch == '=') {
                        column++;
//						cout << ">=, COP" << endl;
                        laOutput << ">= COP" << " " << line << " " << column << endl;
                    } else {
//						cout << ">, COP" << endl;
                        laOutput << "> COP" << " " << line << " " << column << endl;
                        Retract();
                    }
                    break;
                case ':':
                    column++;
                    ch = laSource.get();
                    if (ch == '=') {
                        column++;
//						cout << ":=, AOP" << endl;
                        laOutput << ":= AOP" << " " << line << " " << column << endl;
                    } else {
                        cout << "[Lexical ERROR]" << " [" << line << "," << column <<"] " << "Missing \"=\" near the \":\" ;" << endl;
                        laOutput << "^ := AOP " << line << " " << column << endl;
                        laOutput << "[Lexical ERROR]" << " [" << line << "," << column <<"] " << "Missing \"=\" near the \":\" ;" << endl;
                        Retract();
                    }
                    break;
                case '+':
                case '-':
                case '*':
                case '/':
                    column++;
//					cout << ch << ", OOP" << endl;
                    laOutput << ch << " OOP" << " " << line << " " << column << endl;
                    break;
                case ';':
                    column++;
//					cout << ch << ", EOP" << endl;
                    laOutput << ch << " EOP" << " " << line << " " << column << endl;
                    break;
                case '(':
                case ')':
                case ',':
                    column++;
//                    cout << ch << ", SOP" << endl;
                    laOutput << ch << " SOP" << " " << line << " " << column << endl;
                    break;
                default:
                    column++;
//					cout << ch << ", UNKNOWN" << endl;
                    laOutput << ch << " UNKNOWN" << " " << line << " " << column << endl;
            }
        }
    }

    laSource.close();
    laOutput.close();
    cout << endl;
    cout << "Finish lexical analysis" << endl;
    cout << "Save lexical analysis results successfully" << endl;
    cout << endl;
    return 0;
}