//
//  main.cpp
//  Sieve_of_Eratosthene
//
//  Created by Imad Collin on 2017-09-28.
//  Copyright © 2017 Imad Collin. All rights reserved.
//

#include <iostream>
#include<list>
#include <pthread.h>
using namespace std;
#include<vector>
#include <math.h>       /* sqrt */

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
        // 2. Set k to 2, the first unmarked number in the list.
        // 3. repeat
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

int main () {
    Sieve s;
    s.firstApproach(25);
    return 0;
}



