#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream infile("FCFS.txt");

    int n;
    infile >> n;

    string pid[100];
    int arrival[100], bt[100], wt[100], tat[100];
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        infile >> pid[i] >> arrival[i] >> bt[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                swap(arrival[j], arrival[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (arrival[i] > current_time)
        {
            current_time = arrival[i];
        }
        wt[i] = current_time - arrival[i];
        tat[i] = wt[i] + bt[i];
        current_time += bt[i];
    }
    cout << endl;

    cout << "Gantt Chart: ";
    for (int i = 0; i < n; i++)
    {
        cout << pid[i];
        if (i != n - 1)
            cout << " --> ";
    }
    cout << endl;

    cout << "\nProcess\tArrival\tBurst Time\tWaiting Time\tTurnaround Time\n";

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++)
    {
        cout << pid[i] << "\t" << arrival[i] << "\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";
        total_wt += wt[i];
        total_tat += tat[i];
    }

    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    cout << "\nTotal Waiting Time: " << total_wt;
    cout << "\nAverage Waiting Time: " << avg_wt;
    cout << "\nAverage Turnaround Time: " << avg_tat;
    cout << "\nTurnaround Time: " << current_time;

    return 0;
}
