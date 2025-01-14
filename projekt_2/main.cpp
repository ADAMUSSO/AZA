#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet {
private:
    vector<int> parent;

public:
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;//each element is its own parent
        }
    }
    int small(int s) {
        if (s == parent[s]) {
            return s;
        }
        return parent[s] = small(parent[s]);//compress the path for further search
    }
    void unionSets(int u, int v) {
        parent[u] = v;//union of 2 sets
    }
};

struct Job {
    int id;
    int deadline;
    int profit;
};

bool compareJobs(Job a, Job b) {
    return a.profit > b.profit;//sort based on profit
}

int main() {
    int profit_sum = 0;
    int d = 0;
    int n = 0;
    cout << "Number of jobs: ";
    cin >> n;
    vector<Job> Jobs(n);
    //program is set to autofill but can be moddified for user input
    ///////////AUTO FILL
    vector<int> jobs_deadline = {2, 4, 3, 2, 3, 1, 1};
    vector<int> jobs_profit = {40, 15, 60, 20, 10, 45, 55};
    for(int i = 0; i < n; ++i) {
        Jobs[i].id = i + 1;
        //////////////////USER INPUT
        //cout << "deadline of job number " << i + 1 << ": ";
        //cin >> jobs[i].deadline;
        //cout << "profit of job number " << i + 1 << ": ";
        //cin >> jobs[i].profit;
        //////////////////AUTOMATIC INPUT
        Jobs[i].deadline = jobs_deadline[i];
        Jobs[i].profit = jobs_profit[i];
    }

    sort(Jobs.begin(), Jobs.end(), compareJobs);
    for (const auto& job : Jobs) {
        d = max(d, job.deadline);//finding max deadline
    }
    DisjointSet ds(d + 1);//create disjoint set up to max deadline +1


    for (const auto& job : Jobs) {
        int availableSlot = ds.small(job.deadline); //finding free spot on its deadline or sooner
        if (availableSlot > 0) {
            ds.unionSets(availableSlot, ds.small(availableSlot - 1)); //put job in the spot and update
            profit_sum += job.profit;
            cout << "Job " << job.id << " scheduled at slot " << availableSlot << " with profit " << job.profit << endl;
        }
    }
    cout << "Total Profit: " << profit_sum << endl; //output final profit
    return 0;
}
