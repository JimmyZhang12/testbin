#include <iostream>
#include <cstdint>
#include <stdlib.h> 
#include <unistd.h>
#include <vector>

using namespace std;

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
    int version=0;

    #ifdef FAST
    version = 1;
    #endif

    bool print = false;

    int option;
    while((option = getopt(argc, argv, "m:n:k:m:p:v:")) != -1){ //get option from the getopt() method
      switch(option){
         case  'v':
            version = atoi(optarg);
            break;
         case 'p': 
            print = atoi(optarg)==1?1:0;
            break;
      }
   }

    cout<<"mode="<<version<<", m="<<m<<", n="<<n<<", k="<<k<<'\n';
    LCG lcg = LCG();
    vector<vector<uint32_t>> a(
        m, vector<uint32_t>(k,0));
    for (uint32_t i=0; i<m; i++){
        for (uint32_t j=0; j<k; j++)
            a[i][j] = lcg.generate();
        
    }
    cout <<"Init matrix A done!\n";

    vector<vector<uint32_t>> b(
        k, vector<uint32_t>(n,0));
    for (uint32_t i=0; i<k; i++){
        for (uint32_t j=0; j<n; j++)
            b[i][j] = lcg.generate();
        
    }
    cout <<"Init matrix B done!\n";

    vector<vector<uint32_t>> c(
        m, vector<uint32_t>(n,0));
        
    cout <<"Init matrix C done!\n";

    if (version==0){
        cout<<"Entering matrix mult loops, baseline...\n";

        #pragma unroll
        for (uint32_t i=0; i<m; i++){
            #pragma unroll
            for (uint32_t j=0; j<n; j++){
                #pragma unroll
                for (uint32_t l=0; l<k; l++){
                    c[i][j] += a[i][l]*b[l][j];
                }
            }
        }
    }
    else if (version==1){
        cout<<"Entering matrix mult loops, cache optimized...\n";
        #pragma unroll
        for (uint32_t i=0; i<m; i++){
            #pragma unroll
            for (uint32_t l=0; l<k; l++){
                #pragma unroll
                for (uint32_t j=0; j<n; j++){
                    c[i][j] += a[i][l]*b[l][j];
                }
            }
        }      
    } 
    else if (version==2){
        #define BLOCK 100
        cout<<"Entering matrix mult loops, blocks...\n";

        #pragma unroll
        for (uint32_t i0=0; i0<m; i0=i0+BLOCK){
            #pragma unroll
            for (uint32_t l0=0; l0<k; l0=l0+BLOCK){
                #pragma unroll
                for (uint32_t j0=0; j0<n; j0=j0+BLOCK){

                    #pragma unroll
                    for (uint32_t i=0; i<BLOCK; ++i){
                        #pragma unroll
                        for (uint32_t l=0; l<BLOCK; ++l){
                            #pragma unroll
                            for (uint32_t j=0; j<BLOCK; ++j){
                                c[i][j] += a[i][l]*b[l][j];
        }}}}}}  
    }
    else{
        cout<<"Invalid option\n";
    }

    cout<<"Done!\n";
    if (print){
        cout << "A\n";    
        for (uint32_t i=0; i<m; i++){
            for (uint32_t j=0; j<k; j++)
                cout << a[i][j] << " ";
            cout << '\n';
        }
        cout << "B\n";    
        for (uint32_t i=0; i<n; i++){
            for (uint32_t j=0; j<k; j++)
                cout << b[i][j] << " ";
            cout << '\n';
        }
        cout << "C\n";    
        for (uint32_t i=0; i<m; i++){
            for (uint32_t j=0; j<n; j++)
                cout << c[i][j] << " ";
            cout << '\n';
        }
    }   

}
