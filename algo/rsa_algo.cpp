#include <iostream>
#include "rsa_algo.hpp"

using namespace std;

int main(){
    unsigned long long int prime_num_1 = gen_prime_num();
    unsigned long long int prime_num_2 = gen_prime_num();
    cout << prime_num_1 << " " << prime_num_2 << endl;
    return 0;
}