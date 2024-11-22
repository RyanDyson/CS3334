#include <iostream>
using namespace std;

int main () {
    int n;
    cin>>n;
    for (int i=0; i<n; i++) {
        int price; int items;
        cin>>price>>items;
        int* itemsArr = new int[items];

        for (int i=0; i<items; i++) {
            cin>>itemsArr[i];
        }

        for (int j=0; j<items; j++) {
            for (int k=j+1; k<items; k++) {
                if (itemsArr[j] + itemsArr[k] == price) {
                    cout<<"Case #"<<i+1<<": "<<j+1<<" "<<k+1<<endl;
                    break;
                }
            }
        }
    }
}