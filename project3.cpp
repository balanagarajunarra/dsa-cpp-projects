// Bala Nagaraju Narra//
// Load the required libraries//
#include <iostream>
#include <vector>
using namespace std;

// creating class Tree //
class Tree {
protected:
    int size;                 // Store the size of the tree total no of nodes.
    int* parentArray;         // Pointer to the parent array.

public:
    Tree() : size(0), parentArray(nullptr) {}       // Default Constructor initialize size 0 and parent array to nullptr.

    Tree(int noOfNodes) : size(noOfNodes) {
        parentArray = new int[size];                // Create the parent array dynamically based on no of nodes.
        for (int i = 0; i < size; i++) {
            parentArray[i] = -1;                     // Initialize parent array with -1.
        }
    }

// create a function to build the tree dynamically based on user provided nodes.
void buildTree() {
    int parent, numChildren, child; //initialize variables.
    int count = 0;  // Counter to keep track of the number of -1's in the parent array

    // Labeled loop to break out of the outer loop
    outerLoop:
    for (int i = 0; i < size; i++) { //loop through size of tree.
        cin >> parent >> numChildren; //reads input values from user

        // Set the parent of the current node.
        for (int j = 0; j < numChildren; j++)  {
            cin >> child;
            parentArray[child] = parent;   // Set the parent of the child node.
        }

        // Count the number of -1 values to keep track of children.
        count = 0;
        for (int k = 0; k < size; k++) {
            if (parentArray[k] == -1) {
                ++count;
            }
        }

        // Break the loop if count reaches 1 means all necessary children have been assigned
        if (count == 1) {
            break;
        }
    }

    // Check if the outer loop needs to be broken
    if (count != 1) {
        goto outerLoop;
    }
}

    // creating function to get parent of given child node
    int getParent(int child) {
        return parentArray[child];
    }

    // creating function to get children of givn parent.
    vector<int> getChildren(int parent) { // vector is used for dynamic allocation//
        vector<int> children;
        for (int i = 0; i < size; i++) { //loop through size//
            if (parentArray[i] == parent) {
                children.push_back(i);  // add child nodes of given parent to vector//
            }
        }
        return children; //return children//
    }

// creating function to get root node//
    int getRoot() {
        for (int i = 0; i < size; i++) { //loop through the array//
            if (parentArray[i] == -1) { //check if value is -1//
                return i; //return the root node//
            }
        }
        return -1; // Tree is empty or invalid.
    }

//create function to get height of the tree//  
int getHeight(int node) {
    int maxHeight = 0; //initialize the variables/
    int Height;
    for (int i = 0; i < size; i++) { //loop theought array//
        int currentHeight = 0; //initialize current height 0//
        int currentNode = i; //initialize current node as i//

        while (currentNode != -1) { //while loop to check for parent//
            currentNode = parentArray[currentNode];
            currentHeight++; //increament the current height//
        }

        if (currentHeight > maxHeight) { //check current height is maximum or not//
            maxHeight = currentHeight; //assigning current height to maximum height//
        }
    }
        int level = 0; //calculating the level
        int parent = parentArray[node];
        // Traverse up the tree until reaching the root node (parent = -1)
        while (parent != -1) { 
            level++; //increment the level
            parent = parentArray[parent]; //move to the parent of currnet node//
        }
		Height = maxHeight-level; //calculating the height by subtracting maxheight from level//
        return Height; //return the height//
}

    //creating the function for getting level//
    int getLevel(int node) {
        int level = 1; //initializing the level as 1
        int parent = parentArray[node];
        // Traverse up the tree until reaching the root node (parent = -1)
        while (parent != -1) {
            level++; //Increment the level
            parent = parentArray[parent]; //move to the parent of currnet node//
        }
        return level; //return calculated level
    }

    int getSize() { //getting size of the tree
        return size;
    }

    // boolean value for the node is a leaf node in tree structure//
    bool isLeaf(int node) {
        for (int i = 0; i < size; i++) { //loop through the array//
            if (parentArray[i] == node) { //check if current element is equal to given node//
                return false; //return false//
            }
        }
        return true; //return true//
    }

    //create a function to get leaf nodes
    void getLeafNodes(vector<int>& nodes, int root) {
        if (isLeaf(root)) { //If it is a leaf Add the root node to the nodes vector.
            nodes.push_back(root);
        } else {
            for (int i = 0; i < size; i++) {
                // Check if the current element in parentArray is a child of the root node
                if (parentArray[i] == root) {
                    //calling getLeafNodes() function recursively
                    getLeafNodes(nodes, i);
                }
            }
        }
    }

    // creating a function getNodesAtLevel() that returns node at given level.
    vector<int> getNodesAtLevel(int level) {
        vector<int> nodes; //initialize nodes vector for dynamic allocation.
        for (int i = 0; i < size; i++) {
            // check if the level of the current node is equal to given level
            if (getLevel(i) == level) {
                nodes.push_back(i); //add current node to the nodes vector
            }
        }
        return nodes; //return the nodes vector
    }

// create a function getLeastCommomAncestor for given nodes.
    int getLeastCommonAncestor(int nodeA, int nodeB) {
        vector<int> pathA, pathB;
        getPathToRoot(pathA, nodeA); //get the path to the root for given nodeA
        getPathToRoot(pathB, nodeB); //get the path to the root for given nodeB
        int lca = -1; //initialize lca as -1.
        // Iterate from the end of both pathA and pathB to beginning
        for (int i = pathA.size() - 1, j = pathB.size() - 1; i >= 0 && j >= 0; i--, j--) {
            // check if nodes in the paths are equal
            if (pathA[i] == pathB[j]) {
                lca = pathA[i]; // update lca to current common ancestor
            } else {
                break; // stop the loop if the nodes are different
            }
        }
        return lca; // returns the least commmon ancestor
    }

//create function findPath for given nodes
vector<int> findPath(int nodeA, int nodeB) {
    vector<int> pathA, pathB;
    getPathToRoot(pathA, nodeA); //calling getPathRoot function for path and node
    getPathToRoot(pathB, nodeB);
    int lca = getLeastCommonAncestor(nodeA, nodeB); //calling getLeastCommonAncestor function for nodeA and nodeB assigning to lca.
    vector<int> path;

    // Add the path from nodeA to the LCA (including the LCA itself)
    for (int i = 0; i < pathA.size(); i++) {
        path.push_back(pathA[i]); //add the nodes to path in the end of vector.
        if (pathA[i] == lca) { //if path node equal to lca break the function.
            break;
        }
    }

    // Add the path from the LCA to nodeB (excluding the LCA itself)
    bool foundLCA = false;
    //Iterate from end of pathB to the beginning
    for (int i = pathB.size() - 1; i >= 0; i--) {
        if (pathB[i] == lca) {
            foundLCA = true; // set foundLCA to true if path node equal to lca.
        }
        //check if foundLCA is set and current node is not eaqual to lca.
        if (foundLCA && pathB[i] != lca) {
            path.push_back(pathB[i]); // Add current node to path vector
        }
    }

    return path; //return path vector.
}


// create a function getNodesInSubtree to get nodes in the subtree
    void getNodesInSubtree(vector<int>& nodes, int root) {
        nodes.push_back(root); // Add root node to nodes vector
        for (int i = 0; i < size; i++) {
            if (parentArray[i] == root) { //check if the current node is a child of the root
                getNodesInSubtree(nodes, i); // call getNodesInSubtree functio recursively for child node
            }
        }
    }

// create a function getPathToRoot to get the path to the root
    void getPathToRoot(vector<int>& path, int node) {
        path.push_back(node); // Add nodes to the path vector
        if (parentArray[node] != -1) { //check if parent of current node is not the root
            getPathToRoot(path, parentArray[node]); // Call getPathToRoot recursively for parent node
        }
    }

//create a function display to view the treee in output
    void display() {
        // print statement for printing header in output console
        cout << "Displaying the Parent Array:" << endl;
        for (int i = 0; i < size; i++) { //looping throught the parent array
            cout << "Child: " << i << " Parent: "; //print child for each itereation
            int parent = parentArray[i];
            if (parent != -1) { //check if parent is not root then print parent
                cout << parent;
            } else {
                cout << "-1"; // if paarent is root print -1
            }
            cout << endl; //print next line
        }
    }

    ~Tree() {
        delete[] parentArray;    // Deallocate the memory.
    }
};

int main() {
    int numNodes; //initialize number of total nodes in tree
    cin >> numNodes; // take input of number of nodes in tree//
    Tree* myTree = new Tree(numNodes); // create new instance of tree with number of nodes
    myTree->buildTree(); //calling function buildTree to build tree for given no of nodes.

    // Process queries
    char queryType; //initialize queryType
    int nodeA, nodeB, level; // initialize nodeA, nodeB and level
    vector<int> nodes; //initialize nodes vector for dynamic allocation

// once tree is created enter into while loop for processing queries.
    while (cin >> queryType) {
        switch (queryType) {
            // If queryType is L then call getLevel function for given node by user
            case 'L': {
                cin >> nodeA; //user input for getting level
                //print output from called function
                cout << "The level of node " << nodeA << " is: " << myTree->getLevel(nodeA) << endl;
                break; //break the loop
            }
            // If queryType is P then call getParent function for given node
            case 'P': {
                cin >> nodeA; //user input for getting parent
                //print output from called function
                cout << "The parent of node " << nodeA << " is: " << myTree->getParent(nodeA) << endl;
                break; //break the loop
            }
            // If queryType is E then call getNodesAtLevel function for given node
            case 'E': {
                cin >> level; //user input for level
                nodes = myTree->getNodesAtLevel(level); //call the function and save the nodes
                cout << "The nodes at level " << level << " are: "<<endl;
                //Iterate the nodes from the function and print them
                for (int node : nodes) {
                    cout << node << " ";
                }
                cout << endl; //print new line
                break;//break loop.
            }
            // if queryType is C then call getChildren function
            case 'C': {
                cin >> nodeA; //user input for nodes
                nodes = myTree->getChildren(nodeA); //call the getChildren function
                cout << "The children of node " << nodeA << " are: "<<endl;
                //Iterate the nodes vector from the function and print them
                for (int node : nodes) {
                    cout << node << " ";
                }
                cout << endl; //print new line
                break; //break loop
            }
            // if queryType is G then call getLeafNodes function
            case 'G': {
                cin >> nodeA; //user input node
                nodes.clear(); //clearing the nodes vector
                myTree->getLeafNodes(nodes, nodeA); //call the function getLeafNodes function for given nodes
                cout << "The leaf nodes for node " << nodeA << " are: "<<endl;
                // iterate the nodes vector and print the nodes
                for (int node : nodes) {
                    cout << node << " ";
                }
                cout << endl;
                break; //break the loop
            }
            // if queryType is A then call getLeastCommonAncestor function
            case 'A': {
                cin >> nodeA >> nodeB; //user input nodes for getting common ancestor
                //call the function and print the results.
                cout << "The LCA of " << nodeA << " and " << nodeB << " is: " << myTree->getLeastCommonAncestor(nodeA, nodeB) << endl;
                break; //break the loop
            }
            
            // if queryType is A then call isLeaf function
            case 'I': {
                cin >> nodeA; //user input node for knowing it is leaf node or not
                if (myTree->isLeaf(nodeA)) { //if leaf  print the results
                    cout << "The node " << nodeA << " is a leaf." << endl;
                } else { //if not leaf node print the results
                    cout << "The node " << nodeA << " is not a leaf." << endl;
                }
                break; //break the loop
            }

            // if queryType is A then call getNodesInSubtree function
            case 'N': {
                cin >> nodeA; // user input node for getting nodes in subtree
                nodes.clear(); //clear the nodes vector
                myTree->getNodesInSubtree(nodes, nodeA); //call the function to get the nodes in given subtree node.
                //print the results. by iterating nodes
                cout << "The nodes in subtree rooted by " << nodeA << " are: "<<endl;
                for (int node : nodes) { //iterate for printing results
                    cout << node << " ";
                }
                cout << endl;//print new line
                break;//break the function
            }
            
            // if queryType is A then call getHeight function
            case 'H': {
                cin >> nodeA; //user input node for height of that node
                //calling the function and printing the result height of given node
                cout << "The height of " << nodeA << " is: "<<myTree->getHeight(nodeA) << endl;
                break;//break the loop
            }

            // if queryType is A then call findPath function
            case 'F': {
                cin >> nodeA >> nodeB; //user input nodes for getting path betwwen them
                //calling the function findPath and storing result in nodes
                nodes = myTree->findPath(nodeA, nodeB);
                //print the results by iterating the nodes
                cout << "The path between " << nodeA << " and " << nodeB << " is: "<<endl;
                for (int node : nodes) {
                    cout << node << " ";
                }
                cout << endl;//print new line
                break;//break the loop
            }
        }
    }

   myTree->display(); //calling disply function//

    delete myTree; // deallocating memory for tree//

    return 0;
}

