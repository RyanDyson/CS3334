#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Quad {
    public:
    static int countNode;
    int data;
    Quad* northWest;
    Quad* northEast;
    Quad* southEast;
    Quad* southWest;

    Quad() {
        countNode++;
        northWest = NULL;
        northEast = NULL;
        southEast = NULL;
        southWest = NULL;
    };
    Quad(int data) { //constructor for root quad tree
        this->data = data;
        northWest = NULL;
        northEast = NULL;
        southEast = NULL;
        southWest = NULL;
    }


    void  divideFour() {
        northWest = new Quad();
        northEast = new Quad();
        southEast = new Quad();
        southWest = new Quad();
    }

    void colorCheck(int** pixels, int wStart, int wEnd, int hStart, int hEnd) {
        bool isAllZero = true;
        bool isAllOne = true;

        for (int i=hStart ;i<hEnd; i++) {
            for (int j=wStart; j<wEnd; j++) {
                if (pixels[i][j] == 1) {
                    isAllZero = false;
                }
                else {
                    isAllOne = false;
                }
            }
        }
        if (isAllOne) {
            data = 1;
        }
        else if (isAllZero) {
            data =  0;
        }
        else {
            data = 2;
        }
    }

    void ans(int** pixels, int wStart, int wEnd, int hStart, int hEnd) {
        this->colorCheck(pixels, wStart, wEnd, hStart, hEnd);

        if (data != 1 && data!= 0) {
            this->divideFour();
            int midW = (wStart + wEnd) / 2;
            int midH = (hStart + hEnd) / 2;

            northWest->ans(pixels, wStart, midW, hStart, midH);
            northEast->ans(pixels, midW, wEnd, hStart, midH);
            southWest->ans(pixels, wStart, midW, midH, hEnd);
            southEast->ans(pixels, midW, wEnd, midH, hEnd);
        }
    }
};

int Quad::countNode = 1;

int main() {
    int k; 
    while(cin>>k) {
        int n = pow(2, k);
        int** arr = new int*[n];

        bool isInitialAllBlack = true;
        bool isInitialAllWhite = true;
        for (int j=0; j<n; j++) {
            int* row = new int[n];
            string input; cin>>input;
            for (int i=0; i<n; i++) {
                row[i] = int(input[i]) - 48;
            }
            arr[j] = row;
        }

        int rootData = isInitialAllBlack ? 0 : (isInitialAllWhite ? 1 : 2);
        Quad::countNode = 1;
        Quad* root = new Quad(rootData);
        root->ans(arr, 0, n, 0, n);
        cout<< root->countNode <<endl;

        for (int i=0; i<n; i++) {
            delete[] arr[i];
        }
        delete[] arr;
        }
    return 0;
}