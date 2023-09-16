#include <iostream>
#include "IntervalMatrix.h"

using namespace std;

int main() {
    // Read input
    int n, m;
    cin >> n >> m;
    IntervalMatrix im(n, m);
    im.MATRead();

    // Test Interval class methods
    Interval i1(2,10);
    Interval i2(2,14);
    cout <<i1 == i2) <<; // should print 0
    cout <<i1 < i2) <<;  // should print 1
    cout << (i1 > i2) <<;  // should print 0

    // Test IntervalMatrix class methods
    im.FindOverlapping(i1, 0);
    im.Stabbing(4, 0);
    IntervalMatrix sortedIm = im.Sort(0);
    sortedIm.PrintMAT();

    // Clean up memory
    for (int i = 0; i <; i++) {
        delete[] im.MAT[i];
        delete[] sortedIm.MAT[i];
    }
    delete[] im.MAT;
    delete[] sortedIm.MAT;

    return 0;
}