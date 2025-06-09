#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() 
{
    ifstream inputFile("batch.inp");
    if (!inputFile.is_open()) 
    {
        cerr << "Could not open input file 'batch.inp'." << endl;
        return 1;
    }
    ofstream outputFile("batch.out");
    if (!outputFile.is_open()) 
    {
        cerr << "Could not open input file 'batch.out'." << endl;
        return 1;
    }

    int a;
    inputFile >> a;

    vector<vector<int>> programs(a);

    for (int i = 0; i < a; ++i) 
    {
        int time;
        while (inputFile >> time && time != -1) 
        {
            programs[i].push_back(time);
        }
    }

    int total_cpu_idle_time = 0;
    int current_cpu_time = 0;

    for (int i = 0; i < a; ++i) 
    {
        for (size_t j = 0; j < programs[i].size(); ++j) 
        {
            int time = programs[i][j];
            if (j % 2 == 0) 
            { 
                if (current_cpu_time < time) 
                {
                    total_cpu_idle_time += time - current_cpu_time;
                    current_cpu_time = time;
                }
                current_cpu_time += time;
            } 
            else 
            { 
                current_cpu_time += time;
            }
        }
    }

    outputFile << total_cpu_idle_time << " " << current_cpu_time << endl;

    inputFile.close();
    outputFile.close();

    return 0;
}
