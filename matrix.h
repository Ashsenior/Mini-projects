/* This header file containes functions related to matrix like 

    empty matrice == empty_mat(int,int)
    input mat == input_mat(int.int)
    display mat == display(float **,int,int)
    dot mat == dot(float **,float **,int,int)
    transpose mat == t(float **,int,int)
    sum mat == sum(float **,float **,int,int)
    diff mat == sub(float **,float **,int,int)
    determinant mat == det(float **,int,int)
    adjoint mat == adj(float **,int,int)
    inverse mat == inverse(float **,int,int)
    identity mat == I(int)
    
*/


// Creates and returns an empty matrice 
float **empty_mat(int m,int n){
    float **mat = malloc(m*sizeof(float*));
    for (int i=0;i<m;i++){
        *(mat+i) = malloc(n*sizeof(float));
    }
    return mat;
}

// creates an matrice takkes input and returns the matrice
float **input_mat(int m,int n){
    float **mat = empty_mat(m,n);
    for (int j=0;j<m;j++){
        for (int k=0;k<n;k++){
            scanf("%f",(*(mat+j)+k));
        }
    }
    return mat;
}

// Displays a matrice 
void display(float **mat,int m,int n){
    printf("\n");
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            printf("%f ",*(*(mat+i)+j));
        }
        printf("\n");
    }
    printf("-----------------------------\n");
}

// Return the product_matrice of dot Product of two matrices 
float **dot(float **a,float **b,int w,int z){
    float **p_arr = empty_mat(w,z);

    for (int i=0;i<w;i++){
        for (int j=0;j<z;j++){
           *(*(p_arr+i)+j) = 0;
           for (int k=0;k<z;k++){
               float n = *(*(a+i)+k);
               float m = *(*(b+k)+j);
               *(*(p_arr+i)+j) += n*m;
           } 
        }
    }
    return p_arr;
}

// Creates and returns the transpose of the matrice
float **t(float **a,int w,int x){
    float **t_arr = empty_mat(w,x);
    for (int i=0;i<x;i++){
        for (int j=0;j<w;j++){
            *(*(t_arr+i)+j) = *(*(a+j)+i);
        }
    }
    return t_arr;
}

// Returns sum of two matrices 
float **sum(float **a,float **b,int w,int x){
    float **s_arr = empty_mat(w,x);
    for (int i=0;i<w;i++){
        for (int j=0;j<x;j++){
            *(*(s_arr+i)+j) = *(*(a+i)+j) + *(*(b+i)+j);
        }
    }
    return s_arr;
}

// Returns difference of two matrices 
float **sub(float **a,float **b,int w,int x){
    float **s_arr = empty_mat(w,x);
    for (int i=0;i<w;i++){
        for (int j=0;j<x;j++){
            *(*(s_arr+i)+j) = *(*(a+i)+j) - *(*(b+i)+j);
        }
    }
    return s_arr;
}

// Takes out 2by2 matrice determinant
float **cube(float **mat,int m,int n,int x,int y){
    float **cube = empty_mat(m-1,n-1);
    int tmp_i=0,tmp_j=0;

    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if (i==x){
                continue;
            }
            else if (j==y){
                continue;
            }
            else{
                *(*(cube+tmp_i)+tmp_j) = *(*(mat+i)+j);
                if (tmp_i==0 && tmp_j==0){
                    tmp_j++;
                }
                else if (tmp_i==0 && tmp_j==1){
                    tmp_i++;
                    tmp_j--;
                }
                else if (tmp_i==1 && tmp_j==0){
                    tmp_j++;
                }
            }
        }
    }
    return cube;
}

// Returns determinant of 2by2 matrice
float det2(float **mat){
    float det;
    det = ((*(*(mat+0)+0)) * (*(*(mat+1)+1))) - ((*(*(mat+1)+0)) * (*(*(mat+0)+1)));
    return det;
}

// Returns determinant of any matrice 
float det(float **mat,int m,int n){
    if (m==1 && n==1){ 
        return *(*(mat+0)+0);
    }
    else if (m==2 && n==2){
        return det2(mat); 
    }
    float det=0;
    for (int j=0;j<n;j++){
        float **c = cube(mat,m,n,0,j);
        if (j%2==0){
            det = det + (*(*(mat+0)+j))*det2(c);
        }
        else{
            det = det - (*(*(mat+0)+j))*det2(c);
        }
    }
    return det;
}

// Returns identity matrice
float **I(int n){
    float **I = empty_mat(n,n);
    for (int j=0;j<n;j++){
        for (int k=0;k<n;k++){
            if (j==k){
                *(*(I+j)+k) = 1;
            }
            else{
                *(*(I+j)+k) = 0;
            }
        }
    }
    return I;
}

// Returns adjoint of a matrix 
float **adj(float **mat,int m,int n){
    float **minors = empty_mat(m,n);  

    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            if ((i+j)%2==0){
                *(*(minors+i)+j) = det2(cube(mat,m,n,i,j));
            }
            else {
                *(*(minors+i)+j) = -(det2(cube(mat,m,n,i,j)));
            }
        }
    }
    float **adj = t(minors,m,n);
    return adj;
}

// Returns the inverse of matrix
float **inverse(float **mat,int m,int n){
    float **inverse = empty_mat(m,n);
    int d = det(mat,m,n);
    float **a = adj(mat,m,n);
    for (int i=0;i<m;i++){
        for (int j=0;j<n;j++){
            *(*(inverse+i)+j) = (*(*(a+i)+j))/d;
        }
    }
    return inverse;
}
