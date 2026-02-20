#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int bt, priority, ct, tat, wt;
};

int main()
{
    ifstream infile("priority1.txt");
    int n;
    infile >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        infile >> processes[i].bt >> processes[i].priority;
        if (processes[i].bt < 0)
        {
            cerr << "Burst time must be non-negative" << endl;
            return 1;
        }
        processes[i].pid = "P" + to_string(i + 1);
    }

    // Sort by priority (lower number = higher priority), tie-break by original order
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.priority < b.priority; });

    vector<pair<string, int>> gantt_chart;
    int current_time = 0;
    int total_tat = 0, total_wt = 0;

    for (auto &p : processes)
    {
        // Non-preemptive: run each process to full completion
        gantt_chart.push_back({p.pid, p.bt});

        current_time += p.bt;
        p.ct = current_time;
        p.tat = p.ct; // AT = 0, so TAT = CT - 0 = CT
        p.wt = p.tat - p.bt;

        total_tat += p.tat;
        total_wt += p.wt;
    }

    cout << "\nGantt Chart: ";
    for (size_t i = 0; i < gantt_chart.size(); i++)
    {
        cout << gantt_chart[i].first;
        if (i != gantt_chart.size() - 1)
            cout << " --> ";
    }
    cout << endl;

    // Sort back by pid for display
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.pid < b.pid; });

    cout << "\nProcess\tBT\tPriority\tCT\tTAT\tWT\n";
    for (auto &p : processes)
    {
        cout << p.pid << "\t" << p.bt << "\t" << p.priority
             << "\t\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
    }

    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    cout << "\nTotal Turnaround Time: " << total_tat;
    cout << "\nTotal Waiting Time: " << total_wt;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avg_wt << "\n";

    return 0;
}