// Computing Structures Project -2 //
// Bala Nagaraju Narra//

//Importing necessary libraries//
#include <iostream>
#include <string>

using namespace std;

// creating a class named TokenProbability//
class TokenProbability {
// creating 3 variables in protected
protected:
    string fromWords;
    string toWords;
    float probability;
// To access the variables in protected we create get variables and set them
public:
    TokenProbability() : probability(0.0) {} // set probability to 0.0//
 // To access the variables in protected we create get variables and set them//
    TokenProbability(string from, string to, float prob)
        : fromWords(move(from)), toWords(move(to)), probability(prob) {}

    string getFromWords() { // getFromWords returns fromWords//
        return fromWords;
    }

    void setFromWords(string from) { // assigning from value to fromWords//
        fromWords = move(from);
    }

    string getToWords() {   // getToWords returns toWords//
        return toWords;
    }

    void setToWords(string to) {   // assigning to value to toWords// 
        toWords = move(to);
    }

    float getProbability() { //getter method returns probability//
        return probability;
    }

    void setProbability(float prob) {// setter method assign prob value to probability//
        probability = prob;
    }
// destructor
    ~TokenProbability() {}
        
    
};

//Creating a class named LanguageModel//
class LanguageModel {
//declaring access specifire//
protected:
    int modelSize;//int variable modelsize//
    TokenProbability* tp;//tp pointer to TokenProbability//

public:
    LanguageModel() {
        modelSize = 0;//intializing modelsize to 0//
        tp = nullptr;//set tp to nullptr//
    }
//destructor deallocationg the memory allocated for the model//
    ~LanguageModel() {
        delete[] tp;
    }

//creating a void function insert with 3 variables//
    void insert(string fromWords, string toWords, float probability) {
        //dynamically allocate new array of TokenProbability objects temp//
        //with size modelSize+1//
        TokenProbability* temp = new TokenProbability[modelSize + 1];
        //looping through model size-1 and assign obect from tp to same index in temp//
        for (int i = 0; i < modelSize; i++) {
            temp[i] = tp[i];
        }
        //creates new TokenProbability for fromWord, toword and probability//
        temp[modelSize] = TokenProbability(fromWords, toWords, probability);
        delete[] tp;//deallocates the allocated memory//
        tp = temp;//updating tp with temp//
        modelSize++;//incerasing size of model//
        //Printing output to console//
        cout << "Inserting: " << fromWords << " : " << toWords << " "<<probability << endl;
        
    }

//creating void function with 2 variables to remove matched words//
void remove(const string& fromWords, const string& toWords) {
    for (int i = 0; i < modelSize; i++) {//for loop through modelsize//
        //match for both fromwords and towords both//
        if (tp[i].getFromWords() == fromWords && tp[i].getToWords() == toWords) {
            // Remove the model by shifting the remaining elements in the array
            for (int j = i; j < modelSize - 1; j++) {
                tp[j] = tp[j + 1];
            }
            // Decrement the modelSize to reflect the removal
            modelSize--;
            return;
        }
    }
        //if there is no match for fromword then print error message//
        cout << "\n";
        cout << "Error: " << fromWords << " : " << toWords << " not present to remove." << endl;
}

//creating the void function modify with 3 variables to modify matched words//
void modify(string fromWords, string toWords, float probability) {
    bool found = false;//set found to boolean false//
    for (int i = 0; i < modelSize; i++) {//loop through modelsize//
        //if both fromwords and toWords matched with fromWords and toWords//
        //then update the TokenProbability with new fromWords and ToWords//
        if (tp[i].getFromWords() == fromWords && tp[i].getToWords() == toWords) {
            tp[i] = TokenProbability(fromWords, toWords, probability);
            found = true;//set found to true if condition is true//
            
            break;
        }
    }
    //if condition is false then print error message//
    if (!found) {
        cout << "\n";
        cout << "Error: " << fromWords << " : " << toWords << " not present to modify." << endl;
    }
}

void createSentence(string& result, string& currentInput) {
    // Find the last two words in the current input
    string a, b, ab;//declaring variables a, b, ab//
    size_t pos1 = currentInput.rfind(' '); //searching for last space//
    size_t pos2 = currentInput.rfind(' ', pos1 - 1);//searching second-to-last space//
    if (pos1 == string::npos) {//no space means only one word//
        // Only one word, assign it to 'b'
        b = currentInput;
    } else if (pos2 == string::npos) {//If no second space then we have 2 words//
        // Two words, assign the last word to 'b' and the first word to 'a'
        a = currentInput.substr(0, pos1);
        b = currentInput.substr(pos1 + 1);
        ab=a+" "+b;//adding a and b assigning to ab//
    } else {
        // More than two words, assign the second-to-last word to 'a' and the last word to 'b'
        a = currentInput.substr(pos2 + 1, pos1 - pos2 - 1);
        b = currentInput.substr(pos1 + 1);
        ab=a+" "+b;
    }

// creating variables to get next word and probability//
    string nextWord;
    string nextWordab;
    float Pb = 0.0;
    float Pab = 0.0;

    // Function to find the probability of the word that follows 'b' (if it exists)

    float maxProbability = 0.0f;//setting max probability to 0//
    //looping model to search b with from word//
    
    for (int k = 0; k < modelSize; k++) {
        //if matched then take probability from model//
        if (tp[k].getFromWords() == b) {
            float currentProbability = tp[k].getProbability();
            //if current probability is greater than maxProbability take toWord //
            //and reassign currentProbaility with maxProbability//
            if (currentProbability > maxProbability) {
                nextWord = tp[k].getToWords();
                maxProbability = currentProbability;
            }
        }
    }

    Pb = maxProbability;//assigning above matched probability to Pb//


    // Function to find the probability of 'a' and 'b' together

    maxProbability = 0.00;//reassigning max probability to 0//

        //looping model for comparing ab with fromWord//
        for (int k = 0; k < modelSize; k++) {
            //if matched then take probability//
            if (tp[k].getFromWords() == ab) {
                float currentProbability = tp[k].getProbability();
                //if currentProbability greater than maxProbability take toWord//
                //and reassign maxProbability to currentProbability//
                if (currentProbability > maxProbability) {
                    nextWordab = tp[k].getToWords();
                    maxProbability = currentProbability;
                }
            }
        }
        Pab = maxProbability;//assigning maxProbability to Pab//

    string updatedResult;//variable for updating result with mathed words//
    
    //counting the words in the result and updating//
    int wordcount = 1;
    int length = result.length();
    for (int i = 0; i < length; i++) {
        if (result[i] == ' ') {
            wordcount++;
        }
    }

    //condition for nextword from both b and ab matching not empty string//
    if (nextWord.empty() && nextWordab.empty()) {
        //max words of our sentence should be less than 20 print final sentence//
        if(wordcount <= 20){
        cout << "Output: "<<result << endl;
        return;
    }}
    //if both probabilities not equal to 0 means next word is not empty//
    if(Pb != 0 || Pab != 0){
    //Comparing both probabilities and take the next word from maxprobability match//
    if (Pb > Pab) {
        updatedResult= result + " " + nextWord;
        //recursing the createSentence with our updated result//
        createSentence(updatedResult, updatedResult);

    } else {
        updatedResult = result + " " + nextWordab;
        //recursing the createSentence with our updated result//
        createSentence(updatedResult, updatedResult);
    }}
    
}

//function for displaying model by looping and getting FromWords, ToWords, Probability and printing them in output console//
void display() {
    cout << "Printing the Language Model:" << endl;
        for (int i = 0; i < modelSize; i++) {
            cout << tp[i].getFromWords() << " : " << tp[i].getToWords() << " : " << tp[i].getProbability() << endl;
 }

}};

//main function// 
int main() {
    //variables for command//
    char commandChar;
    // setting model to new model//
    LanguageModel* lModel = new LanguageModel();
    //Entering While loop and prompt user to enter command//
    while (cin >> commandChar) {
        //using switch case for different characteds//
        switch (commandChar) {
            case 'I': {//If character is I then //
                
                //declaring variables and temporary variables for input//
                int fromcount;
                int tocount;
                string fromwords;
                string towords;
                string fromWords;
                string toWords;
                float probability;
                
                //prompt user to input count for fromwords and towords//
                cin >> fromcount>>tocount;
                
                //based on fromcount loop and prompt user for fromwords input//
                for (int i = 0; i<fromcount; i++) {
                cin >> fromwords;//input prompt//
                fromWords += fromwords+" ";}//add fromwords to previous froword and space in end//
                fromWords.pop_back();//removing last space//
                
                //based on tocount loop and prompt user for towords input//
                for (int i = 0; i<tocount; i++) {
                cin >> towords;//input prompt//
                toWords += towords+" ";}// add towords to previous towords and space in end//
                toWords.pop_back(); //removing last space//

                cin >> probability;//input for probability//

                //calling insert function from lModel//
                lModel->insert(fromWords, toWords, probability);
                break;
            }
            case 'M': { //If character is  M then//
               //variables for temperary string and probability and words//
                int fromcount;
                int tocount;
                string fromwords;
                string towords;
                string fromWords;
                string toWords;
                float probability;

                //user input for count for from and to words//
                cin >> fromcount>>tocount;
                
                //loop for from count to enter fromwords//
                for (int i = 0; i<fromcount; i++) {
                cin >> fromwords;//user input for fromwords//
                fromWords += fromwords+" ";}//adding fromwords to previous fromword and space in end//
                fromWords.pop_back();//removing space in the end//
                
                //loop for tocount to enter to words//
                for (int i = 0; i<tocount; i++) {
                cin >> towords;//user input for towords//
                toWords += towords+" ";}//adding towords to previous toword and space in end//
                toWords.pop_back();//removing last space//
                
                cin >> probability;//input for probability//
                //calling the modify function from lModel//
                lModel->modify(fromWords, toWords, probability);
                break;
            }
            case 'R': {//If character is R then//
                //declaring variables for count and words to remove//
                int fromCount;
                int toCount;
                string fromwords;
                string towords;
                string fromWords;
                string toWords;

                //user input for count//
                cin >> fromCount>>toCount;
                
                //loop through fromcount and take user input//
                for (int i = 0; i<fromCount; i++) {
                cin >> fromwords;
                fromWords += fromwords+" ";}//adding words to previous word and space in end//
                fromWords.pop_back();//removing last space//
                
                //loop through tocount and take user input//
                for (int i = 0; i<toCount; i++) {
                cin >> towords;
                toWords += towords+" ";}//adding towords to previous towords and space in end//
                toWords.pop_back();//removing last space//
                //calling remove model//
                lModel->remove(fromWords, toWords);
                break;
            }
            case 'S': {//If character is S then//
                //declaring variables//
                int wordCount;
                string word;
                string currentstring;
                //user input for word count//
                cin>>wordCount;
                // loop through wordcount and taking input for words//
                for (int i=0; i<wordCount; i++){
                    cin>> word;
                    currentstring+=word+" ";//adding words with previous word and space in end;
                    }
                currentstring.pop_back();//removing the last space//
                //printing the user input in output console//
                cout<<"Input: "<<currentstring<<endl;
                //calling the function for creating sentence with updated result//
                lModel->createSentence(currentstring, currentstring);
                break;
            }
            default:
                break;
        }
    }
    lModel->display();//displaying the model after while loop//
    return 0;
};
