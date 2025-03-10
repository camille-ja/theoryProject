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
    bool isStart = false;
    string epsilon = "e";
    //Initializes a new variable
    public:
    Variables(string n, bool e){
        name = n;
        isStart = e;
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
    }; //end of class definition
    
    string Variables::getLeft(){
        return left;       
    }
    string Variables::getRight(){
        return right;
    }  
    bool Variables::hasEpsilon(){
        return isStart;
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
                variables.insert(variables.begin(), symbol);
            }
        }

        cout << "Variables: ";
        //Prints out the variables in order
        for(int i = variables.size() - 1; i > 0; i--){
            cout << variables[i] << ", ";
        }
        cout << variables[0] << endl;

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
                newVariables.insert(newVariables.begin(), Variables(rules.substr(0,1), true));
            } //Reads in normal variables and sets the name as what was read in
            else{
                newVariables.insert(newVariables.begin(), Variables(rules.substr(0,1), false));
            }
            int m = 0; //acts as the index for the index of the rules string we're looking at
            int n = rules.length();
            while(m < n){ //loops untill we've looked at every index of rules
                if(rules.substr(0, 1) == ">" || rules.substr(0, 1) == "|"){ //If we've found one of these symbols, there's a terminal after it
                    string temp = rules.substr(2, rules.length()); //Saves the string at the start of the terminal
                    if(!newVariables[0].hasLeft()){ //If the variable doesn't has a left terminal, set the terminal to be the variables left child
                        newVariables[0].setLeft(temp.substr(0, temp.find(" "))); //Saves the portion of rules until we hit a space
                    } else if(!newVariables[0].hasRight()) { //If the variable doesn't has a right terminal, set the terminal to be the variables right child
                        newVariables[0].setRight(temp.substr(0, temp.find(" ")));
                    }
                }
                m++; 
                rules = rules.substr(1, rules.length()); //Decreases rules so we can look at the next index
            }
        }

        cout << "Rules: " << endl;
        //Prints out the rules in order. If the variable doesn't have a left, right, or epsilon, nothing is printed for that category
        for(int i = newVariables.size() - 1; i >= 0; i--){
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
        cout << "Start Varaiable: " << newVariables[newVariables.size() - 1].getVariable() << endl;
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