#include <iostream>
#include <stdlib.h> 
#include <unistd.h>
#include <Eigen/Sparse>

using namespace std;
using namespace Eigen; 

#define M 10000
#define N 10000
#define K 1000

#define PERCENT_NONZERO 10

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


static SparseMatrix<uint32_t> genA(int percent_nz) {
    SparseMatrix<uint32_t> A(M,K);      
    Val_Gen vg = Val_Gen();
    Ind_Gen k_gen = Ind_Gen(7, K);
    Ind_Gen m_gen = Ind_Gen(819251, M);
    cout <<"Random Number Generators Created\n";

    std::vector<T> tripletList1;
    tripletList1.reserve((int)((M*K)*((float)percent_nz/100.0)));
    for(int i=0; i<(int)((M*K)*((float)percent_nz/100.0)); i++)
    {
      tripletList1.push_back(T(
          m_gen.generate(),
          k_gen.generate(),
          vg.generate()));
    }
    A.setFromTriplets(tripletList1.begin(), tripletList1.end());
    cout <<"SPMM-Init matrix A done!\n";
    return A;

}


int main(int argc, char* argv[]){


    cout <<"Starting SPMM!\n";
    auto pnz = PERCENT_NONZERO;
    DoNotOptimize(pnz);
    SparseMatrix<uint32_t> A = genA(pnz);       // Statement 2  
    DoNotOptimize(A);

    SparseMatrix<uint32_t> B(K,N);      
    SparseMatrix<uint32_t> C(M,N); 
    cout <<"Matrices Created\n";


    Val_Gen vg = Val_Gen();
    Ind_Gen k_gen = Ind_Gen(7, K);
    Ind_Gen n_gen = Ind_Gen(127607, N);
    Ind_Gen m_gen = Ind_Gen(819251, M);
    cout <<"Random Number Generators Created\n";

    std::vector<T> tripletList1;
    tripletList1.reserve((int)((M*K)*((float)PERCENT_NONZERO/100.0)));
    for(int i=0; i<(int)((M*K)*((float)PERCENT_NONZERO/100.0)); i++)
    {
      tripletList1.push_back(T(
          m_gen.generate(),
          k_gen.generate(),
          vg.generate()));
    }
    A.setFromTriplets(tripletList1.begin(), tripletList1.end());


    std::vector<T> tripletList2;
    tripletList2.reserve((int)((K*N)*((float)PERCENT_NONZERO/100.0)));
    for(int i=0; i<(int)((K*N)*((float)PERCENT_NONZERO/100.0)); i++)
    {
      tripletList2.push_back(T(
          k_gen.generate(),
          n_gen.generate(),
          vg.generate()));
    }
    B.setFromTriplets(tripletList2.begin(), tripletList2.end());
    cout <<"SPMM-Init matrix B done!\n";
    cout <<"SPMM-Performing matrix multiplication..\n";
    C=A*B;
    cout <<"Done!\n";
   
}
