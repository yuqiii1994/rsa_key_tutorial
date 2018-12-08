#include "utils.cpp"

class generate_key_pair;

unsigned long long int encrypt_msg(char raw_txt, unsigned long int n, unsigned long int e);
unsigned long long int decrypt_msg(unsigned long int cipher_txt, unsigned long int n, unsigned long int d);