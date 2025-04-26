#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, double> gradeMap = 
    {
        {"A+", 4.5}, {"A0", 4.0},
        {"B+", 3.5}, {"B0", 3.0},
        {"C+", 2.5}, {"C0", 2.0},
        {"D+", 1.5}, {"D0", 1.0},
        {"F", 0.0}
    };

    double totalScore = 0.0;
    double totalCredits = 0.0;

    for (int i = 0; i < 20; ++i) 
    {
        string line, subject, gradeStr;
        double credit;
        getline(cin, line);

        istringstream iss(line);
        iss >> subject >> credit >> gradeStr;

        if (gradeStr == "P") continue;

        totalScore += credit * gradeMap[gradeStr];
        totalCredits += credit;
    }

    double gpa = totalScore / totalCredits;

    cout << fixed << setprecision(6) << gpa << endl;

    return 0;
}