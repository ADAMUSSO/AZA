#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int file_sum = 0;
    int n = 0;
    int size = 0;
    int temp;
    cout << "Insert the number of files: ";
    cin >> n;
    vector<int> files = {12,8,3,1,6,20};
    ///////////////////USER INPUT////////////
    //vector<int> files;

    //for(int i  = 0;i<n;i++){
        //cout << "size of file "<<i+1<<": ";
        //cin >> size;
        //files.push_back(size);
    //}

   cout << "\n";
    while (files.size() > 1){
        sort(files.begin(),files.end());//sort to get minimum at the beginning
        temp = files[0]+files[1];//sum first 2
        file_sum += temp;
        cout<<"File sizes:"<<files[0]<<", "<<files[1]<<" Total  memory:"<<file_sum<<" Remaining files: ";
        files.erase(files.begin(),files.begin()+2);//delete first 2
        files.push_back(temp);//put new at the back
        for(int file : files){
            cout<<file<<", ";
        }
        cout<<"\n";

    }
    cout<<file_sum;//final memory usage



    return 0;
}
