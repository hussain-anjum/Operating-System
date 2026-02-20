#include <bits/stdc++.h>
using namespace std;
struct Process
{
    string pid;
    int at, bt, priority, ct, tat, wt;
    bool completed;
};
int main()
{
    ifstream infile("priority_non.txt");
    int n;
    infile >> n;
    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        infile >> processes[i].pid >> processes[i].at >> processes[i].bt >> processes[i].priority;
        processes[i].completed = false;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.at < b.at; });

    vector<pair<string, int>> gantt_chart;

    int current_time = processes[0].at;
    int completed_count = 0;
    int idle_time = 0;
    string last_pid = "";

    while (completed_count < n)
    {
        int selected_index = -1;
        int highest_priority = INT_MAX; // Lower number = Higher priority

        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= current_time && !processes[i].completed)
            {
                if (processes[i].priority < highest_priority)
                {
                    highest_priority = processes[i].priority;
                    selected_index = i;
                }
            }
        }

        if (selected_index == -1)
        {
            current_time++;
            idle_time++;
            if (last_pid != "Idle")
            {
                gantt_chart.push_back({"Idle", 1});
                last_pid = "Idle";
            }
            else
            {
                gantt_chart.back().second++;
            }
            continue;
        }

        Process &p = processes[selected_index];

        // Non-preemptive: run the selected process to completion
        gantt_chart.push_back({p.pid, p.bt});
        last_pid = p.pid;

        current_time += p.bt;
        p.ct = current_time;
        p.tat = p.ct - p.at;
        p.wt = p.tat - p.bt;
        p.completed = true;
        completed_count++;
    }

    cout << "\nGantt Chart: ";
    for (size_t i = 0; i < gantt_chart.size(); i++)
    {
        cout << gantt_chart[i].first;
        if (i != gantt_chart.size() - 1)
            cout << " --> ";
    }
    cout << endl;

    cout << "\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    int total_tat = 0, total_wt = 0;
    for (auto &p : processes)
    {
        cout << p.pid << "\t" << p.at << "\t" << p.bt
             << "\t" << p.priority << "\t\t" << p.ct
             << "\t" << p.tat << "\t" << p.wt << "\n";
        total_tat += p.tat;
        total_wt += p.wt;
    }
    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    cout << "\nTotal Waiting Time: " << total_wt;
    cout << "\nTotal Turnaround Time: " << total_tat;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time: " << avg_wt;
    cout << "\nTotal Idle Time: " << idle_time;

    return 0;
}