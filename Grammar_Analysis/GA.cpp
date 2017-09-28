/**
 * @author TripleZ
 * @date 2017-09-27
 * @brief A simple grammar analysis program written by C++.
 */
#include "GA.h"
using namespace std;

Unit unit;

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
    getline(gaSource, line);
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
        cout << line << endl;
    } else { // No lexical error
        iss >> unit.value;
        iss >> unit.key;
        iss >> unit.line;
        iss >> unit.column;
//        unit.print();
    }
}

/**
 * Throw an error.
 * @param type Error type.
 */
void ThrowError(int type){
    switch(type){
        case 0:
            cout << "[Grammar ERROR] Missing word \"program\"" << endl;
            break;
        case 1:
            cout << "[Grammar ERROR] Missing identifier after \"program\"" << endl;
            break;
        case 2:
            cout << "[Grammar ERROR] Missing end character" << endl;
            break;
        case 3:
            cout << "[Grammar ERROR] Missing identifier after \"const\"" << endl;
            break;
        case 4:
            cout << "[Grammar ERROR] Missing assignment operation" << endl;
            break;
        case 5:
            cout << "[Grammar ERROR] Missing assignment integer" << endl;
            break;
        case 6:
            cout << "[Grammar ERROR] Missing identifier after \"var\"" << endl;
            break;
        case 7:
            cout << "[Grammar ERROR] Missing identifier after \",\"" << endl;
            break;
        default:
            cout << "[Grammar ERROR] Unknown error" << endl;
            break;
    }
}

/**
 * <condecl> → const <const>{,<const>};
 * <const> → <id>:=<integer>
 * <id> → l{l|d}
 * l represent letter.
 */
void Condecl() {
    ReadLine();
    if (unit.key == "ID"){
        ReadLine();
        if (unit.value == ":=" && unit.key == "AOP") {
            ReadLine();
            if (unit.key == "INT") {
                ReadLine();
                while (unit.value == "," && unit.key == "SOP"){
                    ReadLine();
                    if (unit.key == "ID"){
                        ReadLine();
                        if (unit.value == ":=" && unit.key == "AOP"){
                            ReadLine();
                            if (unit.key == "INT") {
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
                }
                if (unit.value == ";" && unit.key == "EOP") {
                    // Over.
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
 * <vardecl> → var <id>{,<id>};
 * <id> → l{l|d}
 * l represent letter.
 */
void Vardecl() {
    ReadLine();
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
            // Over.
        } else {
            ThrowError(2); // Missing EOP
        }
    } else {
        ThrowError(6); // Missing ID
    }
}

/**
 * <proc> → procedure <id>（<id>{,<id>}）;<block>{;<proc>}
 */
void Proc() {

}


/**
 * <body> → begin <statement>{;<statement>}end
 */
void Body() {

}

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

}

/**
 * <lexp> → <exp> <lop> <exp>|odd <exp>
 */
void Lexp() {

}

/**
 * <exp> → [+|-]<term>{<aop><term>}
 */
void Exp() {

}

/**
 * <term> → <factor>{<mop><factor>}
 */
void Term() {

}

/**
 * <factor>→<id>|<integer>|(<exp>)
 */
void Factor() {

}

/**
 * <block> → [<condecl>][<vardecl>][<proc>]<body>
 */
void Block() {
    ReadLine();
    if (unit.value == "const" && unit.key == "RESERVED") {
        Condecl();
    }
    if (unit.value == "var" && unit.key == "RESERVED") {
        Vardecl();
    }
    if (unit.value == "procedure" && unit.key == "RESERVED") {
        Proc();
    }

    Body();
}




/**
 * <prog> → program <id>; <block>
 */
void Prog() {
    ReadLine();
    if (unit.value == "program" && unit.key == "RESERVED"){
        ReadLine();
        if (unit.key == "ID") {
            ReadLine();
            if (unit.value == ";" && unit.key == "EOP") {
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

/**
 * Grammar analysis main program
 * @return
 */
int GA() {

    OpenFile();
    Prog();
    return 0;
}