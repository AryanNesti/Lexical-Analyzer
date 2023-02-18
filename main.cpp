#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>
#include <algorithm>
#include "lex1.h"
#include "lex.cpp"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv []){
    int lineNumber = 0;
    LexItem tok;
    string fname;
    bool v = false;
    bool iconst = false;
    bool fconst = false;
    bool strconst = false;
    bool ident = false;
    ifstream file(argv[1], ios::in);
    if(argc == 1){
        cout << ("NO SPECIFIED INPUT FILE NAME.") << endl;
        exit(0);
    }
    if(!file.good()){
        cout << "CANNOT OPEN the File " << string(argv[1]) << endl;
        exit(0);
    }
    for( int i=2; i<argc; i++ ) {
        string arg( argv[i] );
        if( arg == "-v" ) {
            v = true;
        } else if (arg == "-iconst"){
            iconst = true;
        } else if (arg == "-fconst") {
            fconst = true;
        } else if (arg == "-strconst") {
            strconst = true;
        } else if (arg == "-ident") {
            ident = true;
        } else if(arg[0] != '-'){
            cout << "ONLY ONE FILE NAME ALLOWED" << endl;
            exit(0);
        } else{
            cout << "UNRECOGNIZED FLAG " << arg << endl;
            exit(0);
        }
    }

    if(!v && !iconst && !fconst && !ident && !strconst){
        int Tcount = 0;
        int Lcount = -1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
        }
        if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        cout << "Lines: " << Lcount << endl;
        if(Lcount != 0){
            cout << "Tokens: " << Tcount << endl;
        }
        exit(1);
    }
    int Tcount = 0;
    int Lcount = -1;
    map<int, Token> ans;
    map<int,Token>::iterator it;
    map<float, Token> ans1;
    map<float,Token>::iterator it1;
    map<string, Token> ans2;
    map<string,Token>::iterator it2;
    map<string, Token> ans3;
    map<string,Token>::iterator it3;
    while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
        Tcount++;
        if(v){
            if(tok.GetToken() == IDENT || tok.GetToken() == ICONST || tok.GetToken() == SCONST || tok.GetToken() == RCONST){
                cout << tokenPrint[tok.GetToken()] << "(" << tok.GetLexeme() << ")" << endl;
            } else{
                cout << tokenPrint[tok.GetToken()] << endl;
            }
        }
        if(iconst){
            stringstream geek(tok.GetLexeme());
            int x = 0;
            geek >> x;
            it = ans.find(x);

            if(it == ans.end() && tok.GetToken() == ICONST){
                ans[x] = tok.GetToken();
            }
        }
        if(fconst){
            stringstream geek(tok.GetLexeme());
            float x = 0;
            geek >> x;
            it1 = ans1.find(x);
            if(it1 == ans1.end() && tok.GetToken() == RCONST){
                ans1[x] = tok.GetToken();
            }
        }
        if(strconst){
            it2 = ans2.find(tok.GetLexeme());
            if(it2 == ans2.end() && tok.GetToken() == SCONST){
                ans2[tok.GetLexeme()] = tok.GetToken();
            }
        }
        if(ident){
            string temp1;
            it3 = ans3.find(tok.GetLexeme());
            temp1 = tok.GetLexeme();
            transform(temp1.begin(), temp1.end(), temp1.begin(), ::toupper);
            //cout << temp1 << " " << tokenPrint[tok.GetToken()] << endl;
            if(kwmap.find(temp1) != kwmap.end()){
                continue;
            }
            if(it3 == ans3.end() && tok.GetToken() == IDENT){
                ans3[temp1] = tok.GetToken();
            }
        }
    }
    if(tok == ERR){
        cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")"  << endl;
        exit(1);
    }
    if(tok.GetToken() == DONE){
        Lcount = tok.GetLinenum();
    }
    if(Lcount == -1){
        cout << "Lines: 0" << endl;
        exit(1);
    }
    cout << "Lines: " << Lcount << endl;
    cout << "Tokens: " << Tcount << endl;
    if(iconst){
        cout << "INTEGERS:" << endl;
        for(it = ans.begin(); it != ans.end(); it++){
            cout << it->first << endl;
        }
    }
    if(fconst){
        cout << "REALS:" << endl;
        for(it1 = ans1.begin(); it1 != ans1.end(); it1++){
            cout << it1->first << endl;
        }
    }
    if(strconst){
        cout << "STRINGS:" << endl;
        for(it2 = ans2.begin(); it2 != ans2.end(); it2++){
            cout << "\"" << it2->first << "\"" << endl;
        }
    }
    if(ident){
        cout << "IDENTIFIERS:" << endl;
        string temp;
        for(it3 = ans3.begin(); it3 != ans3.end(); it3++){
            temp += it3->first + ", ";
        }
        cout << temp.substr(0, temp.length() - 2) << endl;
    }
    /*
    if(v){
        int Tcount = 0;
        int Lcount = -1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
            if(tok.GetToken() == IDENT || tok.GetToken() == ICONST || tok.GetToken() == SCONST || tok.GetToken() == RCONST){
                cout << tokenPrint[tok.GetToken()] << "(" << tok.GetLexeme() << ")" << endl;
                continue;
            }
            cout << tokenPrint[tok.GetToken()] << endl;
        }
        if(tok == ERR){
            cout << "Error in line " << tok.GetLinenum() << " (" << tok.GetLexeme() << ")"  << endl;
            exit(1);
        }
        if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        if(Lcount == -1){
            cout << "Lines: 0" << endl;
            exit(1);
        }
        cout << "Lines: " << Lcount << endl;
        cout << "Tokens: " << Tcount << endl;
    } if(iconst) {
        map<int, Token> ans;
        map<int,Token>::iterator it;
        int Tcount = 0;
        int Lcount = -1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
            stringstream geek(tok.GetLexeme());
 
            // The object has the value 12345 and stream
            // it to the integer x
            int x = 0;
            geek >> x;
            it = ans.find(x);

            if(it == ans.end() && tok.GetToken() == ICONST){
                ans[x] = tok.GetToken();
            }
        }
        if(tok == ERR){
            cout << "Error in line " << tok.GetLinenum() + 1 << " (" << tok.GetLexeme() << ")"  << endl;
            exit(1);
        }*/
        /*for(it = ans.begin(); it != ans.end(); it++){
            cout << tokenPrint[it->second] << "(" << it->first << ")" << endl;
        }*/
        /*if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        if(Lcount == -1){
            cout << "Lines: 0" << endl;
            exit(1);
        }
        if(!strconst && !v && !fconst && !ident){
            cout << "Lines: " << Lcount << endl;
            cout << "Tokens: " << Tcount << endl;
        }
        cout << "INTEGERS:" << endl;
        for(it = ans.begin(); it != ans.end(); it++){
            cout << "here" << endl;
            cout << it->first << endl;
        }
    } 
    if(fconst) {
        map<float, Token> ans;
        map<float,Token>::iterator it;
        int Tcount = 0;
        int Lcount = -1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
            stringstream geek(tok.GetLexeme());
 
            // The object has the value 12345 and stream
            // it to the integer x
            float x = 0;
            geek >> x;
            it = ans.find(x);
            if(it == ans.end() && tok.GetToken() == RCONST){
                ans[x] = tok.GetToken();
            }
        }
        if(tok == ERR){
            cout << "Error in line " << tok.GetLinenum() + 1 << " (" << tok.GetLexeme() << ")"  << endl;
            exit(1);
        }
        if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        if(Lcount == -1){
            cout << "Lines: 0" << endl;
            exit(1);
        }
        if(!strconst && !v && !iconst && !ident){
            cout << "Lines: " << Lcount << endl;
            cout << "Tokens: " << Tcount << endl;
        }
        cout << "REALS:" << endl;
        for(it = ans.begin(); it != ans.end(); it++){
            cout << it->first << endl;
        }
        
    } if(strconst) {
        map<string, Token> ans;
        map<string,Token>::iterator it;
        int Tcount = 0;
        int Lcount = -1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
            it = ans.find(tok.GetLexeme());
            if(it == ans.end() && tok.GetToken() == SCONST){
                ans[tok.GetLexeme()] = tok.GetToken();
            }
        }
        if(tok == ERR){
            cout << "Error in line " << tok.GetLinenum() + 1 << " (" << tok.GetLexeme() << ")"  << endl;
            exit(1);
        }
        if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        if(Lcount == -1){
            cout << "Lines: 0" << endl;
            exit(1);
        }
        if(!fconst && !v && !iconst && !ident){
            cout << "Lines: " << Lcount << endl;
            cout << "Tokens: " << Tcount << endl;
        }
        cout << "STRINGS:" << endl;
        for(it = ans.begin(); it != ans.end(); it++){
            cout << "\"" << it->first << "\"" << endl;
        }
    } 
    if(ident) {
        map<string, Token> ans;
        map<string,Token>::iterator it;
        int Tcount = 0;
        int Lcount = -1;
        string temp1;
        while((tok = getNextToken(file,lineNumber))!= DONE && tok != ERR){
            Tcount++;
            it = ans.find(tok.GetLexeme());
            temp1 = tok.GetLexeme();
            transform(temp1.begin(), temp1.end(), temp1.begin(), ::toupper);
            cout << temp1 << " " << tokenPrint[tok.GetToken()] << endl;
            if(kwmap.find(temp1) != kwmap.end()){
                continue;
            }
            if(it == ans.end() && tok.GetToken() == IDENT){
                ans[temp1] = tok.GetToken();
            }
        }
        if(tok == ERR){
            cout << "Error in line " << tok.GetLinenum()  + 1  << " (" << tok.GetLexeme() << ")"  << endl;
            exit(1);
        }*/
        /*for(it = ans.begin(); it != ans.end(); it++){
            temp1 = it->first;
            transform(temp1.begin(), temp1.end(), temp1.begin(), ::toupper);
            cout << tokenPrint[it->second] << "(" << temp1 << ")" << endl;
        }*/
        /*if(tok.GetToken() == DONE){
            Lcount = tok.GetLinenum();
        }
        if(Lcount == -1){
            cout << "Lines: 0" << endl;
            exit(1);
        }
        if(!strconst && !v && !fconst && !ident){
            cout << "Lines: " << Lcount << endl;
            cout << "Tokens: " << Tcount << endl;
        }
        cout << "IDENTIFIERS:" << endl;
        string temp;
        for(it = ans.begin(); it != ans.end(); it++){
            temp += it->first + ", ";
        }
        //transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        cout << temp.substr(0, temp.length() - 2) << endl;
    } */
    return 0;
}