%{
    #include<stdio.h>
    int count = 0;
%}
%%
a {count++; if(count % 2 == 0) printf("Even Number Of A's\n");}
[0-9]+ {printf("NUMBER\n");}
[+] {printf("ASSIGNMENT OPERATORS\n");}
. {fprintf(stderr,"Wrong Character %s\n",yytext);}
"end" {return 0;}
[ \t\n] {}
%%
int main(){
    yylex();
    if(count % 2 == 0){
        printf("Even Number Of A's\n");
    }
    return 0;
}
