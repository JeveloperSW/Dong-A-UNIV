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
    int cur = 0;
    int remaining = 0;
    int finish_time = -1;
    int next_ready_time;
    bool waiting_io = false;

    Process(int id, int arrival, const vector<int>& bursts)
        : id(id), arrival(arrival), bursts(bursts), next_ready_time(arrival) {}

    bool isDone() const
    {
        return cur >= bursts.size();
    }

    void startCpu()
    {
        remaining = bursts[cur];
    }

    void completeCpu(int now)
    {
        cur++;
        if (cur < bursts.size())
        {
            int io = bursts[cur++];
            next_ready_time = now + io;
            waiting_io = true;
        } 
        else
        {
            finish_time = now;
        }
    }
};

int main()
{
    ifstream fin("srtf.inp");
    ofstream fout("srtf.out");

    if (!fin.is_open() || !fout.is_open())
    {
        cerr << "Could not open file" << endl;
        return 1;
    }

    int N;
    fin >> N;
    vector<Process> P;

    for (int i = 0; i < N; ++i)
    {
        int a, x;
        fin >> a;
        vector<int> bursts;
        while (true)
        {
            int x;
            fin >> x;
            if (x == -1) break;
            bursts.push_back(x);
        }
        P.emplace_back(i, a, bursts);
    }

    int time = 0;
    int idle = -1;
    int running = -1;

    auto cmp = [&](int a, int b)
    {
        if (P[a].remaining != P[b].remaining)
            return P[a].remaining > P[b].remaining;
        if (P[a].next_ready_time != P[b].next_ready_time)
            return P[a].next_ready_time > P[b].next_ready_time;
        return P[a].id > P[b].id;
    };

    priority_queue<int, vector<int>, decltype(cmp)> ready(cmp);

    while (true)
    {
        bool all_done = true;
        for (int i = 0; i < N; ++i)
        {
            if (!P[i].isDone()) all_done = false;

            if (!P[i].isDone() && P[i].next_ready_time == time)
            {
                if (P[i].cur == 0 || P[i].waiting_io)
                {
                    P[i].startCpu();
                    ready.push(i);
                    P[i].waiting_io = false;
                }
            }
        }

        if (all_done) break;

        if (running != -1 && P[running].remaining == 0)
        {
            P[running].completeCpu(time);
            running = -1;
        }

        if (!ready.empty())
        {
            int next = ready.top();
            if (running == -1 || cmp(running, next))
            {
                if (running != -1) ready.push(running);
                running = next;
                ready.pop();
            }
        }

        if (running != -1)
        {
            P[running].remaining--;
        }
        else
        {
            idle++;
        }

        time++;
    }

    for (auto& p : P)
    {
        if (p.finish_time == -1)
        {
            p.finish_time = p.next_ready_time;
        }
    }

    fout << idle << '\n';
    for (auto& p : P) fout << p.finish_time << endl;

    fin.close();
    fout.close();

    return 0;
}
