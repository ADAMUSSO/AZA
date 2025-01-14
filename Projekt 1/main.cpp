#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct Job {
    int id;
    int profit;
    int deadline;
} Job;

//Compare profits for sort
bool compareJobs(Job a, Job b) {
    if (a.profit == b.profit) {
        return a.deadline < b.deadline;
    }
    return a.profit > b.profit;
}

//schedule function to check if job can be assigned
int schedule(vector<Job>& jobs, vector<int>& jobSchedule) {
    int totalProfit = 0;
    for (int i = 0; i < jobs.size(); ++i) {
        if(jobSchedule[jobs[i].deadline] == -1){
            jobSchedule[jobs[i].deadline] = jobs[i].id;
            totalProfit += jobs[i].profit;
        }

    }
//return sum of the profit of the scheduled jobs
    return totalProfit;
}
//output of the jobs and final profit
void print_final(const vector<int>& jobSchedule, int maxDeadline, int totalProfit) {
    cout << "Scheduled jobs: ";
    for (int i = 1; i <= maxDeadline; ++i) {
        if (jobSchedule[i] != -1) {
            cout << "Job " << jobSchedule[i] << " ";
        }
    }
    cout << "\nOverall income: " << totalProfit << endl;
}

int main() {
//main can be modified to be able to handle user input
    int n = 0;
    cout << "Number of jobs: ";
    cin >> n;
    vector<Job> jobs(n);
    ///////////AUTO FILL
    vector<int> jobs_deadline = {2, 4, 3, 2, 3, 1, 1};
    vector<int> jobs_profit = {40, 15, 60, 20, 10, 45, 55};
    for(int i = 0; i < n; ++i) {
        jobs[i].id = i + 1;
        //////////////////USER INPUT
        //cout << "deadline of job number " << i + 1 << ": ";
        //cin >> jobs[i].deadline;
        //cout << "profit of job number " << i + 1 << ": ";
        //cin >> jobs[i].profit;
        //////////////////AUTOMATIC INPUT
        jobs[i].deadline = jobs_deadline[i];
        jobs[i].profit = jobs_profit[i];
    }
    //sort the jobs based on the profit
    sort(jobs.begin(), jobs.end(), compareJobs);

    int maxDeadline = 0;
    //calculate maximum deadline value
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }

    vector<int> jobSchedule(maxDeadline + 1, -1);
    int totalProfit = schedule(jobs, jobSchedule);
    print_final(jobSchedule, maxDeadline, totalProfit);
    return 0;
}








