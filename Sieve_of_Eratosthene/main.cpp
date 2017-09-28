//
//main.cpp
//Sieve_of_Eratosthenes
//
//Created by Imad Collin on 2017-09-19.
//Copyright © 2017 Imad Collin. All rights reserved.
//

#include <iostream>
#include<list>
#include <pthread.h>
using namespace std;
#include<vector>
#include <math.h> /* sqrt */

class Sieve{
public:
    void firstApproach(int n){
        //1. Create a list of natural numbers: 1; 2; 3; : : : ;Max.
        list<int> list;
        vector<int> vec;
        int max;
        cout<<"Enter the Max number for finding the Prime:"<<endl;
        cin>> max;
        
        //primes Vect
        vector<bool> primes(max,true);
        int sq=sqrt(max);
        
        for(int i=0;i<max;i++){
            primes[i]=true;
        }
        //2. Set k to 2, the first unmarked number in the list.
        //3. repeat
        for(int k=2;k<sq;k++){
            if(primes[k]){
                for (int j = k * k; j < max; j += k) {
                    primes[j] = false;
                }
            }
        }
        //4. The unmarked numbers are all prime.
        for(int i=2;i<max;i++){
            if(primes[i]){
                vec.push_back(i);
                cout<<i<<endl;
            }
        }
        cout<<"size is vector "<<vec.size()<<endl;
    }
    
};
//Complixity:
/** for normal approach
 O * sqrt(n)
 For te loop as well will be: O * (n*sqrt n)
 
 for this algorithm
 loop is: O(n)
 for nests loops O * log(n)
 THE RESULT =O(n ln ln n)
 
 */
int shared;
void* secondApproach(void* arg){
    
    int *argument_ptr= (int *)arg;
    int argument_1=*argument_ptr;
    
    //1-List of numbers
    //int n=argument_1;
    int n=25;
    int e;
    int primes[n+1];
    for (int i=0; i<n; i++)
        primes[i]=1;
    //2- seed k=2
    //3- loop until k*k<n
    for(int i=2;i*i<n;i++)
    {
        if(primes[i]==1){
            //4. Mark all multiples of [k*k-n]
            for (int j = i*i; j<n; j +=i) {
                primes[j] = 0;
            }
        }
    }
    //5- prinet unmarked numbers
    for (int i=2; i<=n; i++) {
        if(primes[i]){
            
            cout<<i<<endl;
            // shared=i;
            e=i;
        }
        
    }
    for(int i=0;i<argument_1;i++){
        shared=shared+i;
        cout<<shared<<endl;
        
    }
    // pthread_exit(&e);
    pthread_exit(0);
    return NULL;
}
int main(int argc, char* argv[]){
    
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " Do something" << std::endl;
        return 1;
    }
    long long  argument_1=atoll(argv[1]);
    std::cout << argv[0] << "says hello, " << argument_1 << "!" << std::endl;
    
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid,&attr,secondApproach,&argument_1);
    pthread_join(tid,NULL);
    //Sieve s;
    //s.firstApproach(25);
    //secondApproach();
    
    //Creating one thread for the purpose!
    /*  pthread_t t;
     pthread_create(&t,  NULL,secondApproach,NULL);
     pthread_join(t, NULL);
     */
    //Creating a bunch of threads for the purpose!
    /*
     int cores_num=1;
     pthread_t t_id[cores_num];
     for (int i=0; i<cores_num;i++) {
     pthread_create(&t_id[i],NULL,secondApproach,NULL);
     }
     //Join all threads...!
     for (int i=0; i<cores_num;i++) {
     pthread_join(t_id[i], NULL);
     }
     */
}

