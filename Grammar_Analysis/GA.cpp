/**
 * @author TripleZ
 * @date 2017-09-27
 * @brief A simple grammar analysis program written by C++.
 */
#include "GA.h"
using namespace std;

string value;
string key;

fstream source;
fstream output;

/**
 * Read file line by line.
 * @return Global variables: value & key.
 */
string line;
void ReadLine() {
// Remember ERROR procedure.
    getline(source, line);


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
 * <prog> → program <id>; <block>
 */
void Prog() {
    ReadLine();
    if (value == "program" && key == "RESERVED"){
        ReadLine();
        if (key == "ID") {
            ReadLine();
            if (value == ";" && key == "EOP") {
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

/**
 * <block> → [<condecl>][<vardecl>][<proc>]<body>
 */
void Block() {
    ReadLine();
    if (value == "const" && key == "RESERVED") {
        Condecl();
    }
    if (value == "var" && key == "RESERVED") {
        Vardecl();
    }
    if (value == "procedure" && key == "RESERVED") {
        Proc();
    }

    Body();
}

/**
 * <condecl> → const <const>{,<const>};
 * <const> → <id>:=<integer>
 * <id> → l{l|d}
 * l represent letter.
 */
void Condecl() {
    ReadLine();
    if (key == "ID"){
        ReadLine();
        if (value == ":=" && key == "AOP"){
            ReadLine();
            if (key == "INT") {
                ReadLine();
                while (value == "," && key == "SOP"){
                    ReadLine();
                    if (key == "ID"){
                        ReadLine();
                        if (value == ":=" && key == "AOP"){
                            ReadLine();
                            if (key == "INT") {
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
                if (value == ";" && key == "EOP") {
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
    if (key == "ID") {
        ReadLine();
        while (value == ",", key == "SOP") {
            ReadLine();
            if (key == "ID") {
                ReadLine();
            } else {
                ThrowError(7);// Missing ID
            }
        }
        if (value == ";" && key == "EOP") {
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
 * <lop> → =|<>|<|<=|>|>=
 */
void Lop() {

}

/**
 * <aop> → +|-
 */
void Aop() {

}

/**
 * <mop> → *|/
 */
void Mop() {

}

/**
 * <id> → l{l|d}
 * l represent letter.
 */
void Id() {

}

/**
 * <integer> → d{d}
 * d represent digit.
 */
void Int() {

}


void OpenFile() {
    source.open("la_output", ios::in); // Read file
    output.open("ga_output", ios::out | ios::trunc); // Write file

    if (!source.is_open()) {
        cout << "Cannot open the source file!\a" << endl;
        exit(1);
    }
    if (!output.is_open()) {
        cout << "Cannot open the output file!\a" << endl;
    } else {
        // Header of the file (DateTime & File name & Lang set)

        time_t rawtime;
        struct tm * timeinfo;

        time (&rawtime);
        timeinfo = localtime (&rawtime);

        output << "# Grammar Analysis Result" << endl;
        output << "# Generated Time: " << asctime(timeinfo);
        output << "# Language Set: PL/0" << endl;
        output << endl;
    }
}

/**
 * Grammar analysis main program
 * @return
 */
int GA() {


    Prog();
    return 0;
}