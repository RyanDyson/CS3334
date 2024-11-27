#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
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

void solution3(vector<int> input) {
    unordered_map<int, int> map;
    for (int i = 0; i < input.size(); i++) {
        map[input[i]]++;
    }
    int max = 0;
    int maxIndexx = 0;
    for (int i = 0; i< input.size(); i++) {
        int e = map[input[i]];
        if (e> max) {
            max = e;
            maxIndexx = input[i];
        }
    }
    cout<<maxIndexx<<endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    while(getline(cin, line)) {
        vector<int> res = inputRes(line);

        solution3(res);
    }
}