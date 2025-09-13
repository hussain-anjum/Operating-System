#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "Enter the no of process: ";
    cin >> n;
    if (n <= 0)
    {
        cerr << "Invalid no of process" << endl;
        return 1;
    }
    int bt[n];
    int wt[n];
    int total_tat = 0, total_wt = 0;

    for (int i = 0; i < n; i++)
    {
        cout << "Enter the burst time for P" << i << ": ";
        cin >> bt[i];
        if (bt[i] < 0)
        {
            cerr << "Burst time can not be non-negative" << endl;
            return 1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        total_tat += bt[i];
    }

    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
    }

    double avg_wt = (double)total_wt / n;

    cout << "\nProcess\t\tBurst time\tWaiting time" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "P" << i << "\t\t" << bt[i] << "\t\t" << wt[i] << endl;
    }
    cout << "\nTotal turn around time: " << total_tat << endl;
    cout << "Total waiting time: " << total_wt << endl;
    cout << "Average waiting time: " << fixed << setprecision(2) << avg_wt;
}