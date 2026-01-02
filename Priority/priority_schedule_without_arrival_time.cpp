#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int bt, priority, ct, tat, wt, remaining_bt;
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
        processes[i].remaining_bt = processes[i].bt;
    }

    vector<pair<string, int>> gantt_chart;
    int current_time = 0;
    int completed_count = 0;
    string last_pid = "";

    while (completed_count < n)
    {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        // Find process with highest priority (lower number = higher priority)
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_bt > 0)
            {
                if (processes[i].priority < highest_priority)
                {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1)
            break;

        Process &p = processes[highest_priority_index];
        p.remaining_bt--;
        current_time++;

        if (last_pid != p.pid)
        {
            gantt_chart.push_back({p.pid, 1});
            last_pid = p.pid;
        }
        else
        {
            gantt_chart.back().second++;
        }

        if (p.remaining_bt == 0)
        {
            p.ct = current_time;
            p.tat = p.ct;
            p.wt = p.tat - p.bt;
            completed_count++;
        }
    }

    cout << "\nGantt Chart: ";
    for (size_t i = 0; i < gantt_chart.size(); i++)
    {
        cout << gantt_chart[i].first;
        if (i != gantt_chart.size() - 1)
            cout << " --> ";
    }
    cout << endl;

    cout << "\nProcess\tBT\tPriority\tCT\tTAT\tWT\n";
    int total_tat = 0, total_wt = 0;

    for (auto &p : processes)
    {
        cout << p.pid << "\t" << p.bt << "\t" << p.priority
             << "\t\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
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