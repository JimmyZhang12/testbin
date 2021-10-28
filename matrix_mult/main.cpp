#include <iostream>
#include <cstdint>
#include <stdlib.h> 
#include <unistd.h>


using namespace std;

#define MOD 7919

class LCG{
    private:
        uint32_t curr = 0;
        uint32_t prev = 0;
        uint32_t a,m,c;
    public:
        LCG(uint32_t a, uint32_t b, uint32_t m){
            this->a = a;
            this->c = c;
            this->m = m;
        }
        uint32_t generate(){
            prev = curr;
            curr = (a*prev + c) % m;
            return curr;
        }
};


int main(int argc, char* argv[]){
    int mode=0;
    int m=10;
    int n=10;
    int k=10;
    bool print = false;

    int option;
    while((option = getopt(argc, argv, "m:n:k:m:p:v:")) != -1){ //get option from the getopt() method
      switch(option){
         case 'm':
            m = atoi(optarg);
            break;
         case 'n': 
            n = atoi(optarg);
            break;
         case 'k':
            k = atoi(optarg);
            break;
         case  'v':
            mode = atoi(optarg);
            break;
         case 'p': 
            print = atoi(optarg)==1?1:0;
            break;
      }
   }

    cout<<"mode="<<mode<<", m="<<m<<", n="<<n<<", k="<<k<<'\n';
    
    LCG lcg = LCG(55, 91, MOD);
    uint32_t a[m][k];
    for (uint32_t i=0; i<m; i++){
        for (uint32_t j=0; j<k; j++)
            a[i][j] = lcg.generate();
        
    }
    uint32_t b[n][k];
    for (uint32_t i=0; i<n; i++){
        for (uint32_t j=0; j<k; j++)
            b[i][j] = lcg.generate();
        
    }
    uint32_t c[m][n] = {0};
    for (uint32_t i=0; i<m; i++){
        for (uint32_t j=0; j<n; j++)
            c[i][j] = 0;
    }
    if (mode==0){
        cout<<"Entering matrix mult loops...\n";
        for (uint32_t i=0; i<m; i++){
            for (uint32_t j=0; j<n; j++){
                for (uint32_t l=0; l<k; l++){
                    c[i][j] += a[i][l]*b[l][j];
                }
            }
        }
    }
    else if (mode==1){
        cout<<"Entering matrix mult loops...\n";
        for (uint32_t l=0; l<k; l++){
            for (uint32_t i=0; i<m; i++){
                for (uint32_t j=0; j<n; j++){
                    c[i][j] += a[i][l]*b[l][j];
                }
            }
        }      
    }  
    else{

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
