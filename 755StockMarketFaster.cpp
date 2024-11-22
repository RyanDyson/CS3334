#include <iostream>
#include <stack>
#include <vector>
using namespace std;

long int largestArea(vector<int> &arr, int n) {
    //arr[i]*(right smaller - left smaller - 1)
    stack<int> s;
    long int maxArea = 0;
    for (int i=0; i<=n; i++) {
        while (!s.empty() && (i==n || arr[s.top()] >= arr[i])) {
            long int height = arr[s.top()];
            s.pop();
            long int width = s.empty() ? i : i - s.top() - 1;
            long int temp = width * height;
            if (temp > maxArea) {
                maxArea = temp;
            }
        }
        s.push(i);
    }

    return maxArea;
}

int main() {
 int n; cin>>n;
    while (n-->0) {
        int colNum; cin>>colNum;
        vector<int> arr;
        for (int i=0; i<colNum; i++) {
            int x; cin>>x;
            arr.push_back(x);
        }
        cout<<largestArea(arr, colNum)<<endl;
    }
}