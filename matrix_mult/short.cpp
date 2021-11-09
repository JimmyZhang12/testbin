#include <iostream>
#include <cstdint>
#include <stdlib.h> 
#include <unistd.h>
#include <vector>

void matmul(int **a, int **b, int **c, int m, int n, int k){
    #pragma unroll
    for (int i=0; i<m; i++){
        for (int l=0; l<k; l++){
            for (int j=0; j<n; j++){
                c[i][j] += a[i][l]*b[l][j];
            }
        }
    }      

}
