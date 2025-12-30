#include <bits/stdc++.h>
using namespace std;

struct Process
{
    string pid;
    int bt, remaining_bt, ct, tat, wt;
};

int main()
{
    ifstream infile("RR1.txt");

    int n, time_quantum;
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
        processes[i].pid = "P" + to_string(i + 1);
        processes[i].remaining_bt = processes[i].bt;
    }

    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    if (time_quantum <= 0)
    {
        cerr << "Time quantum must be positive" << endl;
        return 1;
    }

    queue<int> ready_queue;
    for (int i = 0; i < n; i++)
    {
        ready_queue.push(i);
    }

    vector<pair<string, int>> gantt_chart;
    int current_time = 0;
    int completed = 0;

    while (completed < n)
    {
        if (ready_queue.empty())
            break;

        int idx = ready_queue.front();
        ready_queue.pop();

        if (processes[idx].remaining_bt > 0)
        {
            int execution_time = min(time_quantum, processes[idx].remaining_bt);
            gantt_chart.push_back({processes[idx].pid, execution_time});

            current_time += execution_time;
            processes[idx].remaining_bt -= execution_time;

            if (processes[idx].remaining_bt == 0)
            {
                processes[idx].ct = current_time;
                processes[idx].tat = processes[idx].ct;
                processes[idx].wt = processes[idx].tat - processes[idx].bt;
                completed++;
            }
            else
            {
                ready_queue.push(idx);
            }
        }
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

    for (auto &p : processes)
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