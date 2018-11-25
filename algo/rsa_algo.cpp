#include <iostream>
#include <vector> 
#include "rsa_algo.hpp"

using namespace std;

int main(){
    produce_key_pair obj_produce_key_pair;
    cout << "pub_key_n : "; 
    cout << obj_produce_key_pair.encryption << endl;
    cout << endl; 
    return 0;
}