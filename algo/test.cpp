#include <iostream>
#include <vector> 
#include <string.h>
#include <string>
#include "utils.hpp"

using namespace std;

int main(){
    cout << "input str" << endl;
    string input_str;
    cin >> input_str;

    char a = input_str.c_str()[0];

    generate_key_pair generate_key_pair_obj;

    unsigned long long int cipher_txt = encrypt_msg(a, generate_key_pair_obj.n, generate_key_pair_obj.e);

    unsigned long long int decipher_txt = decrypt_msg(cipher_txt, generate_key_pair_obj.n, generate_key_pair_obj.d);

    cout << "sent char" << (int)a << endl;
    cout << "encrypted char" << cipher_txt << endl;
    cout << "decrypted char" << decipher_txt << endl;
    return 0;
}