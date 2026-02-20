#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int bt, ct, tat, wt;
};

int main()
{
    ifstream infile("SJF2.txt");

    int n;
    infile >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        infile >> processes[i].bt;
        // if (processes[i].bt < 0)
        // {
        //     cerr << "Burst time must be non-negative" << endl;
        //     return 1;
        // }
        processes[i].pid = "P" + to_string(i);
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.bt < b.bt; });

    queue<Process> ready_queue;
    for (auto &p : processes)
    {
        ready_queue.push(p);
    }

    vector<Process> executed;
    vector<pair<string, int>> gantt_chart;
    int current_time = 0;

    while (!ready_queue.empty())
    {
        Process p = ready_queue.front();
        ready_queue.pop();

        gantt_chart.push_back({p.pid, p.bt});
        p.wt = current_time;
        current_time += p.bt;
        p.ct = current_time;
        p.tat = p.ct;

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

    cout << "\nProcess\tBT\tCT\tTAT\tWT\n";
    int total_tat = 0, total_wt = 0;

    for (auto &p : executed)
    {
        cout << p.pid << "\t" << p.bt << "\t" << p.ct
             << "\t" << p.tat << "\t" << p.wt << "\n";
        total_tat += p.tat;
        total_wt += p.wt;
    }

    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    cout << "\nTotal Turnaround Time: " << total_tat;
    cout << "\nTotal Waiting Time: " << total_wt;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avg_wt << "\n";

    return 0;
}