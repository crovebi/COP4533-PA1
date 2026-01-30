#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
using namespace std;

//number of hospitals/students
int n;

//preferences
vector<vector<int>> hospital_prefs;
vector<vector<int>> student_prefs; 

//matches
vector<int> hospital_match;
vector<int> student_match;

// ------------------- validity --------------------//
//verify the match is valid
bool valid_match(){
    unordered_set<int> matched_students;
    for(int h = 0; h < n; ++h){
        int s = hospital_match[h];
        //check if the student index is valid
        if(s < 0 || s > n){
            cout << "INVALID: Hospital " << h+1 << " matched to invalid student " << s << "\n";
            return false;
        }
        //check if the student has already been matched
        if(matched_students.count(s)){
            cout << "INVALID: Student " << s+1 << " matched more than once\n";
            return false;
        }
        matched_students.insert(s);
    }
    return true;
}

// ------------------- stability -------------------- //
//verify the match is stable
bool stable_match(){
    vector<vector<int>> hospital_rank(n, vector<int>(n));
    vector<vector<int>> student_rank(n, vector<int>(n));
    //build the rank matrix for hospitals
    for(int h = 0; h < n; ++h){
        for(int i = 0; i < n; ++i){
            int s = hospital_prefs[h][i];
            hospital_rank[h][s] = i;
        }
    }
    //build the rank matrix for students
    for(int s = 0; s < n; ++s){
        for(int i = 0; i < n; ++i){
            int h = student_prefs[s][i];
            student_rank[s][h] = i;
        }
    }
    //check if its unstable
    for(int h = 0; h < n; ++h){
        int current_student = hospital_match[h];
        for(int s = 0; s < n; ++s){
            //what student hospital h prefers over its current match
            if(s == current_student) break; //no more preferred students
            int current_h_for_s = student_match[s];
            if(student_rank[s][h] < student_rank[s][current_h_for_s]){
                cout << "UNSTABLE: Blocking pair (Hospital " << h+1 << ", Student " << s+1 << ")\n";
                return false;
            }
        }
    }
    return true;
}