#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int at, bt, ct, tat, wt, remaining_bt;
    bool in_queue = false;
};

int main()
{
    ifstream infile("RR2.txt");
    int n, time_quantum;
    infile >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; i++)
    {
        infile >> processes[i].pid >> processes[i].at >> processes[i].bt;
        processes[i].remaining_bt = processes[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    if (time_quantum <= 0)
    {
        cerr << "Time quantum must be positive" << endl;
        return 1;
    }

    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b)
         { return a.at < b.at; });

    queue<int> ready_queue;
    vector<pair<string, int>> gantt_chart;

    int current_time = 0;
    int completed_count = 0;
    int idle_time = 0;
    string last_pid = "";
    int i = 0;

    while (completed_count < n)
    {
        // Add all processes that have arrived by current_time to the queue
        while (i < n && processes[i].at <= current_time)
        {
            if (!processes[i].in_queue && processes[i].remaining_bt > 0)
            {
                ready_queue.push(i);
                processes[i].in_queue = true;
            }
            i++;
        }

        if (ready_queue.empty())
        {
            // CPU is idle
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

        int idx = ready_queue.front();
        ready_queue.pop();
        processes[idx].in_queue = false;

        int execution_time = min(time_quantum, processes[idx].remaining_bt);

        if (last_pid != processes[idx].pid)
        {
            gantt_chart.push_back({processes[idx].pid, execution_time});
            last_pid = processes[idx].pid;
        }
        else
        {
            gantt_chart.back().second += execution_time;
        }

        current_time += execution_time;
        processes[idx].remaining_bt -= execution_time;

        // Add newly arrived processes to the queue
        while (i < n && processes[i].at <= current_time)
        {
            if (!processes[i].in_queue && processes[i].remaining_bt > 0)
            {
                ready_queue.push(i);
                processes[i].in_queue = true;
            }
            i++;
        }

        if (processes[idx].remaining_bt == 0)
        {
            processes[idx].ct = current_time;
            processes[idx].tat = processes[idx].ct - processes[idx].at;
            processes[idx].wt = processes[idx].tat - processes[idx].bt;
            completed_count++;
        }
        else
        {
            // Process still has remaining time, add back to queue
            ready_queue.push(idx);
            processes[idx].in_queue = true;
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

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    int total_tat = 0, total_wt = 0;

    for (auto &p : processes)
    {
        cout << p.pid << "\t" << p.at << "\t" << p.bt
             << "\t" << p.ct << "\t" << p.tat << "\t" << p.wt << "\n";
        total_tat += p.tat;
        total_wt += p.wt;
    }

    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    cout << "\nTotal Waiting Time: " << total_wt;
    cout << "\nTotal Turnaround Time: " << total_tat;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nAverage Waiting Time: " << avg_wt;
    cout << "\nTotal Idle Time: " << idle_time << "\n";

    return 0;
}