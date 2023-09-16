// Project 1
// DSA 5005 - Summer 2023
// Bala Nagaraju Narra


#include<iostream>
using namespace std;

//initializing class Interval and defining its member variables
class Interval {
protected:
    int begin;
    int end;

public:
    Interval();
    Interval(int a, int b);
    Interval(Interval& otherInterval);
    Interval& operator=(const Interval& otherInterval);
    bool operator==(Interval& otherInterval);
    bool operator>(Interval& otherInterval);
    bool operator<(Interval& otherInterval);
    int getBegin();
    int getEnd();
};

// Default constructor for Interval class with default constructor for begin and end parameters
// we initialized the begin and end parameters with value of -1
Interval::Interval(){
    begin=-1;
    end=-1;
}

// Default constructor for Interval class with default constructor parameters begin and end 
// we need to assign begin and end parameters with int a and b
Interval::Interval(int a, int b){
    begin = a;
    end = b;
}
// Copy constructor for Interval class 
// with copy constructor for begin and end parameters
Interval::Interval(Interval& otherInterval){
    begin = otherInterval.begin;
    end = otherInterval.end;
}

// Assignment operator for Interval class
// with assignment operator for begin and end parameters
Interval& Interval::operator=(const Interval& otherInterval) {
    if (this != &otherInterval) {
        begin = otherInterval.begin;
        end = otherInterval.end;
    }
    return *this;
}
//if the two intervals overlap returns TRUE
// else returns false
////////////////////////////////////////////////////////////////
bool Interval::operator==(Interval& otherInterval) {
    if (begin == otherInterval.begin && end == otherInterval.end){
        return true;
    }
    else {
        return false;
    }
}

//if the first interval is greater than the second returns TRUE
// else returns false
bool Interval::operator>(Interval& otherInterval) {
    if (begin > otherInterval.begin){
        return true;
    }
    else {
        return false;
    }
}

//if the first interval is less than the second returns TRUE
// else returns false
bool Interval::operator<(Interval& otherInterval) {
    if (begin < otherInterval.begin){
        return true;
    }
    else {
        return false;
    }
}

// Returns the begin value of the interval
int Interval::getBegin() {
    return begin;
}
// Returns the end value of the interval
int Interval::getEnd() {
    return end;
}

// initializing the class IntervalMatrix and defining its member variables
class IntervalMatrix {
protected:
    Interval** MAT;
    int numRows;
    int numCols;

public:
    IntervalMatrix();
    IntervalMatrix(int n, int m);
    IntervalMatrix( IntervalMatrix& otherMAT);
    IntervalMatrix& operator=(IntervalMatrix& otherMAT);
    void MATRead();
    void PrintMAT();
    void FindOverlapping( Interval& X, int Dim);
    void Stabbing(int x, int Dim);
};
// Default constructor for IntervalMatrix class 
//with default constructor for numRows and numCols  MAT parameters
// we need to initialize the numRows and numCols parameters to 0
// We assign MAT to nullptr
IntervalMatrix::IntervalMatrix() {
    numRows = 0;
    numCols = 0;
    MAT = nullptr;
}
// Default constructor for IntervalMatrix class 
//with default constructor for numRows and numCols  MAT parameters
// we assignm n and m to numRows and numCols parameters
// We assign MAT to a pointer to an array 
IntervalMatrix::IntervalMatrix(int n, int m) {
    numRows = n;
    numCols = m;
    MAT = new Interval*[n];
    for (int i = 0; i < n; i++) {
        MAT[i] = new Interval[m];
    }
}
// Copy constructor for IntervalMatrix class 
// with copy constructor for numRows and numCols  MAT parameters
IntervalMatrix::IntervalMatrix( IntervalMatrix& otherMAT){
    numRows = otherMAT.numRows;
    numCols = otherMAT.numCols;
    MAT = new Interval*[numRows];
    for (int i = 0; i < numRows; i++) {
        MAT[i] = new Interval[numCols];
        for (int j = 0; j < numCols; j++) {
            MAT[i][j] = otherMAT.MAT[i][j];
        }
    }
}

// Constructor for IntervalMatrix class
// with default constructor for numRows and numCols  MAT parameters
// we use for loop to initialize MAT parameters
IntervalMatrix& IntervalMatrix::operator=( IntervalMatrix& otherMAT) {
        numRows = otherMAT.numRows;
        numCols = otherMAT.numCols;
        MAT = new Interval*[numRows];
        for (int i = 0; i < numRows; i++) {
            MAT[i] = new Interval[numCols];
            for (int j = 0; j < numCols; j++) {
                MAT[i][j] = otherMAT.MAT[i][j];
            }
        }
    return *this;
}
// Constructor for IntervalMatrix class
// Read from input file and convert to Matrix object using Interval values
void IntervalMatrix::MATRead() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            int begin, end;
            cin >> begin >> end;
            MAT[i][j] = Interval(begin, end);
        }
    }
}

// Constructor for IntervalMatrix class
// Print the Matrix object to output file using Interval values
void IntervalMatrix::PrintMAT() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            cout << MAT[i][j].getBegin() << " - " << MAT[i][j].getEnd() << " ";
        }
        cout << endl;
    }
    cout << endl;
}
// Function to find overlapping intervals in the Matrix
// with the Interval object X and Dim values 
// Dim is the dimension of the Matrix
void IntervalMatrix::FindOverlapping( Interval& X, int Dim) {
    for (int i = 0; i < numRows; i++) { // for loop to find overlapping intervals in the Matrix array with the Interval object X
        //If condition is true, then we find overlapping intervals in the Matrix array
        if (X.getBegin() <= MAT[i][Dim].getEnd() && X.getEnd() >= MAT[i][Dim].getBegin()) {
            cout << i << " ";
        }//It will return the index of the overlapping interval   
    }
    cout << endl;
}

// Function to find overlapping intervals in the Matrix 
// using Stabbing method with the Interval object X and Dim values
void IntervalMatrix::Stabbing(int x, int Dim) {
    for (int i = 0; i < numRows; i++) { // for loop to find overlapping intervals in the Matrix array with the Interval object X
        if (x >= MAT[i][Dim].getBegin() && x <= MAT[i][Dim].getEnd()) {
         // if condition is true, then we find overlapping intervals in the Matrix array
            cout << i << " ";
        }
    }
    cout << endl;
}

// Driver code
// initially numRows and numCols are -1
int main() {
    int numRows=-1;
    int numCols=-1;
    cin >> numRows >> numCols; // read rows and columns from input file and convert them to int
    IntervalMatrix* IM= new IntervalMatrix(numRows, numCols); 
    IM->MATRead(); // read rows and columns from input file and convert them to int
    cout << "Printing the Matrix:" << endl; 
    IM->PrintMAT(); // print the Matrix to output file using Interval values

    char command; // input command line
    int n1, n2, n3; // input values for n1, n2 and n3

    while (cin >> command) { // read command from input file
//condition to check if the command is S or O
//IF the command is S then we need to perform Stabbing method to find overlapping intervals
        if (command == 'S') {
            cin >> n1 >> n2;
            cout << "The Intervals which the point "<< n1 <<"stabs for dimension "<< n2 <<" are:" << endl;
            IM->Stabbing(n1, n2);
            cout << endl;
        } 
 // IF the command is O then we need to perform FindOverlapping method to find overlapping intervals
        else if (command == 'O') {
            cin >> n1 >> n2 >> n3;
            cout << "The Intervals overlapping with the given interval ("<< n1 << ", "<< n2 <<") for dimension "<< n3 << " are:"<< endl;
            Interval X(n1, n2);
            IM->FindOverlapping(X, n3);
            cout << endl;
        }
    }

    return 0;
}
//----------------------------------------------------------------