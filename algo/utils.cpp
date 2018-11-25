#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <list>
#include <string>

#define SEED 10

using namespace std;

// the data to be shared between pub key and private key, so that they can be constructed as a pair
struct data_shared{
    unsigned long int prime_1, prime_2, phi, pub_key_n, encryption, private_key_m;
}data_shared;

bool _check_prime_num(unsigned long int num){
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

bool _check_is_a_factor(unsigned long int num){
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

unsigned long int _gen_prime_num(){
    srand(SEED);
    unsigned long int num;
    bool isPrime;
    while(1){
        num = rand()%1000; // to contain the num in [0, 999]
        isPrime = _check_prime_num(num);
        if(isPrime)
        return num;
    }
}

struct data_shared _get_pub_key(){
    srand(SEED);
    unsigned long int prime_1, prime_2;
    prime_1 = _gen_prime_num();
    prime_2 = _gen_prime_num();

    unsigned long int pub_key_n = prime_1 * prime_2;
    unsigned long int phi = (prime_1 - 1) * (prime_2 - 1);

    unsigned long int encryption;
    while(1){
        encryption = rand() % phi;
        if (!_check_is_a_factor(encryption))
            break;
    } 

    // to store the two components of pub keys to a cpp vector
    (data_shared).prime_1 = prime_1;
    (data_shared).prime_2 = prime_2;
    (data_shared).phi = phi;
    (data_shared).pub_key_n = pub_key_n;
    (data_shared).encryption = encryption;

    return data_shared;
}

struct data_shared _get_private_key(){
    data_shared = _get_pub_key();

    unsigned int k = 2;

    unsigned long int private_key_m = (k * data_shared.phi + 1) / data_shared.encryption;
    data_shared.private_key_m = private_key_m;
    
    return data_shared;
}

class produce_key_pair{
    private:
        struct data_shared get_key_data();

    public:
        produce_key_pair();

        unsigned long int pub_key_n;
        unsigned long int encryption;
        unsigned long int private_key_m;
};

struct data_shared produce_key_pair::get_key_data(){
    data_shared = _get_private_key();
    return data_shared;
}

produce_key_pair::produce_key_pair(){
    struct data_shared data_shared = get_key_data();
    produce_key_pair::pub_key_n = data_shared.pub_key_n;
    produce_key_pair::encryption = data_shared.encryption;
    produce_key_pair::private_key_m = data_shared.private_key_m;
}

list<int> encrypt_msg(string input_str){
    list<int> encrypted_l;
    int str_len = input_str.size();
    for (int i = 0; i < str_len; i++){
        encrypted_l.push_back(input_str[i]);
    } 

    return encrypted_l;
}