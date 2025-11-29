#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int at, bt, ct, tat, wt;
};

int main()
{
    ifstream infile("FCFS.txt");

    int n;
    infile >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        infile >> processes[i].pid >> processes[i].at >> processes[i].bt;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.at < b.at; });

    queue<Process> ready_queue; // Queue to manage processes in FCFS order based on arrival time
    for (auto &p : processes)
    {
        ready_queue.push(p); // Enqueue all processes initially based on arrival time
    }

    vector<Process> executed;
    vector<pair<string, int>> gantt_chart;
    int current_time = processes[0].at;
    int idle_time = 0;

    while (!ready_queue.empty())
    {
        Process p = ready_queue.front();
        ready_queue.pop();

        if (p.at > current_time)
        {
            int idle_duration = p.at - current_time;
            idle_time += idle_duration;
            gantt_chart.push_back({"Idle", idle_duration});
            current_time = p.at;
        }

        gantt_chart.push_back({p.pid, p.bt});
        current_time += p.bt;

        p.ct = current_time;
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;

        executed.push_back(p);
    }

    cout << "\nGantt Chart: ";
    for (size_t i = 0; i < gantt_chart.size(); i++)
    {
        cout << gantt_chart[i].first;
        if (i != gantt_chart.size() - 1)
            cout << " --> ";
    }
    cout << "\n";

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    int total_tat = 0, total_wt = 0;

    for (auto &p : executed)
    {
        cout << p.pid << "\t" << p.at << "\t" << p.bt
             << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
        total_tat += p.tat;
        total_wt += p.wt;
    }

    cout << "\nAverage Turnaround Time: " << (double)total_tat / n;
    cout << "\nAverage Waiting Time: " << (double)total_wt / n;
    cout << "\nTotal Idle Time: " << idle_time << "\n";

    return 0;
}