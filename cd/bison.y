%{
    #include<stdio.h>
%}
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL
%%
calclist:
  |  calclist exp EOL {printf("=%d\n",$1);}
;
exp:factor
  | exp ADD factor {$$=$1+$3;}
  | exp SUB factor {$$=$1-$3;}
;
factor:term
   | exp MUL term {$$=$1*$3;}
   | exp DIV term {$$=$1/$3;}
;
term:NUMBER
   | ABS term {$$ = $2 >=0?$2:- $2;}
;
%%
int main(int argc,char *argv[]){
    yyparse();
}
yyerror(char *s){
    fprintf(stderr,"error %s\n",s);
}
