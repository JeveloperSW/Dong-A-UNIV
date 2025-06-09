#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("batch.inp");
    ofstream outputFile("batch.out");

    if (!inputFile || !outputFile) {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int programCount;
    inputFile >> programCount;

    vector<vector<int>> programs(programCount);

    for (int i = 0; i < programCount; ++i) {
        int time;
        while (inputFile >> time && time != -1) {
            programs[i].push_back(time);
        }
    }

    int totalIdleTime = 0;
    int currentTime = 0;

    for (const auto& program : programs) {
        for (size_t i = 0; i < program.size(); ++i) {
            int duration = program[i];

            if (i % 2 == 0) { 
                if (currentTime < duration) {
                    totalIdleTime += duration - currentTime;
                    currentTime = duration;
                }
                currentTime += duration;
            } else {
                currentTime += duration; 
            }
        }
    }

    outputFile << totalIdleTime << " " << currentTime << endl;

    return 0;
}
