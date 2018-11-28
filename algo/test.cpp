#include <iostream>
#include <vector> 
#include <string.h>
#include <string>
#include "rsa_algo.hpp"

using namespace std;

int main(){
    cout << "input str" << endl;
    string input_str;
    cin >> input_str;

    char a = input_str.c_str()[0];

    generate_key_pair generate_key_pair_obj;

    unsigned long long int cipher_txt = encrypt_msg(a, generate_key_pair_obj.n, generate_key_pair_obj.e);

    unsigned long long int decipher_txt = decrypt_msg(cipher_txt, generate_key_pair_obj.n, generate_key_pair_obj.d);

    cout << (int)a << endl;
    cout << cipher_txt << endl;
    cout << decipher_txt << endl;
    return 0;
}