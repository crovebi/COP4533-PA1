#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

std::vector<std::vector<int>> preferenceInput(std::ifstream& file, int n) {
    std::vector<std::vector<int>> prefs(n);
    std::string line;
    
    for (int i = 0; i < n; i++) {
        std::getline(file, line);
        std::istringstream iss(line);
        int val;
        while (iss >> val) {
            prefs[i].push_back(val - 1);
        }
    }
    return prefs;
}

std::vector<int> deferredAcceptance(std::vector<std::vector<int>> hospital_preference, std::vector<std::vector<int>> student_preference, int n) {

}

int main() {
    std::string filePath = "data/input.in";
    std::ifstream infile(filePath);
    
    if(!infile) {
        std::cerr << "Error: Cannot open file: " << filePath << std::endl;
        return 1;
    }
    
    std::string line;
    std::getline(infile, line);
    int number = std::stoi(line);

    std::vector<std::vector<int>> hospital_preference = preferenceInput(infile, number);
    std::vector<std::vector<int>> student_preference = preferenceInput(infile, number);

    std::vector<int> final_matching = deferredAcceptance(hospital_preference, student_preference, number);
    
    std::cout << "\nFinal Matching Results:" << std::endl;
    for(int i = 0; i < number; i++) {
        std::cout << "Hospital " << (i + 1) << " is matched with Student " << (final_matching[i] + 1) << std::endl;
    }
    
    std::ofstream outfile("data/output.out");
    if(outfile.is_open()) {
        for(int i = 0; i < number; i++) {
            outfile << (i + 1) << " " << (final_matching[i] + 1) << std::endl;
        }
    }
    
    infile.close();
    return 0;
}
