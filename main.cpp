#include <ostream>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
void readFiles(){
    string descriptionFile = "astarGrammar.txt";
    string inputFile = "astarGrammarInput.txt";
    //cin >> descriptionFile; 
    //cin >> inputFile;
    cout << "c++ CFGTest " << descriptionFile << " " << inputFile << endl;

    ifstream fin;
    fin.open(descriptionFile);
    if(fin.fail()){
        cerr << "Files not found" <<endl;
    }
    string tempLine = "";
    getline(fin, tempLine);
    cout << "Variables: " + tempLine << endl;

    vector <string> variables;
    //cout << tempLine<< endl;
    for(int i = 0; i < tempLine.size(); i++){
        string symbol = tempLine.substr(i,1);
        if(symbol != "," && symbol != " "){
            variables.insert(variables.begin(), symbol);
        }
    }

    getline(fin, tempLine);
    cout << "Terminals: " + tempLine << endl;

    vector <string> terminals;
    for(int i = 0; i < tempLine.size(); i++){
        string symbol = tempLine.substr(i,1);
        if(symbol != "," && symbol != " "){
            terminals.insert(terminals.begin(), symbol);
        }
    }
    
    vector<string> rules;
    //store rules in vector
    //index 0 is start variable (has to be bc cnf)
    //use separation to find what the rules go to 
   
    

}

int main() {
    std::cout << "hi" << std::endl;
    readFiles();
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