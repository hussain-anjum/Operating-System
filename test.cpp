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

    int bt[n]; // burst time
    int wt[n]; // waiting time

    for (int i = 0; i < n; ++i)
    {
        cout << "Enter burst time for P" << i << ": ";
        cin >> bt[i];
        if (bt[i] < 0)
        {
            cerr << "Burst time must be non-negative" << endl;
            return 1;
        }
    }

    // Calculate waiting times
    wt[0] = 0; // waiting time for 1st process is 0
    for (int i = 1; i < n; ++i)
    {
        wt[i] = wt[i - 1] + bt[i - 1];
    }

    // Calculate total waiting time
    int total_wt = 0;
    for (int i = 0; i < n; ++i)
    {
        total_wt += wt[i];
    }

    // Calculate turnaround times and total turnaround time
    int tat[n]; // turnaround time array
    int total_tat = 0;
    for (int i = 0; i < n; ++i)
    {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i];
    }

    double avg_wt = static_cast<double>(total_wt) / n;
    double avg_tat = static_cast<double>(total_tat) / n;

    cout << "\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    cout << "\nTotal Turnaround Time: " << total_tat << endl;
    cout << "Total Waiting Time: " << total_wt << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wt << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avg_tat << endl;

    // Gantt Chart
    cout << "\nGantt Chart:\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i;
        if (i != n - 1)
            cout << " => ";
    }
    cout << "\n";

    return 0;
}
