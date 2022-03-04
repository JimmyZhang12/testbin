#include <iostream>
#include <stdlib.h> 
#include <unistd.h>
#include <math.h>
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


static SparseMatrix<uint32_t> genA(bool regular) {
    Val_Gen vg = Val_Gen();
    std::vector<T> tripletList1;
    tripletList1.reserve((int)((M*K)*((float)PERCENT_NONZERO/100.0)));

    if (regular){

        int vals_per_row = ceil((float)K/(float)PERCENT_NONZERO);
        cout <<"Regular A "<< vals_per_row << "vals\n";

        for (int i=0; i<M; i++){
            for (int j=0; j<K; j=j+vals_per_row){
                tripletList1.push_back(T(i,j,
                    vg.generate()));       
            }
        }
    }
    else{
        Ind_Gen k_gen = Ind_Gen(7, K);
        Ind_Gen m_gen = Ind_Gen(819251, M);
        for(int i=0; i<(int)((M*K)*((float)PERCENT_NONZERO/100.0)); i++){
            tripletList1.push_back(T(
                m_gen.generate(),
                k_gen.generate(),
                vg.generate()));
        }
    }

    SparseMatrix<uint32_t> A(M,K);      
    A.setFromTriplets(tripletList1.begin(), tripletList1.end());

    cout <<"SPMM-Init matrix A done!\n";
    return A;

}


static SparseMatrix<uint32_t> genB(bool regular) {
    Val_Gen vg = Val_Gen();
    std::vector<T> tripletList1;
    SparseMatrix<uint32_t> B(K,N);      

    if (regular){

        int vals_per_row = ceil((float)N/(float)PERCENT_NONZERO);
        cout <<"Regular B "<< vals_per_row << " vals\n";

        for (int i=0; i<K; i++){
            for (int j=0; j<N; j=j+vals_per_row){
                tripletList1.push_back(T(i,j,
                    vg.generate()));       
            }
        }
    }
    else{
        Ind_Gen k_gen = Ind_Gen(5763, K);
        Ind_Gen n_gen = Ind_Gen(127607, N);

        tripletList1.reserve((int)((K*N)*((float)PERCENT_NONZERO/100.0)));
        for(int i=0; i<(int)((N*K)*((float)PERCENT_NONZERO/100.0)); i++)
        {
        tripletList1.push_back(T(
            k_gen.generate(),
            n_gen.generate(),
            vg.generate()));
        }
    }
    B.setFromTriplets(tripletList1.begin(), tripletList1.end());
    cout <<"SPMM-Init matrix B done!\n";
    return B;

}



int main(int argc, char* argv[]){
    bool regular = false;

    int option;
    while((option = getopt(argc, argv, "r:")) != -1){ //get option from the getopt() method
      switch(option){
         case  'r':
            regular = atoi(optarg);
            break;
      }
   }


    cout <<"Starting SPMM!\n";
    auto pnz = PERCENT_NONZERO;
    SparseMatrix<uint32_t> C(M,N); 

    DoNotOptimize(regular);
    SparseMatrix<uint32_t> A = genA(regular);       // Statement 2  
    DoNotOptimize(A);

    DoNotOptimize(regular);
    SparseMatrix<uint32_t> B = genB(regular);       // Statement 2  
    DoNotOptimize(B);
    cout <<"Matrices Created\n";
    cout <<"SPMM-Performing matrix multiplication..\n";

    C=A*B;
    cout <<"Done!\n";
   
}
