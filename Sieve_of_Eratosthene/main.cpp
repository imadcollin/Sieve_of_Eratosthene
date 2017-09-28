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
 THE RESULT =O(n) +  O * log(n)
 
 */

void *secondApproach(void*){
    int n=250000;
    int e;
    int primes[n+1];
    for (int i=0; i<n; i++)
        primes[i]=1;
    for(int i=2;i*i<n;i++)
    {
        if(primes[i]==1){
            
            for (int j = i*i; j<n; j +=i) {
                primes[j] = 0;
            }
        }
    }
    for (int i=2; i<=n; i++) {
        if(primes[i]){
            
            cout<<i<<endl;
            e=i;
        }
        
    }
    pthread_exit(&e);
    
    return NULL;
}
int main () {
    Sieve s;
    //s.firstApproach(25);
    //secondApproach();
    
    //Creating one thread for the purpose!
    /*  pthread_t t;
     pthread_create(&t,  NULL,secondApproach,NULL);
     pthread_join(t, NULL);
     */
    //Creating a pnuch of threads for the purpose!
    int cores_num=3;
    pthread_t t_id[cores_num];
    for (int i=0; i<cores_num;i++) {
        pthread_create(&t_id[i],NULL,secondApproach,NULL);
    }
    //Join all threads...!
    for (int i=0; i<cores_num;i++) {
        pthread_join(t_id[i], NULL);
    }
}

