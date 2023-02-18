#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include "lex1.h"
using namespace std;

LexItem getNextToken (istream& in, int& linenumber){
    enum TokState { START, INID, INSTRING, ININT, INREAL, INCOMMENT, INPOSSIBLEREAL, INEQUAL} lexstate = START;
    string lexeme;
    char ch, nextch, nextchar, nextch1;
    int strtype = 0;//0 for double quotes and 1 for single quotes

    while(in.get(ch) && !in.eof()) {
        if(ch == '\n'){
            linenumber++;
        }
        switch( lexstate ) {
            case START:
                if(ch == '\n'){
                    //linenumber++;
                    continue;
                }
                if(isspace(ch)){
                    continue;
                }
                lexeme = ch;
                if(ch == '!' || ch == '#'){
                    lexstate = INCOMMENT;
                    continue;
                }
                if(isalpha(ch)){
                    lexstate = INID;
                    continue;
                }
                if(isdigit(ch)){
                    lexstate = ININT;
                    continue;
                }
                if(ch == '.'){
                    lexstate = INPOSSIBLEREAL;
                    continue;
                }
                if(ch == '\"' || ch == '\''){
                    lexeme = "";
                    lexstate = INSTRING;
                    continue;
                }
                if(ch == '+'){
                    return LexItem(PLUS, lexeme, linenumber);
                } 
                if(ch == '-'){
                    return LexItem(MINUS, lexeme, linenumber);
                } 
                if(ch == '='){
                    lexstate = INEQUAL;
                    continue;
                } 
                if(ch == '/'){
                    return LexItem(DIV, lexeme, linenumber);
                } 
                if(ch == '*'){
                    return LexItem(MULT, lexeme, linenumber);
                } 
                if(ch == '>'){
                    return LexItem(GTHAN, lexeme, linenumber);
                } 
                if(ch == '<' || ch == '?'){
                    return LexItem(ERR, lexeme, linenumber);
                } 
                if(ch == ','){
                    return LexItem(COMMA, lexeme, linenumber);
                } 
                if(ch == '('){
                    return LexItem(LPAREN, lexeme, linenumber);
                } 
                if(ch == ')'){
                    return LexItem(RPAREN, lexeme, linenumber);
                } 
                if(ch == ';'){
                    return LexItem(SEMICOL, lexeme, linenumber);
                } 
                if(ch == '%'){
                    return LexItem(REM, lexeme, linenumber);
                } 

            case INID:
                if(isalnum(ch)){
                    lexeme += ch;
                    continue;
                }
                if((lexeme == "if" || lexeme == "IF") && in.peek() == '('){
                    return LexItem(IF, lexeme, linenumber);
                }
                if(lexeme == "PROGRAM"){
                    return LexItem(PROGRAM, lexeme, linenumber);
                }
                if(lexeme == "FLOAT" || lexeme == "float"){
                    in.putback(ch);
                    return LexItem(FLOAT, lexeme, linenumber);
                }
                if(lexeme == "WRITE"){
                    return LexItem(WRITE, lexeme, linenumber);
                }
                if(lexeme == "string" || lexeme == "STRING"){
                    return LexItem(STRING, lexeme, linenumber);
                }
                if(lexeme == "REPEAT"){
                    return LexItem(REPEAT, lexeme, linenumber);
                }
                if(lexeme == "int" || lexeme == "INT"){
                    in.putback(ch);
                    return LexItem(INT, lexeme, linenumber);
                }
                if(lexeme == "END"){
                    return LexItem(END, lexeme, linenumber);
                }
                else {
                    if(ch != '\n'){
                        in.putback(ch);
                    }
                    return LexItem(IDENT, lexeme, linenumber);
                }
            case ININT:
                if(isdigit(ch)){
                    lexeme += ch;
                    continue;
                }
                if(ch == '.'){
                    lexeme += ch;
                    lexstate = INPOSSIBLEREAL;
                    continue;
                } 
                else {
                    if(ch != '\n'){
                        in.putback(ch);
                    }
                    return LexItem(ICONST, lexeme, linenumber);
                }
            case INPOSSIBLEREAL:
                if(isdigit(ch)){
                    lexstate = INREAL;
                    lexeme += ch;
                    continue;
                } else {
                    if(ch != '\n'){
                        in.putback(ch);
                    }
                    return LexItem(ERR, lexeme, linenumber);
                }
            case INREAL:
                if(isdigit(ch)){
                    lexeme += ch;
                    continue;
                } else {
                    if(ch != '\n'){
                        in.putback(ch);
                    }
                    return LexItem(RCONST, lexeme, linenumber);
                }
            case INCOMMENT:
                if(ch != '\n'){
                    lexeme += ch;
                    continue;
                } else {
                    lexstate = START;
                    continue;
                } 
            case INSTRING:
                if(ch == '\n'){
                    return LexItem(ERR, "\"" + lexeme, linenumber);
                }
                if(ch != '\"'){
                    lexeme += ch;
                    continue;
                }
                else{
                    return LexItem(SCONST, lexeme, linenumber);
                } 
            case INEQUAL:
                if(ch == '='){
                    return LexItem(EQUAL, lexeme, linenumber);
                } else {
                    return LexItem(ASSOP, lexeme, linenumber);
                }
        }
    }
    return LexItem(DONE, lexeme, linenumber);
}


