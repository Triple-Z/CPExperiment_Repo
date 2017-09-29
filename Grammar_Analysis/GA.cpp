/**
 * @author TripleZ
 * @date 2017-09-27
 * @brief A simple grammar analysis program written by C++.
 */

#include "GA.h"
using namespace std;

Unit unit;
int errorStack[100] = {-1};
int *errorType = errorStack;
bool error = false;
fstream gaSource;
fstream gaOutput;


/**
 * Read file line by line.
 * @return Global variables: unit.value & unit.key.
 */
string line;
string::iterator itLine;

void ReadLine() {
// Remember ERROR procedure.
    if (getline(gaSource, line)){
//    cout << line << endl;

        itLine = line.begin();
        while (*itLine == '#' || line.empty()) {// Jump annotations & empty lines
            getline(gaSource, line);
//        cout << line << endl;
            itLine = line.begin();
        }

        istringstream iss(line);

        if (*itLine == '^'){ // Lexical error
            char ch;
            iss >> ch; // '^'
            iss >> unit.value;
            iss >> unit.key;
            iss >> unit.line;
            iss >> unit.column;
//        unit.print();
            getline(gaSource, line);
        } else { // No lexical error
            iss >> unit.value;
            iss >> unit.key;
            iss >> unit.line;
            iss >> unit.column;
//        unit.print();
        }
    } else {
//        cout << "[DEBUG] End of file" << endl;
    }
}

/**
 * Throw an error.
 * @param type Error type.
 */
void ThrowError(int type){
    error = true;
    *errorType = type;
    errorType++;
//    cout << "[DEBUG] ERROR TYPE: " << type << endl;
    switch(type){
        case 0:
            cout << "[Grammar ERROR] " << " [" << unit.line << "," << unit.column << "] " << "Missing word \"program\"" << endl;
            break;
        case 1:
            cout << "[Grammar ERROR] " << " [" << unit.line << "," << unit.column << "] " << "Missing identifier after \"program\"" << endl;
            break;
        case 2:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing end character \";\"" << endl;
            break;
        case 3:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier after \"const\"" << endl;
            break;
        case 4:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing assignment operation" << endl;
            break;
        case 5:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing assignment integer" << endl;
            break;
        case 6:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier after \"var\"" << endl;
            break;
        case 7:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier after \",\"" << endl;
            break;
        case 8:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Cannot resolve type \"" << unit.value << "\"" << endl;
            break;
        case 9:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier after \"procedure\"" << endl;
            break;
        case 10:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing parentheses in \"procedure\"" << endl;
            break;
        case 11:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier in \"procedure\"" << endl;
            break;
        case 12:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing word \"begin\"" << endl;
            break;
        case 13:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing word \"end\"" << endl;
            break;
        case 14:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing statement identifier" << endl;
            break;
        case 15:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing word \"then\"" << endl;
            break;
        case 16:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing word \"do\"" << endl;
            break;
        case 17:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier in \"call\"" << endl;
            break;
        case 18:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing parentheses in \"call\"" << endl;
            break;
        case 19:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing identifier in \"read\"" << endl;
            break;
        case 20:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing parentheses in \"read\"" << endl;
            break;
        case 21:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing parentheses in \"write\"" << endl;
            break;
        case 22:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing the compare operator" << endl;
            break;
        case 23:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Missing parentheses" << endl;
            break;
        case 24:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Wrong factor" << endl;
            break;
        default:
            cout << "[Grammar ERROR] "<< " [" << unit.line << "," << unit.column << "] " <<"Unknown error" << endl;
            break;
    }
}

void Exp();
/**
 * <factor>→<id>|<integer>|(<exp>)
 */
void Factor() {
    if (unit.key == "ID" || *errorType == 24) {
        if (unit.key != "ID" && unit.key != "INT" && unit.value == "(" && *errorType == 24) errorType++;
        ReadLine();
        // End factor
    } else if (unit.key == "INT") {
        ReadLine();
        // End factor
    } else if (unit.key == "SOP" && unit.value == "(") {
        ReadLine();
        Exp();
        if (unit.key == "SOP" && unit.value == ")" || *errorType == 23) {
            if (unit.value != ")" && *errorType == 23) errorType++;
            ReadLine();
            // End factor
        } else {
            ThrowError(23);
        }
    } else {
        ThrowError(24);
    }
}

/**
 * <term> → <factor>{<mop><factor>}
 */
void Term() {
    Factor();
    if (unit.value == "*" || unit.value == "/") {
        ReadLine();
        Factor();
    }
}

/**
 * <exp> → [+|-]<term>{<aop><term>}
 */
void Exp() {
    if (unit.value == "+" || unit.value == "-") {
        ReadLine();
    }
    Term();
    if (unit.value == "+" || unit.value == "-") {
        ReadLine();
        Term();
    }
}

/**
 * <lexp> → <exp> <lop> <exp>|odd <exp>
 */
void Lexp() {
    if (unit.value == "odd") {
        ReadLine();
        Exp();
    } else {
        Exp();
//        ReadLine();
        if (unit.key == "COP" || *errorType == 22) {
            if (unit.key != "COP" && *errorType == 22) errorType++;
            ReadLine();
            Exp();
        } else {
            ThrowError(22);
        }
    }

}


void Body();
/**
 * <statement> → <id> := <exp>
               |if <lexp> then <statement>[else <statement>]
               |while <lexp> do <statement>
               |call <id>[（<exp>{,<exp>}）]
               |<body>
               |read (<id>{，<id>})
               |write (<exp>{,<exp>})
 */
void Statement() {
    if (unit.key == "RESERVED" && unit.value == "if") {
        ReadLine();
        Lexp();
        if (unit.key == "RESERVED" && unit.value == "then" || *errorType == 15) {
            if (*errorType == 15 && unit.value != "then") errorType++;
            ReadLine();
            Statement();
//            ReadLine();
            if (unit.key == "RESERVED" && unit.value == "else") {
                ReadLine();
                Statement();
//                ReadLine();
            }
        } else {
            ThrowError(15);
        }

    } else if (unit.key == "RESERVED" && unit.value == "while") {
        ReadLine();
        Lexp();
        if (unit.key == "RESERVED" && unit.value == "do" || *errorType == 16) {
            if (*errorType == 16 && unit.value != "do") errorType++; else ReadLine();
//            ReadLine();
            Statement();
//            ReadLine();
        } else {
            ThrowError(16);
        }

    } else if (unit.key == "RESERVED" && unit.value == "call") {
        ReadLine();
        if (unit.key == "ID" || *errorType == 17) {
            if (*errorType == 17 && unit.key != "ID") errorType++;
            ReadLine();// Read more one line...
            if (unit.key == "SOP" && unit.value == "(") {
                ReadLine();
                Exp();
//                ReadLine();
                while (unit.key == "SOP" && unit.value == ",") {
                    ReadLine();
                    Exp();
//                    ReadLine();
                }
                if (unit.value == ",") ReadLine();
                if (unit.key == "SOP" && unit.value == ")" || *errorType == 18) {
                    if (*errorType == 18 && unit.value != ")") errorType++;
                    ReadLine();
                } else {
                    ThrowError(18);
                }
            }
        } else {
            ThrowError(17);
        }

    } else if (unit.key == "RESERVED" && unit.value == "read") {
        // read (<id>{，<id>})
        ReadLine();
        if (unit.key == "SOP" && unit.value == "(" || *errorType == 20) {
            if (*errorType == 20 && unit.value != "(") errorType++;
            ReadLine();
            if (unit.key == "ID" || *errorType == 19) {
                if (*errorType == 19 && unit.key != "ID") errorType++;
                ReadLine();
                while (unit.key == "SOP" && unit.value == ",") {
                    ReadLine();
                    if (unit.key == "ID" || *errorType == 19) {
                        if (*errorType == 19 && unit.key != "ID") errorType++;
                        ReadLine();
                    } else {
                        ThrowError(19);
                    }
                }
                if (unit.value == ",") ReadLine();
                if (unit.key == "SOP" && unit.value == ")" || *errorType == 20) {
                    if (*errorType == 20 && unit.value != ")") errorType++;
                    ReadLine();
                    // Over read...
                } else {
                    ThrowError(20);
                }
            } else {
                ThrowError(19);
            }

        } else {
            ThrowError(20);
        }

    } else if (unit.key == "RESERVED" && unit.value == "write") {
        // write (<exp>{,<exp>})

        ReadLine();
        if (unit.key == "SOP" && unit.value == "(" || *errorType == 21) {
            if (*errorType == 21 && unit.value != "(") errorType++;
            ReadLine();
            Exp();
            while (unit.key == "SOP" && unit.value == ",") {
                ReadLine();
                Exp();
            }
//            if (unit.value == ",") ReadLine();
            if (unit.key == "SOP" && unit.value == ")" || *errorType == 21) {
                if (*errorType == 21 && unit.value != ")") errorType++;
                ReadLine();
                // Over write...
            } else {
                ThrowError(21);
            }
        } else {
            ThrowError(21);
        }

    } else if (unit.key == "ID") {
        // <id> := <exp>
        ReadLine();
        if (unit.key == "AOP" && unit.value == ":=" || *errorType == 4) {
            if (*errorType == 4 && unit.value != ":=" ) errorType++;
            ReadLine();
            Exp();
        } else {
            ThrowError(4);
        }
    } else{
        Body();
    }
}

/**
 * <body> → begin <statement>{;<statement>}end
 */
void Body() {
    if (unit.key == "RESERVED" && unit.value == "begin" || *errorType == 12) {
        if (*errorType == 12 && unit.value != "begin") errorType++;
        ReadLine();
        Statement();
        while (unit.key == "EOP" && unit.value == ";") {
            ReadLine();
            Statement();
        }
//        if (unit.value == ";") ReadLine();
        if (unit.key == "RESERVED" && unit.value == "end" || *errorType == 13 || error) {
            if (*errorType == 13 && unit.value != "end") errorType++;
            if (!error) ReadLine();
            // Over
        } else {
            ThrowError(13);
        }
    } else {
        ThrowError(12);
    }

}

void Block();
/**
 * <proc> → procedure <id>（<id>{,<id>}）;<block>{;<proc>}
 */
void Proc() {
    if(unit.key == "ID" || *errorType == 9) {
        if(*errorType == 9 && unit.key != "ID") errorType++; else ReadLine();
//        ReadLine();
        if (unit.key == "SOP" && unit.value == "(" || *errorType == 10){
            if (*errorType == 10 && unit.value != "(") errorType++;
            ReadLine();
            if (unit.key == "ID" || *errorType == 11) {
                if (*errorType == 11 && unit.key != "ID") errorType++;
                ReadLine();

                while (unit.value == "," && unit.key == "SOP"){

                    ReadLine();
                    if (unit.key == "ID"|| *errorType == 11){
                        if(unit.key != "ID") errorType++;
                        ReadLine();

                    } else{
                        ThrowError(11); // Missing id
                    }
                    if(error) break;
                }
                if (unit.value == ",") ReadLine();
                if (unit.key == "SOP" && unit.value == ")" || *errorType == 10){
                    if (*errorType == 10 && unit.value != ")") errorType++;
                    ReadLine();

                    if (unit.key == "EOP" && unit.value == ";" || *errorType == 2) {
                        if (*errorType == 2 && unit.value != ";") errorType++;
                        ReadLine();
                        Block();

                        while (unit.key == "EOP" && unit.value == ";") {
                            ReadLine();
                            Proc();
                        }

//                        ReadLine();
                        // End Proc
                    } else {
                        ThrowError(2);
                    }
                } else {
                    ThrowError(10);
                }

            } else {
                ThrowError(11);
            }
        } else {
            ThrowError(10);
        }
    } else {
        ThrowError(9);
    }
}

/**
 * <vardecl> → var <id>{,<id>};
 * <id> → l{l|d}
 * l represent letter.
 */
void Vardecl() {
    if (unit.key == "ID") {
        ReadLine();
        while (unit.value == ",", unit.key == "SOP") {
            ReadLine();
            if (unit.key == "ID") {
                ReadLine();
            } else {
                ThrowError(7);// Missing ID
            }
        }
        if (unit.value == ";" && unit.key == "EOP") {
            ReadLine();
            // Finish var declaration.
        } else {
            ThrowError(2); // Missing EOP
        }
    } else {
        ThrowError(6); // Missing ID
    }
}

/**
 * Const variables declaration.
 * <condecl> → const <const>{,<const>};
 * <const> → <id>:=<integer>
 * <id> → l{l|d}
 * l represent letter.
 */
void Condecl() {
    if (unit.key == "ID" || *errorType == 3){
        if(unit.key != "ID") errorType++;
        ReadLine();
        if (unit.value == ":=" && unit.key == "AOP"|| *errorType == 4) {
            if(!(unit.value == ":=" && unit.key == "AOP")) errorType++;
            ReadLine();
            if (unit.key == "INT"|| *errorType == 5) {
                if(unit.key != "INT") errorType++;
                ReadLine();

                while (unit.value == "," && unit.key == "SOP"){

                    ReadLine();
                    if (unit.key == "ID"|| *errorType == 3){
                        if(unit.key != "ID") errorType++;
                        ReadLine();
                        if (unit.value == ":=" && unit.key == "AOP"|| *errorType == 4){
                            if(!(unit.value == ":=" && unit.key == "AOP")) errorType++;
                            ReadLine();
                            if (unit.key == "INT"|| *errorType == 5) {
                                if(unit.key != "INT") errorType++;
                                ReadLine();
                            } else {
                                ThrowError(5); // Missing INT
                            }
                        } else {
                            ThrowError(4); // Missing AOP
                        }
                    } else{
                        ThrowError(3); // Missing id
                    }
                    if(error) break;
                }
                while (unit.value == ",") ReadLine();
                if (unit.value == ";" && unit.key == "EOP"|| *errorType == 2 || error) {
                    if(!(unit.value == ";" && unit.key == "EOP") && !error) errorType++;
                    ReadLine();
                    // Finish const declaration.
                } else {
                    ThrowError(2); // Missing EOP
                }
            } else {
                ThrowError(5); // Missing INT
            }
        } else {
            ThrowError(4); // Missing AOP
        }
    } else{
        ThrowError(3); // Missing id
    }
}

/**
 * <block> → [<condecl>][<vardecl>][<proc>]<body>
 */
void Block() {

    if (unit.value == "const" && unit.key == "RESERVED") {
        ReadLine();
        Condecl();
    } else if (unit.key == "ID" && *errorType != 8){
        ThrowError(8); // Cannot resolve type
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    } else if (*errorType == 8) {
        errorType++;
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    }

    if (unit.value == "var" && unit.key == "RESERVED") {
        ReadLine();
        Vardecl();
    } else if (unit.key == "ID" && *errorType != 8){
        ThrowError(8); // Cannot resolve type
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    } else if (*errorType == 8) {
        errorType++;
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    }

    if (unit.value == "procedure" && unit.key == "RESERVED") {
        ReadLine();
        Proc();
    } else if (unit.key == "ID" && *errorType != 8){
        ThrowError(8); // Cannot resolve type
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    } else if (*errorType == 8) {
        errorType++;
        while(unit.key != "EOP" && unit.key != "RESERVED"){
            ReadLine();
        }
        ReadLine();
    }

    if (!error){
        Body();
    }
}

/**
 * <prog> → program <id>; <block>
 */
void Prog() {
    ReadLine();
    if ((unit.value == "program" && unit.key == "RESERVED") || *errorType == 0){
        if (*errorType == 0) errorType++;

        ReadLine();
        if (unit.key == "ID" || *errorType == 1) {
            if (*errorType == 1) errorType++;
            ReadLine();
            if ((unit.value == ";" && unit.key == "EOP") || *errorType == 2) {
                if (*errorType == 2 && unit.value != ";") errorType++;
                ReadLine();
                Block();
            } else {
                ThrowError(2);
            }
        } else {
            ThrowError(1);
        }
    } else {
        ThrowError(0);
    }

}

void OpenFile() {
    gaSource.open("la_output", ios::in); // Read file
    gaOutput.open("ga_output", ios::out | ios::trunc); // Write file

    if (!gaSource.is_open()) {
        cout << "Cannot open the gaSource file!\a" << endl;
        exit(1);
    }
    if (!gaOutput.is_open()) {
        cout << "Cannot open the gaOutput file!\a" << endl;
    } else {
        // Header of the file (DateTime & File name & Lang set)

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        gaOutput << "# Grammar Analysis Result" << endl;
        gaOutput << "# Generated Time: " << asctime(timeinfo);
        gaOutput << "# Language Set: PL/0" << endl;
        gaOutput << endl;
    }
}

void CloseFile() {
    gaSource.close();
    gaOutput.close();
}

/**
 * Grammar analysis main program
 * @return
 */
int GA() {

    OpenFile();
    Prog();
    CloseFile();
    while(error){
        error = false;
        errorType = errorStack;
        OpenFile();
        Prog();
        CloseFile();
    }
    return 0;
}