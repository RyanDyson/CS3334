#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<int> inputRes(string line) {
    if (line.empty()) {
        return {};
    }
    vector<int> res ;
    vector<string> arr;

    stringstream ss(line);
    string word;
    while (ss >> word) {
        arr.push_back(word);
    }

    for (int i = 0; i < arr.size(); i++) {
        res.push_back(stoi(arr[i]));
    }

    return res;
}

void solution1(vector<int> input) {
    int maxCount = 0;
    int maxIndex = 0;

    for (int i=0; i<input.size(); i++) {
        int currCount = 0;
        for (int j=0; j<input.size(); j++) {
            if (input[i] == input[j]) {
                currCount++;
            }
        }
        if (currCount > maxCount) {
            maxCount = currCount;
            maxIndex = input[i];
        }
    }

    cout << maxIndex << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while(getline(cin, line)) {
        vector<int> res = inputRes(line);

        solution1(res);
    }
}