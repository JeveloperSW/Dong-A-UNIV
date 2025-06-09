#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process 
{
    int id;
    int arrival;
    vector<int> bursts;
    int nextReady;
    int current = 0;
    int finish = -1;

    Process(int id, int arrival, const vector<int>& bursts)
        : id(id), arrival(arrival), bursts(bursts), nextReady(arrival) {}

    bool isDone() const 
    {
        return current >= bursts.size();
    }

    int currentCpuBurst() const 
    {
        return (current < bursts.size()) ? bursts[current] : 1e9;
    }

    void execute(int now) 
    {
        int cpu = bursts[current++];
        if (current < bursts.size()) 
        {
            int io = bursts[current++];
            nextReady = now + cpu + io;
        } 
        else 
        {
            finish = now + cpu;
            nextReady = finish;
        }
    }
};

int main() 
{
    ifstream fin("sjf.inp");
    ofstream fout("sjf.out");
    if (!fin || !fout) 
    {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int n;
    fin >> n;
    vector<Process> processes;

    for (int i = 0; i < n; ++i) 
    {
        int arrival;
        fin >> arrival;
        vector<int> bursts;
        int b;
        while (fin >> b && b != -1)
            bursts.push_back(b);
        processes.emplace_back(i, arrival, bursts);
    }

    int time = 0, idle = 0;

    auto cmp = [&](int a, int b) 
    {
        const auto& pa = processes[a];
        const auto& pb = processes[b];
        if (pa.currentCpuBurst() != pb.currentCpuBurst())
            return pa.currentCpuBurst() > pb.currentCpuBurst();
        if (pa.nextReady != pb.nextReady)
            return pa.nextReady > pb.nextReady;
        return pa.id > pb.id;
    };
    priority_queue<int, vector<int>, decltype(cmp)> ready(cmp);

    while (true) 
    {
        bool pushed = false;
        for (int i = 0; i < n; ++i) 
        {
            if (!processes[i].isDone() && processes[i].nextReady <= time) 
            {
                ready.push(i);
                processes[i].nextReady = 1e9 + 1; 
                pushed = true;
            }
        }

        if (!ready.empty()) 
        {
            int idx = ready.top(); ready.pop();
            int cpu = processes[idx].currentCpuBurst();
            processes[idx].execute(time);
            time += cpu;
        } 
        else 
        {
            int next = 1e9;
            for (const auto& p : processes)
                if (!p.isDone())
                    next = min(next, p.nextReady);
            if (next == 1e9) break;
            idle += next - time;
            time = next;
        }
    }

    fout << idle << endl;
    for (const auto& p : processes)
        fout << p.finish << endl;

    return 0;
}
