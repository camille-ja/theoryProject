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
    // this sets the variable to have an epsilon terminal
    void setEpsilon();
    void setVariable(string v);
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
    void Variables::setVariable(string v){
        name = v;
    }




class Grammar{
    public:
        //Reads the file and parses the grammar
        void read();
};
    void Grammar:: read(){
        //store the files names into a string for easier access. also makes it easier to evaulate different files since we would only have to make changes here and not throughout the code
        string descriptionFile = "astarGrammar.txt";
        string inputFile = "astarGrammarInput.txt";
        //cin >> descriptionFile; 
        //cin >> inputFile;
        cout << "c++ CFGTest " << descriptionFile << " " << inputFile << endl;

        //Opens an inputstream to read the description file
        ifstream fin;
        //if we cannot open the file, we send an error message
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
        //we have to print out the last variable seperately since we dont want a comma behind the last variable 
        cout << variables[variables.size() - 1] << endl;

        //we know this next line is termals, so we extract that line
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
        //we have to print out the last terminal seperately since we dont want a comma behind the last terminal 
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
                string temp = rules.substr(2, rules.length()); //make a substring behind either one of those symbols
                   string newTemp = temp.substr(0, temp.find(" ")); //now make a substring beginning from behind one of those symbols until we reach a space. this will successfully extract the terminal
                   if(newTemp == "e"){ //set the variable to have an epsilon is the rule includes an epsilon
                       newVariables[i].setEpsilon();
                   }
                   if(!newVariables[i].hasLeft()){ //if it does not already have a left, we set it to be the extracted terminal
                       newVariables[i].setLeft(newTemp);
                   } else if(!newVariables[i].hasRight()) {  //if it does not already have a right, we set it to be the extracted terminal
                       newVariables[i].setRight(newTemp);
                   }
               }
               m++;
               rules = rules.substr(1, rules.length());
           }
       }


        cout << "Rules: " << endl;
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
       cout << "-----------------------------" << endl;

       cout << inputLine << ": ";
       //if the string is empty, meaning it is epsilon, we want to check if the variable accepts epsilon
       if(inputLine == ""){
           if (newVariables[0].hasEpsilon()){
               cout << "Accept" << endl;
           } else {
               cout << "Reject" << endl;
           }
        } else {
            int numRows = 300 * inputLine.length();
            int numCols = 500 * inputLine.length() - 1;


            vector<vector<string>> table(numRows, vector<string>(numCols, ""));   
            cout << " " << endl;         
            

            // Resize the 2D vector
            //table.resize(numRows, vector<Variables>(numCols));

            // Initialize elements
            bool tOne = false;
            bool tTwo = false;

            //LINES 2-5
            for(int i = 0; i < inputLine.length(); i++){ //examine each substring of length 1
                string w = inputLine.substr(i, i + 1); //substring of length 1
                for(int j = 0; j < newVariables.size(); j++){ //for each varaible A
                    if(newVariables[j].getLeft() == w || newVariables[j].getRight() == w){ //test if A -> wi is a rule
                            table[i][i].append(newVariables[j].getVariable()); //if so, place A in table
                        }
                    }
            }
            // for(int i = 0; i < inputLine.length(); i++){
            //     cout << i << " " << table[i][i] << endl;
            // }

            //PROBLEM:: we think l is wrong bc when aa is read, it doesn't go through the loop but because we're putting the variables in A(i,i) we couldn't
            //put it in A(0,n) bc n is 2. So we're interpreting how to put variables in the table (we do this at line 220-226) wrong or we're interpreting how to look for S wrong (we do this at line 317ish)- the book's line 2-5/ line 12
            //second problem: we don't know if our first problem is affecting our main loop (the book's line 7-11). but it's not working 
            for(int l = 2; l <= inputLine.length() - 1; l++){ //line 6
                for(int i = 0; i <= inputLine.length() - l; i++){ //line 7
                    int j = i + l - 1; //line 8
                    for(int k = i; k <= j - 1; k++){ //line 9
                        for(int u = 0; u < newVariables.size(); u++){ //line 10
                            //cout << k << endl;
                            //cout << "test left " << newVariables[u].getVariable() << " " << newVariables[u].getLeft() << " " << newVariables[u].getLeft().length() << endl;

                            if(newVariables[u].getLeft().length() == 2){
                                string var = newVariables[u].getLeft().substr(0,1); //first variable
                                string var2 = newVariables[u].getLeft().substr(1,2); //second variable
                                string f = table[i][k]; //string in the table
                                int b = 0;
                                while(b < f.length() && !tOne){
                                    //cout << "looping " << var << " f:" << f.substr(b,b+1) << " " << f << endl;
                                    if(f.substr(b, b + 1) == var){
                                        //cout << "this works " << tOne << endl;
                                        tOne = true;

                                        int nn = table.size();

                                        //cout << nn << endl;
                                        //[k + 1][j];
                                        string c = table[k + 1][j]; //problem: c is empty
                                        //cout << c << endl;
                                        int g = 0;
                                        //cout << c.length() << endl;
                                        while(g < c.length() && !tTwo){
                                            //cout << "in loop" << endl;
                                            //cout << c.substr(0,1) << var2 << endl;
                                            // if(c.substr(g,g+ 1) == var2){
                                            //     tTwo = true;
                                            //     //cout << "1" << endl;
                                            // }
                                            g++;
                                            //cout << "end looop" << endl;
                                        }
                                    }
                                    b++;
                                }
                                if(tOne && tTwo){ //line 11
                                    table[i][j].append(newVariables[u].getVariable());
                                }
                            }

                            if(newVariables[u].getRight().length() == 2){ //line 10 (for the right)
                                    string var = newVariables[u].getRight().substr(0,1); //first variable
                                    string var2 = newVariables[u].getRight().substr(1,2); //second variable
                                    string f = table[i][k]; //string in the table
                                    int b = 0;
                                    while(b < f.length() && !tOne){
                                        if(f.substr(b, b + 1) == var){
                                            tOne = true;
                                            string c = table[k + 1][j];
                                            int g = 0;

                                            while(g < c.length() && !tTwo){
                                                if(c.substr(g, g+ 1) == var2){
                                                    tTwo = true;
                                                }
                                                g++;
                                            }
                                        }
                                        b++;
                                    }
                                    if(tOne && tTwo){ //line 11 (for the right)
                                        table[i][j].append(newVariables[u].getVariable());
                                    }
                                }
                        }
                }
            }
        
        }
    
    
                    //loop through table?
                    //line 12
                    bool hasS = false;
                    cout << table[0][inputLine.length() -1] << endl;
                    string f =  table[0][inputLine.length() - 1];
                    for(int i = 0; i < f.length(); i++){
                        if(f.substr(i, i + 1) == newVariables[0].getVariable()){
                            hasS = true;
                        }
                    }
                    if(hasS){
                        cout << "Accept" << endl;
                    } else {
                        cout << "Reject" << endl;
                    }
            }
        }
       cout << "-----------------------------" << endl;

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