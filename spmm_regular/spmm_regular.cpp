#include <iostream>
#include <stdlib.h> 
#include <unistd.h>
#include <math.h>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen; 

#define M 20000
#define N 20000
#define K 2000

#define PERCENT_NONZERO 5

typedef Eigen::Triplet<uint32_t> T;

template <class T>
__attribute__((always_inline)) inline void DoNotOptimize(const T &value) {
  asm volatile("" : "+m"(const_cast<T &>(value)));
}

class Val_Gen{
    private:
        uint32_t curr = 99527;
        uint32_t prev = 0;
 
    public:
        uint32_t generate(){
            prev = curr;
            curr = (76333*prev) % 2147483647;
            return curr/(2147483647/65536);
        }
};

class Ind_Gen{
    private:
        uint32_t curr = 75161;
        uint32_t prev = 0;
        uint32_t maxval;
 
    public:
        Ind_Gen(uint32_t seed, uint32_t maxval){
            this->curr = seed;
            this->maxval = maxval;
        }
        uint32_t generate(){
            prev = curr;
            curr = (48271*prev) % 2147483647;
            return curr/(2147483647/maxval);
        }
};


static SparseMatrix<uint32_t> genA() {
    Val_Gen vg = Val_Gen();
    std::vector<T> tripletList1;
    SparseMatrix<uint32_t> A(M,K);      

    int spacing = ceil((float)K/(K*(float)PERCENT_NONZERO/100.0));
    cout <<"Regular A "<< spacing << "vals\n";

    for (int i=0; i<M; i++){
        for (int j=0; j<K; j=j+spacing){
            tripletList1.push_back(T(i,j,
                vg.generate()));       
        }
    }
    
    A.setFromTriplets(tripletList1.begin(), tripletList1.end());
    cout <<"SPMM-Init matrix A done!\n";
    return A;

}


static SparseMatrix<uint32_t> genB() {
    Val_Gen vg = Val_Gen();
    std::vector<T> tripletList1;
    SparseMatrix<uint32_t> B(K,N);      


    int spacing = ceil((float)N/(N*(float)PERCENT_NONZERO/100.0));

    cout <<"Regular B "<< spacing << " vals\n";

    for (int i=0; i<K; i++){
        for (int j=0; j<N; j=j+spacing){
            tripletList1.push_back(T(i,j,
                vg.generate()));       
        }
    }
    
    B.setFromTriplets(tripletList1.begin(), tripletList1.end());
    cout <<"SPMM-Init matrix B done!\n";
    return B;
}



int main(int argc, char* argv[]){


    cout <<"Starting SPMM!\n";
    SparseMatrix<uint32_t> C(M,N); 

    SparseMatrix<uint32_t> A = genA();       // Statement 2  
    DoNotOptimize(A);
    SparseMatrix<uint32_t> B = genB();       // Statement 2  
    DoNotOptimize(B);

    cout <<"Matrices Created\n";
    cout <<"SPMM-Performing matrix multiplication..\n";

    C=A*B;
    cout <<"Done!\n";
   
}
