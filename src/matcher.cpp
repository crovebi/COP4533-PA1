#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <chrono>
using namespace std::chrono;

std::vector<std::vector<int>> preferenceInput(std::ifstream& file, int n) {
    std::vector<std::vector<int>> prefs(n);
    std::string line;
    
    for (int i = 0; i < n; i++) {
        if(file.eof()) {
            std::cerr << "ERROR: Not enough input lines."<< std::endl;
            exit(1);
        }
        if(!std::getline(file, line)) {
            std::cerr << "ERROR: Failed to read line of preferences" << std::endl;
            exit(1);
        }
        for (char c : line) {
            if(!std::isspace(static_cast<unsigned char>(c)) && !std::isdigit(static_cast<unsigned char>(c))) {
                std::cerr << "ERROR: Line contains non-integer character." << std::endl;
                exit(1);
            }
        }
        std::istringstream iss(line);
        int val;
        int count = 0;
        std::vector<int> currentLine;
        while(iss >> val) {
            if(val < 1 || val > n) {
                std::cerr << "ERROR: Value has invalid range." << std::endl;
                exit(1);
            }
            currentLine.push_back(val - 1);
            count++;
        }
        if(count != n) {
            std::cerr << "ERROR: Line has invalid number of values." << std::endl;
            exit(1);
        }
        std::string remaining;
        if(iss >> remaining) {
            std::cerr << "ERROR: Line still contains data" << std::endl;
            exit(1);
        }
        
        std::vector<bool> seen(n, false);
        for(int v : currentLine) {
            if(seen[v]) {
                std::cerr << "ERROR: Line has duplicate values." << std::endl;
                exit(1);
            }
            seen[v] = true;
        }
        
        prefs[i] = std::move(currentLine);
    }
    return prefs;
}

std::vector<int> deferredAcceptance(std::vector<std::vector<int>> hospital_preference, std::vector<std::vector<int>> student_preference, int n) {
    std::vector<int> hospital_matching(n, -1);
    std::vector<int> student_matching(n, -1);
    std::vector<int> next_proposal(n, 0);
    
    std::vector<int> hospital_available;
    for(int h = 0; h < n; h++) {
        hospital_available.push_back(h);
    }
    
    while(!hospital_available.empty()) {
        int h = hospital_available.back();
        hospital_available.pop_back();
        
        while(hospital_matching[h] == -1 && next_proposal[h] < n) {
            int s = hospital_preference[h][next_proposal[h]];
            next_proposal[h]++;
            
            if(student_matching[s] == -1) {
                hospital_matching[h] = s;
                student_matching[s] = h;
            } 
            else {
                int current_hospital = student_matching[s];
                int new_pos = -1, current_pos = -1;
                for(int k = 0; k < n; k++) {
                    if (student_preference[s][k] == h) new_pos = k;
                    if (student_preference[s][k] == current_hospital) current_pos = k;
                    if (new_pos != -1 && current_pos != -1) break;
                }
                
                if(new_pos < current_pos) {
                    hospital_matching[current_hospital] = -1;
                    hospital_available.push_back(current_hospital);
                    
                    hospital_matching[h] = s;
                    student_matching[s] = h;
                }
            }
        }
    }
    
    return hospital_matching;
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

    // ------------------- timing -------------------- //
    auto start = high_resolution_clock::now();

    std::vector<int> final_matching = deferredAcceptance(hospital_preference, student_preference, number);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();

    // ------------------- log timing in csv file -------------------- //
    std::ofstream csv("data/matcher_timing.csv", std::ios::app);
    csv << number << "," << duration << "\n";
    csv.close();

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
