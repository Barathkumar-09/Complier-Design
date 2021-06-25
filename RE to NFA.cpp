#include<stdio.h> 
#include<string.h> 
int crntState = 0; 
void concatenate(char input) 
{ 
 int startState = crntState; 
 if(input == 'a') 
 printf("%d\t %d\t -\t -\n", startState, startState+1); 
if(input == 'b') 
 printf("%d\t -\t %d\t -\n", startState, startState+1); 
crntState += 1; 
} 
void positiveClosure(char input) 
{ 
 int startState = crntState; 
 printf("%d\t -\t -\t %d\n", startState, startState+1); 
 if(input == 'a') 
 printf("%d\t %d\t -\t -\n", startState+1, startState+2); 
if(input == 'b') 
 printf("%d\t -\t %d\t -\n", startState+1, startState+2); printf("%d\t -\t 
-\t %d,%d\n", startState+2, startState+1, startState+3); crntState += 3; 
} 
void kleenClosure(char input) 
{ 
 int startState = crntState; 
 printf("%d\t -\t -\t %d,%d\n", startState, startState+1, startState+3); 
if(input == 'a') 
 printf("%d\t %d\t -\t -\n", startState+1, startState+2); 
if(input == 'b') 
 printf("%d\t -\t %d\t -\n", startState+1, startState+2); printf("%d\t -\t 
-\t %d,%d\n", startState+2, startState+1, startState+3); crntState += 3; 
} 
void orOperation() 
{ 
 int startState = crntState; 
 printf("%d\t -\t -\t %d\n", startState, startState+1);
 printf("%d\t -\t -\t %d,%d\n",startState+1, startState+2, startState+4); printf("%d\t %d\t -\t -\n",startState+2, startState+3); 
 printf("%d\t -\t -\t %d\n",startState+3, startState+6); 
 printf("%d\t -\t %d\t -\n",startState+4, startState+5); 
 printf("%d\t -\t -\t %d\n",startState+5, startState+6); 
 printf("%d\t -\t -\t %d\n", startState+6, startState+7); 
 crntState += 7; 
} 
void complexTerm(char inputBuffer[], int len) 
{ 
 int startState = crntState; 
 if(inputBuffer[len-1] == '*') 
 printf("%d\t -\t -\t %d,%d\n",startState, startState+1, startState+7); else 
 printf("%d\t -\t -\t %d\n", startState, startState+1); printf("%d\t -\t -\t %d,%d\n",startState+1, startState+2, startState+4); printf("%d\t %d\t -\t -\n",startState+2, startState+3); printf("%d\t -\t -\t %d\n",startState+3, startState+6); printf("%d\t -\t %d\t -\n",startState+4, startState+5); printf("%d\t -\t -\t %d\n",startState+5, startState+6); printf("%d\t -\t -\t %d,%d\n", startState+6, startState+1, startState+7); crntState += 7; } 
void reToNfa(char fileName[]) 
{ 
 FILE *looker = fopen(fileName, "r"); 
 char inputBuffer[10], buff; 
 int len, i; 
 while(feof(looker) == 0) 
 { 
 buff = fgetc(looker); i = 0; 
 while((buff != '.')&&(buff != 
EOF)&&(isspace(buff)==0)) { 
 inputBuffer[i++] = buff; 
 buff = fgetc(looker); 
 } 
 inputBuffer[i++] = '\0';
 len = strlen(inputBuffer); 
 if(len == 1) 
 concatenate(inputBuffer[0]); 
 if((len == 2)&&(inputBuffer[1] == '+')) 
 positiveClosure(inputBuffer[0]); 
 if((len == 2)&&(inputBuffer[1] == '*')) 
 kleenClosure(inputBuffer[0]); 
 if((len == 3)&&(inputBuffer[1] == '|')) 
 orOperation(); 
 if((inputBuffer[0] == '(')&&(inputBuffer[len-2] == ')')) complexTerm(inputBuffer, len); 
 } 
} 
void main() 
{ 
 char fileName[20]; 
 printf("Enter the name of file containing re :: "); scanf("%s", fileName); 
 printf("\nstate a b E\n"); 
 reToNfa(fileName); 
 printf("\nInitial State = %d\nFinal State = %d\n", 0, crntState); getch(0); 
} 
