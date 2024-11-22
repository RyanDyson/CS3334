#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

bool isHappy(int n) {
    int sum = 0;
    while (n > 0) {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    if (sum == 1) return true;
    if (sum == 4) return false;
    return isHappy(sum);
}

int main () {
    int n;
    cin>>n;
    for (int i=1 ;i<n+1; i++) {
        if (isPrime(i) && isHappy(i)) {
            cout<<i<<endl;
        }
    }
}   