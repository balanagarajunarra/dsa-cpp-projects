// Bala Nagaraju Narra //
// Computing structures Project 4//


//Loading necessary libraries //
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Creating a function to add elements to the set in ascending order with set variable//
void addElement(vector<int>& set) {
    int numElements; // declaring a variable for number of elements in a set//
    //cout << "Enter the number of elements in the set: ";
    cin >> numElements; // input of numElements //

    for (int i = 0; i < numElements; ++i) { //using for loop to add elements to the set in ascending order//
        int element; //variable for rlrmrnts in set //
        cin >> element; //input of element//
        // Find the correct position to insert the element in ascending order
        auto it = lower_bound(set.begin(), set.end(), element);
        set.insert(it, element); //adding element//
    }

    // Remove duplicates
    vector<int> tempSet; //creating a temperory variable//
    for (int i = 0; i < set.size(); ++i) { //iterating elements in the set through set size//
        //checking current element is first or different from previous element//
        if (i == 0 || set[i] != set[i - 1]) {
            tempSet.push_back(set[i]); //if true add our unique element to the set//
        }
    }
    set = tempSet; //assign tempset to set
}


// Creating a function to display the set in ascending order of elements with variables setname and elements//
void displaySet(const string& setName, const vector<int>& set) {
    cout << setName << ":"; //print setname//
    for (int element : set) { //iterate elements in the set and print them//
        cout << " " << element; //print space//
    }
    cout << endl; //print endline//
}


// creating a function to display result from query with variables set elements//
void displayQuery(const vector<int>& set) {
    for (int element : set) {  //iterate elemente in the set//
        cout << element<<" "; //print the elements and space inbetween//
    }
    cout << endl; //print endline////
}


//creating a function to find union of two sets with variables of vector sets//
vector<int> findUnion(const vector<int>& set1, const vector<int>& set2) {
    vector<int> result; //creating a vector to store result of union//
    int i = 0, j = 0; //initializing i and j pointers for both sets as 0//
    //Iterating both the set's elements for comparing//
    while (i < set1.size() && j < set2.size()) {
        //comparing element in both sets//
        if (set1[i] < set2[j]) { //if true element of set1 less than set2//
            result.push_back(set1[i]); //add the set1 elements to result
            i++; //increment the set1 index//
        } else if (set1[i] > set2[j]) { //If set1 element greater than set2 element//
            result.push_back(set2[j]); //add the set2 element to result//
            j++; //increment set2 index//
        } else {
            result.push_back(set1[i]); //If both are equal add from set1//
            i++; // increment both sets index//
            j++;
        }
    }
    //adding remaining elements if any from set1//
    while (i < set1.size()) {
        result.push_back(set1[i]);
        i++;
    }
    //adding remaining elements if any from set2//
    while (j < set2.size()) {
        result.push_back(set2[j]);
        j++;
    }
    return result; //return the result which contain union of both sets//
}

//Create a funtion to return intersection of 2 sets with vector variables//
vector<int> findIntersection(const vector<int>& set1, const vector<int>& set2) {
    vector<int> result; //vectore to store the result//
    int i = 0, j = 0; //initializing pointers i and j for both sets as 0//
    
    //iterating elements of both sets if any//
    while (i < set1.size() && j < set2.size()) {
        if (set1[i] < set2[j]) { //if element of set1 less than set2//
            i++; //increment pointer of set1//
        } else if (set1[i] > set2[j]) { //if element of set1 greater than set2//
            j++; //increment pointer of set2//
        } else { //if both elements are equal//
            result.push_back(set1[i]); //add the common elements to the result//
            i++; //increment both the pointers//
            j++;
        }
    }
    return result; //return the result which contain intersection of both sets//
}

//Creating main function//
int main() {
    int numSets; //variable for number of sets//
    //cout << "Enter the number of sets: ";
    cin >> numSets; //enter the number of sets//

    //creating vector of pairs that contain string setname and vector of integers elements of sets//
    vector<pair<string, vector<int>>> sets; 

    //looping for input of sets//
    for (int i = 0; i < numSets; ++i) {
        string setName; //variable for set name//
        cin >> setName; //Entering set name//
        //initializing vector of integers elements of sets//
        vector<int> elements;
        addElement(elements); //calling addElement funtion to store elements in sets//
        //creating pairing for setname and its elements and storing them in sets vector//
        sets.push_back(make_pair(setName, elements));
    }

    // Sorting sets based on set names alphabetical order
    for (int i = 0; i < numSets; ++i) { //iterating through sets//
        for (int j = i + 1; j < numSets; ++j) { //iterate to compare all sets with current set//
            if (sets[i].first > sets[j].first) { //If set1 name comes before set2//
                swap(sets[i], sets[j]); // swap their positions in the sets vector//
            }
        }
    }

    vector<vector<int>> setsInOperation; //vector of vector to store sets we do operation on//
    vector<int> result; //vectore to store result//
    string setName; //variable for setname string//
    char operationType; //character to store type of operation
    int numSetsInOperation; //integer to store number of sets for operation//
    vector<string> Query; //vectore to store queries (number of sets<<set names<<operation)//


    //start while loop and input number of sets for querying//
    while(cin >> numSetsInOperation){

    Query.push_back(to_string(numSetsInOperation));//add numSetsInOperation to Query//

    cin >> setName; //Enter the first set for query//
    Query.push_back(setName); //add setname to query//
    
    // Find the set with the given name
    int foundIndex = -1; //temperorily assigning foundIndex as -1//
    for (int i = 0; i < numSets; ++i) { //iterate through sets//
        if (sets[i].first == setName) { //compare our setname with setnames in sets//
            foundIndex = i; //if found change -1 to current index//
            break; //break the loop//
        }
    }

    if (foundIndex != -1) { //if foundIndex not -1 then//
        result = sets[foundIndex].second; //store the set elements in result//
    } else { //otherwise display set not found//
        cout << "Set with name '" << setName << "' not found. Exiting.\n";
        return 1;
    }

    // Process the remaining sets and operations
    for (int i = 1; i < numSetsInOperation; ++i) { //iterating the sets//
        cin >> operationType; //reading the operation type union or intersection//
        Query.push_back(string(1, operationType)); //add operation to query//
        cin >> setName; //Enter next set name//
        Query.push_back(setName); //add next setname to query//
        
        // Find the set with the given name
        int foundIndex = -1;
        for (int i = 0; i < numSets; ++i) {
            if (sets[i].first == setName) {
                foundIndex = i;
                break;
            }
        }
        //If setname found then proceed//
        if (foundIndex != -1) {
            if (operationType == 'A') { //check the operation type is A//
                result = findIntersection(result, sets[foundIndex].second); //If true call Intersection function and update the result//
            } else if (operationType == 'O') { //check operation type is O//
                result = findUnion(result, sets[foundIndex].second);//If true call Union function and update the result//
            } else { //If operation is neither A nor O then print invalid operation//
                cout << "Invalid operation type. Skipping operation.\n";
                break;
            }
        } else { //If set name is not found then print setname//
            cout << "Set with name '" << setName << "' not found. Skipping operation.\n";
            break;
        }
    }
    // Print query we stored while entering setnames and operation type with space inbetween//
    for (size_t i = 0; i < Query.size(); ++i) {
        cout << Query[i];
        if (i < Query.size() - 1) {
            cout << " ";
        }
    }
    Query.clear(); //once print we clear the query vector//
    cout<<": "; //print colon after query//
    
    // Display the result of the operation//
    displayQuery(result); //calling displayQuery function to print result of query//
    }

    // Displaying the input sets in alphabetical order of names
    cout << "\nPrinting file data:\n"; //printing header//
    for (const auto& entry : sets) { //looping to print the sets with their elements//
        displaySet(entry.first, entry.second); //calling the displaySet function//
    }
    return 0;
}
