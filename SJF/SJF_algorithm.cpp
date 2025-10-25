#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    if (n <= 0)
    {
        cerr << "Invalid number of processes" << endl;
        return 1;
    }

    int bt[n];  // burst time
    int wt[n];  // waiting time
    int tat[n]; // turnaround time
    bool completed[n] = {false};

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter burst time for P" << i << ": ";
        cin >> bt[i];
        if (bt[i] < 0)
        {
            cerr << "Burst time must be non-negative" << endl;
            return 1;
        }
        wt[i] = 0;
        tat[i] = 0;
    }

    int completed_count = 0, current_time = 0;
    int total_wt = 0, total_tat = 0;

    while (completed_count < n)
    {
        int idx = -1;
        int min_burst = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && bt[i] < min_burst)
            {
                min_burst = bt[i];
                idx = i;
            }
        }

        if (idx == -1)
        {
            break; // no process left
        }

        wt[idx] = current_time;
        tat[idx] = wt[idx] + bt[idx];
        current_time += bt[idx];
        completed[idx] = true;
        completed_count++;
        total_wt += wt[idx];
        total_tat += tat[idx];
    }

    cout << "\nProcess\t\tBurst Time\tWaiting Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t" << bt[i] << "\t\t" << wt[i] << "\n";
    }

    double avg_wt = (double)total_wt / n;
    cout << "\nTotal Turnaround Time: " << total_tat << endl;
    cout << "Total Waiting Time: " << total_wt << endl;
    cout << "Average Waiting Time: " << avg_wt;

    return 0;
}
