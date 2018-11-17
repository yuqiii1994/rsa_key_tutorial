#include <iostream>
#include <vector> 
#include "rsa_algo.hpp"

using namespace std;

int main(){
    vector<unsigned long int> return_vector;
    return_vector = get_pub_key();
    cout << "vector elements are : "; 
    for (int i = 0; i<return_vector.size(); i++) 
        cout << return_vector[i] << " "; 
    cout << endl; 
    return 0;
}