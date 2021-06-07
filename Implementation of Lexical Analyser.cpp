/*
Lexical Analysis is the first phase of compiler also known as scanner. It converts the input program into a sequence of Tokens.
A C program consists of various tokens and a token is either a keyword, an identifier, a constant, a string literal, or a symbol.

For Example:

1) Keywords:
Examples- for, while, if etc.

2) Identifier
Examples- Variable name, function name etc.

3) Operators:
Examples- '+', '++', '-' etc.

4) Separators:
Examples- ', ' ';' etc
*/
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
 
using namespace std;
 
int isKeyword(char buffer[]){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i, flag = 0;
	
	for(i = 0; i < 32; ++i){
		if(strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}
	
	return flag;
}
 
int main(){
	char ch, buffer[15], operators[] = "+-*/%=";
	ifstream fin("program.txt");
	int i,j=0;
	
	if(!fin.is_open()){
		cout<<"error while opening the file\n";
		exit(0);
	}
	
	while(!fin.eof()){
   		ch = fin.get();
   		
		for(i = 0; i < 6; ++i){
   			if(ch == operators[i])
   				cout<<ch<<" is operator\n";
   		}
   		
   		if(isalnum(ch)){
   			buffer[j++] = ch;
   		}
   		else if((ch == ' ' || ch == '\n') && (j != 0)){
   				buffer[j] = '\0';
   				j = 0;
   				   				
   				if(isKeyword(buffer) == 1)
   					cout<<buffer<<" is keyword\n";
   				else
   					cout<<buffer<<" is indentifier\n";
   		}
   		
	}
	
	fin.close();
	
	return 0;
}
