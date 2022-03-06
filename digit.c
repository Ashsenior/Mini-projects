//In this code we will be calculating the sum of the digits entered by the user without using any iterative loops or recursion
#include<stdio.h>
int main(){
    int sum=0;
    int n;
    printf("write the number- ");
    scanf("%d", &n);
    jumpto:
    sum+=n%10;
    n/=10;
    if (n==0){
        printf("Sum of the digits = %d", sum);
        return 0;
    }
    else
        goto jumpto;
}