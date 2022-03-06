#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(){
    printf("1st input >>>");
    float **mat1 = input_mat(3,3);
    printf("2nd input >>>");
    float **mat2 = input_mat(3,3);
    printf("Display >>>");
    display(mat1,3,3);
    printf("Dot Product >>>");
    display(dot(mat1,mat2,3,3),3,3);
    printf("Transpose >>>");
    display(t(mat1,3,3),3,3);
    printf("Determinant >>>");
    printf("%d\n",det(mat1,3,3));
    printf("Adjoint >>>");
    display(adj(mat1,3,3),3,3);
    printf("Inverse >>>");
    display(inverse(mat1,3,3),3,3);
    printf("Identity matrice >>>");
    display(I(3),3,3);

    return 0;
}