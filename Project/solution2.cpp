#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>
using namespace std;

vector<pair<int, int>> inputRes(string line) {
    int i = 0;
    if (line.empty()) {
        return {};
    }
    vector<pair<int, int>> res;
    stringstream ss(line);
    int num;
    while (ss >> num) {
        res.push_back(make_pair(i, num));
        i++;
    }
    return res;
}

void sort(vector<pair<int, int>>& input) {
    for (int i = 0; i < input.size(); i++) {
        for (int j = i+1; j < input.size(); j++) {
            if (input[i].second > input[j].second) {
                swap(input[i], input[j]);
            }
        }
    }
}

void solution2(vector<pair<int, int>> input) {
    if (input.empty()) {
        cout << "No duplicates" << endl;
        return;
    }

    vector<pair<int, int>> sortedByValue = input;
    sort(sortedByValue);

    int maxCount = 0;
    int currentCount = 1;
    deque<pair<int, int>> candidates;
    bool foundDuplicate = false;

    for (int i = 1; i < sortedByValue.size(); i++) {
        if (sortedByValue[i].second == sortedByValue[i-1].second) {
            currentCount++;
            if (currentCount == 2) foundDuplicate = true;
        } else {
            if (currentCount >= 2) {
                candidates.push_back({sortedByValue[i-(currentCount-1)].first, currentCount});
                maxCount = max(maxCount, currentCount);
            }
            currentCount = 1;
        }
    }
    
    if (currentCount >= 2) {
        candidates.push_back({sortedByValue.back().first, currentCount});
        maxCount = max(maxCount, currentCount);
    }

    if (!foundDuplicate) {
        cout << "No duplicates" << endl;
        return;
    }

    int earliestIndex = INT_MAX;

    while (!candidates.empty()) {
        pair<int, int> candidateFront = candidates.front();
        if (candidateFront.second == maxCount) {
            if (candidateFront.first < earliestIndex) {
                earliestIndex = candidateFront.first;
            }
        }
        candidates.pop_front();
    }

    cout << input[earliestIndex].second << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while (getline(cin, line)) {
        vector<pair<int, int>> res = inputRes(line);
        solution2(res);
    }

    return 0;
}