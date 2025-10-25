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

    int bt[n], wt[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter burst time for P" << i << ": ";
        cin >> bt[i];
        if (bt[i] < 0)
        {
            cerr << "Burst time must be non-negative" << endl;
            return 1;
        }
    }

    int total_tat = 0;
    for (int i = 0; i < n; i++)
        total_tat += bt[i];

    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    int total_wt = 0;
    for (int i = 0; i < n; i++)
        total_wt += wt[i];

    double avg_wt = static_cast<double>(total_wt) / n;

    cout << "\nProcess\t\tBurst Time\tWaiting Time" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << "P" << i << "\t\t" << bt[i] << "\t\t" << wt[i] << endl;
    }

    cout << "\nGantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i;
        if (i != n - 1)
            cout << " -> ";
    }
    cout << endl;

    cout << "\nTotal turn around time: " << total_tat << endl;
    cout << "Total Waiting Time: " << total_wt << endl;
    cout << "Average Waiting Time: " << fixed << setprecision(2) << avg_wt << endl;
    cout << endl;

    return 0;
}
