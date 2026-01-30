#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
std::vector<int> randomPermutation(int n) {
    std::vector<int> permutation(n);
    for (int i = 0; i < n; i++) {
        permutation[i] = i+1;
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(permutation.begin(), permutation.end(), std::default_random_engine(seed));
    
    return permutation;
}

int main(int argc, char *argv[]){
     if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }
    
    int number = atoi(argv[1]);
    std::ofstream outfile("data/input.in");
    if(outfile.is_open()) {
        outfile << number << std::endl;
        for(int i = 0; i < number; i++) {
            std::vector<int> permutation = randomPermutation(number);
            for(int p = 0; p < number; p++){
                outfile << permutation[p] << ((p < number - 1) ? " " : "");
            }
            outfile << std::endl;
        }
        for(int i = 0; i < number; i++) {
            std::vector<int> permutation = randomPermutation(number);
            for(int p = 0; p < number; p++){
                outfile << permutation[p] << ((p < number - 1) ? " " : "");
            }
            outfile << std::endl;
        }
    }
}