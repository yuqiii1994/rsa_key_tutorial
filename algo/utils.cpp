#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include <string>
#include <iostream>
#include <math.h>       /* sqrt */
#include <numeric>      /* lcm: least common multiple */

using namespace std;

#define PRIME_RANGE 256

class generate_key_pair{
    private:
        unsigned long int _gcd(unsigned long int a, unsigned long int b);
        bool _IsPrime(unsigned long int num);
        int _generate_prime(int range);
        vector<unsigned long int> _generate_all_key();
        unsigned long int _modInverse(unsigned long int a, unsigned long int m);

    public:
        generate_key_pair();

        unsigned long int e; // encryption
        unsigned long int d; // decryption
        unsigned long int n; // n
};

// the key pair constructor
generate_key_pair::generate_key_pair(){
    vector<unsigned long int> key_vector = _generate_all_key();
    n = key_vector[0];
    e = key_vector[1];
    d = key_vector[2];
}

// greatest common divisor
unsigned long int generate_key_pair::_gcd(unsigned long int a, unsigned long int b){
    unsigned long int tmp_int;
    while(a != 0){
        tmp_int = b % a;
        b = a;
        a = tmp_int;
    }
    return b;
}

// primality check
bool generate_key_pair::_IsPrime(unsigned long int number){
    if(number<2)
        return false;
    if(number==2)
        return true;
    if(number%2==0)
        return false;
    for(int i=3;i<=sqrt(number);i += 2)
    {
        if(number%i==0)
            return false;
    }
    return true;
}

// for large number mod power calculation
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus){
    if (exponent == 0) return 1;
    unsigned long long aux = 1;
    while(exponent > 1) {
        if (exponent % 2 != 0) {
            aux *= base;
            aux %= modulus;
        }
        base *= base;
        base %= modulus;
        exponent /= 2;
    }
    return (base*aux) % modulus;
}

// find mod inverse
unsigned long int generate_key_pair::_modInverse(unsigned long int a, unsigned long int m)
{ 
    a = a % m; 
    for (unsigned long int x = 1; x < m; x++) 
       if ((a * x) % m == 1) 
          return x;
    return 0; 
} 

// generate prime given a range as the argument
int generate_key_pair::_generate_prime(int range){
    int candidate_num;
    while(1){
        candidate_num = rand() % range;
        if (_IsPrime(candidate_num))
        break;
    }
    return candidate_num;
}

vector<unsigned long int> generate_key_pair::_generate_all_key(){
    // step 1: p * q 
    unsigned long int prime_1 = (unsigned long int)_generate_prime(PRIME_RANGE);
    unsigned long int prime_2 = (unsigned long int)_generate_prime(PRIME_RANGE);
    unsigned long int n = prime_1 * prime_2;

    // step 2: a new prime e for encryption, relatively to (p - 1) * (q - 1)
    unsigned long int e;
    unsigned long int phi = (prime_1 - 1) * (prime_2 - 1);
    unsigned long int prime_lcm = (unsigned long int)lcm(prime_1 - 1, prime_2 - 1);
    cout << prime_lcm << endl;
    while(1){
        e = (unsigned long int)(rand() % prime_lcm);
        if (_IsPrime(e))
            if (_gcd(e, prime_lcm) == 1)
            break;
    }

    // step 3: generate private key d via mod inverse of e
    unsigned long int d;
    d = _modInverse(e, phi);
    if (d == 0)
    throw invalid_argument("failed");

    vector<unsigned long int> return_vector;

    return_vector.push_back(n);
    return_vector.push_back(e);
    return_vector.push_back(d);

    return return_vector;
}

unsigned long long int encrypt_msg(char raw_txt, unsigned long int n, unsigned long int e){
    unsigned long long int tmp = mod_pow(raw_txt, e, n);
    return tmp;
}

unsigned long long int decrypt_msg(unsigned long int cipher_txt, unsigned long int n, unsigned long int d){
    unsigned long long int tmp = mod_pow(cipher_txt, d, n);
    return tmp;
}