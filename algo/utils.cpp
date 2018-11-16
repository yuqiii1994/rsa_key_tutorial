#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

bool check_prime_num(unsigned long long int num){
    unsigned long long int i, count = 0;
    for(i=2; i < num; i++){
        if (num % i == 0)
            count++;
    }
    if(count >= 1)
    return false;
    else
    return true;
}

unsigned long long int gen_prime_num(){
    unsigned long long int num;
    bool isPrime;
    while(1){
        num = rand()%1000;
        isPrime = check_prime_num(num);
        if(isPrime)
        return num;
    }
}