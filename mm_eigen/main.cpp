#include <iostream>
#include <cstdint>
#include <stdlib.h> 
#include <unistd.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen; 

#define m 10000
#define n 10000
#define k 1000

class LCG{
    private:
        uint32_t curr = 0;
        uint32_t prev = 0;
 
    public:
        uint32_t generate(){
            prev = curr;
            curr = (55*prev + 95) % 7919;
            return curr;
        }
};

int main(int argc, char* argv[]){


    LCG lcg = LCG();

    Matrix<uint32_t, Dynamic, Dynamic> a(m,k);
    for (uint32_t i=0; i<m; i++){
        for (uint32_t j=0; j<k; j++)
            a(i,j) = lcg.generate();
    }
    cout <<"Init matrix A done!\n";
    Matrix<uint32_t, Dynamic, Dynamic> b(k,n);
    for (uint32_t i=0; i<k; i++){
        for (uint32_t j=0; j<n; j++)
            b(i,j) = lcg.generate();     
    }
    cout <<"Init matrix B done!\n";

    Matrix<uint32_t, Dynamic, Dynamic> c(m,n);
    cout <<"Performing matrix multiplication..\n";
    c = b*a;
    cout <<"Done!\n";
   
}
