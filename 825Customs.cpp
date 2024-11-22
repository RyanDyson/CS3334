#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;

const int day = 86400;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    deque<pair<int, vector<int>>> allCruises;
    unordered_map<int, int> nationalities;
    int uniqueNationalities = 0;
    int n; cin>>n;

    while (n--) {
        int t, k; cin>>t>>k;
        vector<int> currCruise(k);
        
        int timeWin = t - day + 1;    //1 -86400 = -86399, any cruise's t > -86399 is still counted
        while (!allCruises.empty() && allCruises.begin()->first < timeWin) {
            for (int passenger: allCruises.begin()->second) {
                nationalities[passenger]--;
                if (nationalities[passenger] == 0) {
                    uniqueNationalities--;
                }
            }
            allCruises.pop_front();
        }

        while (k--) {
            int tempPassenger; cin>>tempPassenger;
            if (nationalities[tempPassenger] == 0 ) {
                uniqueNationalities++;
            }
            nationalities[tempPassenger]++;
            currCruise.push_back(tempPassenger);
        }
        pair<int, vector<int>> timeAndCruise = make_pair(t, currCruise);
        allCruises.push_back(timeAndCruise);

        cout<<uniqueNationalities<<endl;
    }
}