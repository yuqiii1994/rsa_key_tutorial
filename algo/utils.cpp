#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector> 

using namespace std;

bool check_prime_num(unsigned long int num){
    unsigned long int i, count = 0;
    for(i=2; i < num; i++){
        if (num % i == 0)
            count++;
    }
    if(count >= 1)
    return false;
    else
    return true;
}

bool check_is_a_factor(unsigned long int num){
    int i, count = 0;
    for(i = 2; i < num; i++){
        if (num % i == 0)
            count++;
    }
    if(count >= 1)
    return true;
    else
    return false;
}

unsigned long int gen_prime_num(){
    unsigned long int num;
    bool isPrime;
    while(1){
        num = rand()%1000;
        isPrime = check_prime_num(num);
        if(isPrime)
        return num;
    }
}

vector<unsigned long int> get_pub_key(){
    unsigned long int prime_1, prime_2;
    prime_1 = gen_prime_num();
    prime_2 = gen_prime_num();

    unsigned long int pub_key_n = prime_1 * prime_2;

    unsigned long int encryption;
    while(1){
        encryption = rand() % ((prime_1-1) * (prime_2-1));
        if (!check_is_a_factor(encryption))
            break;
    } 

    vector<unsigned long int> return_vector; 
    // to store the two components of pub keys to a cpp vector
    return_vector.push_back(pub_key_n);
    return_vector.push_back(encryption);
    return return_vector;
}