#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

//Class that creates a variable and defines its terminals
class Variables{
    string name = "-";
    string left = "-";
    string right = "-";
    bool rightExists = false;
    bool leftExists = false;
    bool epsilon = false;
    //Initializes a new variable
    public:
    Variables(string n){
        name = n;
        }
    //Returns the terminal on the left
    string getLeft();
    //Returns the terminal on the right
    string getRight();
    //Returns if the varaible is the start variable or not
    bool hasEpsilon();
    //Sets the left terminal
    void setLeft(string l);
    //Sets the right terminal
    void setRight(string r);
    //Gets the varible
    string getVariable();
    //Returns true if the variable has a left child, false otherwise
    bool hasLeft();
    //Returns true if the variable has a right child, false otherwise
    bool hasRight();
    // add later
    void setEpsilon();
    }; //end of class definition
    
    string Variables::getLeft(){
        return left;       
    }
    string Variables::getRight(){
        return right;
    }  
    bool Variables::hasEpsilon(){
        return epsilon;
    }
    void Variables::setLeft(string l){
        left = l;
        leftExists = true;
    }
    void Variables::setRight(string r){
        right = r;
        rightExists = true;
    }
    string Variables::getVariable(){
        return name;
    }
    bool Variables::hasLeft(){
        return leftExists;
    }
    bool Variables::hasRight(){
        return rightExists;
    }
    void Variables::setEpsilon(){
        epsilon = true;
    }




class Grammar{
    public:
        //Reads the file and parses the grammar
        void read();
};
    void Grammar:: read(){
        string descriptionFile = "astarGrammar.txt";
        string inputFile = "astarGrammarInput.txt";
        //cin >> descriptionFile; 
        //cin >> inputFile;
        cout << "c++ CFGTest " << descriptionFile << " " << inputFile << endl;

        //Opens an inputstream to read the description file
        ifstream fin;
        fin.open(descriptionFile);
        if(fin.fail()){
            cerr << "Files not found" <<endl;
        }
        //Saves the first line of the description file to temp variable
        string tempLine = "";
        getline(fin, tempLine);

        //Adds all variables to a vector
        vector <string> variables;
        for(int i = 0; i < tempLine.size(); i++){
            string symbol = tempLine.substr(i,1); //Saves the substring of the index we're looking at
            if(symbol != "," && symbol != " "){ //Saves the symbol to the vector if it's not a comma or space
                variables.insert(variables.end(), symbol);
            }
        }

        cout << "Variables: ";
        //Prints out the variables in order
        for(int i = 0; i < variables.size() - 1; i++){
            cout << variables[i] << ", ";
        }
        cout << variables[variables.size() - 1] << endl;

        getline(fin, tempLine);
        vector <string> terminals;
        //Saves the terminals to a vector
        for(int i = 0; i < tempLine.size(); i++){
            string symbol = tempLine.substr(i,1); //Gets the string at the index we're looking at
            if(symbol != "," && symbol != " "){ //Saves the symbol if it isn't a comma or space
                terminals.insert(terminals.begin(), symbol);
            }
        }

        cout << "Terminals: ";
        //Prints the terminals in order
        for(int i = terminals.size() - 1; i > 0; i--){
            cout << terminals[i] << ", ";
        }
        cout << terminals[0] << endl;

        //This loop will addvariables of type Variable to a vector
        vector <Variables> newVariables;
        //Loops for the amount of variables we know we have
        for(int i = 0; i < variables.size(); i++){
            string rules = "";
            getline(fin, rules); //Gets an entire line of the rules of a variable
            if(i == 0){ //If we are reading in the start variable, add a special case to add the epsilon
                newVariables.insert(newVariables.end(), Variables(rules.substr(0,1)));
            } //Reads in normal variables and sets the name as what was read in
            else{
                newVariables.insert(newVariables.end(), Variables(rules.substr(0,1)));
            }
            int m = 0; //acts as the index for the index of the rules string we're looking at
            int n = rules.length();
            while(m < n){ //loops untill we've looked at every index of rules
                if(rules.substr(0, 1) == ">" || rules.substr(0, 1) == "|"){ //If we've found one of these symbols, there's a terminal after it
                string temp = rules.substr(2, rules.length());
                   string newTemp = temp.substr(0, temp.find(" "));
                   if(newTemp == "e"){
                       newVariables[i].setEpsilon();
                   }
                   if(!newVariables[i].hasLeft()){
                       newVariables[i].setLeft(newTemp);
                   } else if(!newVariables[i].hasRight()) {
                       newVariables[i].setRight(newTemp);
                   }
               }
               m++;
               rules = rules.substr(1, rules.length());
           }
       }


        cout << "Rules: " << endl;
        cout<< newVariables.size() << endl;
        cout << newVariables[1].getVariable() << endl;
        //Prints out the rules in order. If the variable doesn't have a left, right, or epsilon, nothing is printed for that category
        for(int i = 0; i < newVariables.size(); i++){
            if(newVariables[i].hasLeft()){
                cout << newVariables[i].getVariable() <<  " -> " << newVariables[i].getLeft() << endl;
            }
            if(newVariables[i].hasRight()){
                cout << newVariables[i].getVariable() <<  " -> " << newVariables[i].getRight() <<endl;
            }
            if(newVariables[i].hasEpsilon()){
                cout << newVariables[i].getVariable() <<  " -> " << "e" << endl;
            }
        }
        cout << "Start Variable: " << newVariables[0].getVariable() << endl;

       ifstream newFin;
       newFin.open(inputFile);
       if(newFin.fail()){
           cerr << "Files not found" <<endl;
       }
       while(newFin.eof() == 0){
       string inputLine = "";
       getline(newFin, inputLine);

       cout << inputLine << ": ";
       if(inputLine == ""){
           if (newVariables[newVariables.size() - 1].hasEpsilon()){
               cout << "Accept" << endl;
           } else {
               cout << "Reject" << endl;
           }
        } else {


                int numRows = inputLine.length();
                int numCols = 2 * inputLine.length() - 1;

                vector<vector<Variables>> table(numRows, vector<Variables>(numCols, Variables("--")));

                // Resize the 2D vector
                //table.resize(numRows, vector<Variables>(numCols));

                // Initialize elements

                for(int i = 0; i < inputLine.length() - 1; i++){
                    string w = inputLine.substr(i, i + 1);
                        for(int j = 0; j < newVariables.size(); j++){
                            if(newVariables[j].getLeft() == w || newVariables[j].getRight() == w){
                                table[i][j] = newVariables[j].getVariable();
                            }
                        }
                    }
                }
                 for(int l = 1; l < inputLine.length(); l++){
                     for(int i = 0; i < inputLine.length() - l + 1; i++){
                         int j = i + l - 1;
                         for(int k = i; k < j - 1; k++){
                             if(newVariables[k].getLeft().length() == 2){
                                 string var = newVariables[k].getLeft().substr(0,1); // 10 isolated first variable within the string
                                 for(int r = k + 1; r < newVariables.size(); r++){
                                    if(var == newVariables[r].getVariable()){
                                        
                                    }
                                }
                             }
                         }
                     }
                 }
            }
        }






int main() {
    std::cout << "hi" << std::endl;
    Grammar().read();
    return 0;
}
/**    #!/bin/bash
    g++ main.cpp -o main
./main */

/*It should take two command line arguments. 

The program should be able to read and “parse” the grammar; what I mean by this is that it should be able to identify what the variables, terminals, 
rules, and start variable of the grammar are. Your program should print out all of this info (see below for the format of this output).

The program should go through each string in the second file and print out whether that string is generated by the grammar. 
It should use the algorithm described in Sipser to do this. If you use any other algorithm/approach to test membership, you will not receive any credit.
*/