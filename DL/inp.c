#include<stdio.h>
#include<stdlib.h>
unsigned int left_circular_shift(int value,int shift_val){
    int numbits = 8;
    int mask = (1 << numbits) - 1;
    return ((value << shift_val) | (value >> (numbits - shift_val))) & mask;
}
unsigned int right_circular_shift(int value,int shift_val){
    int numbits = 8;
    int mask = (1 << numbits) - 1;
    return ((value >> shift_val) | (value << (numbits - shift_val))) & mask;
}
int main(int argc,char *argv[]){
    unsigned int a = 0b1100;
    int shift = 2;
    printf("0x%x 0x%x\n", a, left_circular_shift(a, shift));
    printf("0x%x 0x%x\n", a, right_circular_shift(a, shift));
    return 0;
}
