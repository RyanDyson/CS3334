#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main() {
    int n; cin>>n;
    while(n--) {
        int wordCount; cin>>wordCount;
        string* academicWords = new string[wordCount]; //keys for unorderedMap
        for (int i=0; i<wordCount; i++) {
            cin>>academicWords[i];
        }

        int essayCount; cin>>essayCount;
        int partCount = 0; 
        bool isPart = false;
        int academicFreq = 0;
        unordered_map<string, int> essay;
        for (int i=0; i<essayCount; i++) {
            string temp;
            getline(cin, temp);
            essay[temp]++;
            if (isPart) {
                academicFreq++;
            }

            for (int i=0; i<wordCount; i++) {
                if (temp == academicWords[i]) {
                    academicFreq++;
                    isPart = (isPart == true) ? false : true;
                    break;
                }
            }
        }

        cout<<academicFreq<<endl<<partCount<<endl;
    }
}