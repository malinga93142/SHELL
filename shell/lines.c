#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char **argv)
{
    FILE *fp[100];
    if(argc >= 2){
        for (int i = 1; i < argc;i++){
            char ch;
            int lines = 1;
            fp[i] = fopen(argv[i], "r");
            if(fp[i] == NULL){
                return 1;
            }
            while((ch = fgetc(fp[i])) != EOF){
                if( ch == '\n'){
                    lines++;
                }
            }
            fprintf(stdout, "file<%s>:lines<%d>\n", argv[i], lines);
        }
    }
    return 0;
}