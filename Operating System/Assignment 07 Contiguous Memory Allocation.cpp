#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MEMORY_SIZE = 1000;

struct Process 
{
    int pid;
    int arrival;
    int duration;
    int size;
    int allocated_time = -1;
    int finish_time = -1;
    int start_address = -1;
};

struct Block 
{
    int start;
    int size;
    int pid;
};

enum FitType { FIRST, BEST, WORST };

class Simulator 
{
private:
    vector<Process> processes;
    vector<Block> memory;
    queue<Process> waiting;
    int time = 0;
    int last_allocation_address = -1;
    FitType fit_type;

    void insert_block(int index, const Process& p, int address) 
    {
        Block newBlock = { address, p.size, p.pid };
        Block& hole = memory[index];

        if (hole.size == p.size) 
        {
            memory[index] = newBlock;
        } 
        else 
        {
            hole.start += p.size;
            hole.size -= p.size;
            memory.insert(memory.begin() + index, newBlock);
        }
    }

    void merge_holes() 
    {
        for (size_t i = 0; i + 1 < memory.size();) 
        {
            if (memory[i].pid == -1 && memory[i + 1].pid == -1) 
            {
                memory[i].size += memory[i + 1].size;
                memory.erase(memory.begin() + i + 1);
            } 
            else 
            {
                i++;
            }
        }
    }

    bool try_allocate(Process& p) 
    {
        vector<int> candidate_indices;

        for (size_t i = 0; i < memory.size(); ++i) 
        {
            Block& b = memory[i];
            if (b.pid == -1 && b.size >= p.size)
                candidate_indices.push_back(i);
        }

        if (candidate_indices.empty()) return false;

        int index = candidate_indices[0];
        if (fit_type == BEST) 
        {
            for (int i : candidate_indices)
                if (memory[i].size < memory[index].size)
                    index = i;
        } 
        else if (fit_type == WORST) 
        {
            for (int i : candidate_indices)
                if (memory[i].size > memory[index].size)
                    index = i;
        }

        insert_block(index, p, memory[index].start);
        p.allocated_time = time;
        p.finish_time = time + p.duration;
        p.start_address = memory[index].start;

        return true;
    }

    void release_processes() 
    {
        for (Block& b : memory) 
        {
            for (const Process& p : processes) 
            {
                if (p.pid == b.pid && p.finish_time == time) 
                {
                    b.pid = -1;
                }
            }
        }
        merge_holes();
    }

    void try_waiting_queue() 
    {
        queue<Process> new_waiting;
        while (!waiting.empty()) 
        {
            Process p = waiting.front(); waiting.pop();
            if (try_allocate(p)) 
            {
                processes[p.pid] = p;
                if (p.pid == (int)processes.size() - 1)
                    last_allocation_address = p.start_address;
            } 
            else
            {
                new_waiting.push(p);
            }
        }
        waiting = new_waiting;
    }

public:
    Simulator(vector<Process> procs, FitType type) : processes(procs), fit_type(type) 
    {
        memory = { {0, MEMORY_SIZE, -1} };
    }

    int run() 
    {
        time = 0;
        size_t i = 0;
        while (true) 
        {
            release_processes();
            try_waiting_queue();

            while (i < processes.size() && processes[i].arrival == time) 
            {
                if (try_allocate(processes[i])) 
                {
                    if (processes[i].pid == (int)processes.size() - 1)
                        last_allocation_address = processes[i].start_address;
                } 
                else 
                {
                    waiting.push(processes[i]);
                }
                i++;
            }

            if (i >= processes.size() && waiting.empty()) break;

            time++;
        }

        return last_allocation_address;
    }
};

int main() 
{
    ifstream fin("allocation.inp");
    ofstream fout("allocation.out");
    
    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int n;
    fin >> n;
    vector<Process> input;
    for (int i = 0; i < n; ++i) {
        Process p;
        p.pid = i;
        fin >> p.arrival >> p.duration >> p.size;
        input.push_back(p);
    }

    for (int t = 0; t < 3; ++t) {
        Simulator sim(input, (FitType)t);
        fout << sim.run() << endl;
    }

    return 0;
}
