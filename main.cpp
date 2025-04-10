#include <ostream> // Provides output stream base class 
#include <iostream> // Allows input and output
#include <fstream> // Allows file input and output operations
#include <vector>  // Provides the vector class
#include <algorithm> // Provides common algorithms
using namespace std; //allows us to make print statements without having to keep including std

//Class that creates a variable and defines its terminals
class Variables{
    //intializes string and boolean variables
    string name = "-"; 
    vector<string> terminals;
    bool terminalExists = false;
    bool epsilon = false;
    bool rightT = false; //true if the right variable is a terimnal
    bool leftT = false; //true if left variable is a terminal
    //Initializes a new variable
    public:
    Variables(string n){
        name = n;
        }
    //Returns the terminals
    vector<string> getTerminals();
    bool hasEpsilon();
    //Sets a terminal
    void setTerminal(string t);
    //Gets the varible
    string getVariable();
    //Returns true if the variable has a left child, false otherwise
    bool hasTerminal();
    void setEpsilon();
    //sets the variable to have string v
    void setVariable(string v);
    }; //end of class definition
    //Returns the terminal on the left
    vector<string> Variables::getTerminals(){
        //cout << "hi" << terminalExists << endl;
        return terminals;       
    }
 
    //Returns if the varaible is the start variable or not
    bool Variables::hasEpsilon(){
        return epsilon;
    }
     //Sets the left terminal
    void Variables::setTerminal(string t){
        terminals.insert(terminals.end(), t);
        terminalExists = true;
    }
      //Gets the varible
    string Variables::getVariable(){
        return name;
    }
    //Returns true if the variable has a left child, false otherwise
    bool Variables::hasTerminal(){
        return terminalExists;
    }
    // this sets the variable to have an epsilon terminal
    void Variables::setEpsilon(){
        epsilon = true;
    }
    //sets the variable to have string v
    void Variables::setVariable(string v){
        name = v;
    }




class Grammar{
    public:
        //Reads the file and parses the grammar
        void read();
    };
    /*
    * This program reads a context-free grammar in Chomsky Normal Form from a file and parses its components which are
    * variables, terminals, rules, and a start variable. It then uses the algorithm provided by the Sipser textbook
    * to determine whether each input string from a second file is generated by the grammar.
    */
    void Grammar:: read(){
        //store the files names into a string for easier access. also makes it easier to evaulate different files since we would only have to make changes here and not throughout the code
        string descriptionFile = "equalAsBsGrammar.txt"; //stores the grammar description file to be string easier accessiblilty
        string inputFile = "equalAsBsGrammarInput.txt"; //stores the input file name as a string for easier accessiblilty
        cout << "c++ CFGTest " << descriptionFile << " " << inputFile << endl; //this will print out the first line in the expected output, which indicates what the program is coded in, CFGTest, and the description and input file names

        //Opens an inputstream to read the description file and store as fin
        ifstream fin;
        //if we cannot open the file, we send an error message
        fin.open(descriptionFile);
        if(fin.fail()){
            cerr << "Grammar file not found" <<endl;
        }
        ifstream newFin;  //stores the input file as newFin using an input stream
        newFin.open(inputFile); //opens the file
        if(newFin.fail()){ //if the file was not opened we will send an error message
           cerr << "Input file not found" <<endl;
        }
        //Saves the first line of the description file to temp variable. we initialize the string to be an empty string and then use getLine to update that string to be the first line of the description file
        string tempLine = "";
        getline(fin, tempLine);

        //Adds all variables to a vector
        vector <string> variables;
        for(int i = 0; i < tempLine.size(); i++){ //this will loop through the duration of the string of temp line, which ensures that we parse the entire line
            string symbol = tempLine.substr(i,1); //Saves the substring of the index we're looking at
            if(symbol != "," && symbol != " "){ //Saves the symbol to the vector if it's not a comma or space
                variables.insert(variables.end(), symbol); //we insert to the end of the vector
            }
        }

        cout << "Variables: "; //this will indicate that what we are printing next is out variables
        //Prints out the variables in order
        for(int i = 0; i < variables.size() - 1; i++){ //loop through our variables vector up until the second to last variable
            cout << variables[i] << ", "; //and print out each variable followed by a comma
        }
        //we have to print out the last variable seperately since we dont want a comma behind the last variable 
        cout << variables[variables.size() - 1] << endl;

        //we know this next line is terminals, so we extract that line
        getline(fin, tempLine);
        //initialize a vector for terminals
        vector <string> terminals;
        //Saves the terminals to a vector
        for(int i = 0; i < tempLine.size(); i++){ //this will loop through the duration of the string of temp line, which ensures that we parse the entire line
            string symbol = tempLine.substr(i,1); //Gets the string at the index we're looking at
            if(symbol != "," && symbol != " "){ //Saves the symbol if it isn't a comma or space
                terminals.insert(terminals.begin(), symbol); //we add the symbol to the beginning of the vector
            }
        }

        //we print this to indicate that we are printing out the terminals
        cout << "Terminals: ";
        //Prints the terminals in order
        for(int i = terminals.size() - 1; i > 0; i--){ //print each terminal followed by a comma, excluding the last comma
            cout << terminals[i] << ", ";
        }
        //we have to print out the last terminal seperately since we dont want a comma behind the last terminal 
        cout << terminals[0] << endl;

        //This loop will add variables of type Variable to a vector
        vector <Variables> newVariables;
        //Loops for the amount of variables we know we have
        int counter = 0;
        //initialize an empty string for the rules that we can update later
        string rules = "";
        //create a boolean expression so we can indicate when we have finished reading the rules
        bool doneReading = false;

        //while we are not at the end of the file and we still have rules to read
        while(fin.eof() == 0 && !doneReading){
            rules = ""; //reset rules to be an empty string
            getline(fin, rules); //Gets an entire line of the rules of a variable

            if(rules.length() > 1){ //If we are still reading a rule
                //cout <<  "RULES: " << rules << endl; //print out the rule
                if(counter == 0){ //If we are reading in the start variable, add a special case to add the epsilon
                    newVariables.insert(newVariables.end(), Variables(rules.substr(0,1)));
                } //Reads in normal variables and sets the name as what was read in
                else{
                    //inserts each the rule into the end of newVariables
                    newVariables.insert(newVariables.end(), Variables(rules.substr(0,1)));
                }
                int m = 0; //acts as the index for the index of the rules string we're looking at
                int n = rules.length(); // n is the length of the string of the rules line
                while(m < n){
                    //cout << "------NEW LOOP--------" <<endl;
                    //loops untill we've looked at every index of rules
                    
                    if(rules.substr(0, 1) == ">" || rules.substr(0, 1) == "|"){ //If we've found one of these symbols, there's a terminal or variable after it
                        string temp = rules.substr(2, rules.length()); //make a substring behind either one of those symbols
                        string newTemp = temp.substr(0, temp.find(" ")); //now make a substring beginning from behind one of those symbols until we reach a space. this will successfully extract the terminal
                        if(newTemp == "e"){ //set the variable to have an epsilon is the rule includes an epsilon
                            newVariables[counter].setEpsilon();
                        }
                        newVariables[counter].setTerminal(newTemp);
                }
                m++; //increment m 
                rules = rules.substr(1, rules.length()); //decreases rules length by one so we can evaluate more rules
            }
        }
        else{ //if we are finished set the boolean to true
            doneReading = true;
        }
        counter++;  //incremenet and move to the next string
       }

       //print this to indicate that we are printing the rules
        cout << "Rules: " << endl;
        //Prints out the rules in order. If the variable doesn't have a left, right, or epsilon, nothing is printed for that category
        for(int i = 0; i < newVariables.size(); i++){ //we are looping through the entirity of our newVariables size, since each variable has a rule
            //cout << newVariables[i].getVariable() << "<-- looking at " << endl;
            vector<string> terminalss = newVariables[i].getTerminals();
            for(int qq = 0; qq < terminalss.size(); qq++){
                cout << newVariables[i].getVariable() <<  " -> " << terminalss[qq] << endl;
            }
            /*if(newVariables[i].hasEpsilon()){ //if the variable has an epsilon terminal, we print the variable followed by an arrow followed an e to indicate epsilon
                cout << newVariables[i].getVariable() <<  " -> " << "e" << endl;
            }*/
        }
        //this indicates that we are printing out start variable
        //we stored our last line as rules, which is where the start variable is stored
        cout << "Start Variable: " << rules << endl;
        //read while the input file is not empty
      //  int ww = 0;
        //while(ww < 2){
          //  ww++;
        while(newFin.eof() == 0){
            string inputLine = ""; //Holds the line that's being processed
            getline(newFin, inputLine); //update that string to be the next line in the input file

            cout << inputLine << ": "; //prints the input line followed by a colon which will eventually indicate whether that string accepts or rejects
            //if the string is empty, we want to check if the variable accepts epsilon
            if(inputLine == ""){ //if the input line is empty, we need to check if it has an epsilon allowing for that empty string
                if (newVariables[0].hasEpsilon()){ //if the variable at position 0, which is the start variable has an epsilon, we accept. we know to only check the start variable because the grammar is in chomsky normal form which only allows for epsilon in the start variable
                    cout << "Accept" << endl;
                } else {
                    cout << "Reject" << endl;
                }
            } 
            else { //if the input line is not empty
                int numRows = 300 * inputLine.length(); // we are going to intialize rows and columns for our table. this is kind of a large table but we didn't want to end up with an error due to our table being too small
                int numCols = 500 * inputLine.length() - 1;
                vector<vector<string>> table(numRows, vector<string>(numCols, "")); //this is the table that the rules will be inputted in
                //cout << " " << endl;         

                //Lines 2-5
                for(int i = 0; i < inputLine.length(); i++){ //Examine each substring of length 1
                   // cout << "new substring----" << endl;
                    string w = inputLine.substr(i, 1); //extracts each character from the input line
                    for(int j = 0; j < newVariables.size(); j++){ //Checking rules of each variable A
                        vector<string> terminalss = newVariables[j].getTerminals();
                        for(int q = 0; q < terminalss.size(); q++){
                           // cout << newVariables[j].getVariable() << "-->>> " << terminalss[q] << " = " << w << endl;
                            if(terminalss[q] == w){
                                table[i][i].append(newVariables[j].getVariable());
                              //  cout << " added "  << newVariables[j].getVariable()<< " should match " << table[i][i] << " to " << i << ", " << i << endl;
                            }
                        }
                    }
                }
                //sets the length l of substrings to be analyzed, starting from 2 up to the full input length n.
                for(int l = 2; l <= inputLine.length(); l++){ //line 6
                    //cout << "NEW LINE----------" << endl;
                    //sets the start index i for substrings of length l to iterate over all such substrings in the input.
                    
                    for(int i = 0; i <= inputLine.length() - l; i++){ //line 7
                      //  cout << "newish line" << endl;
                      //  cout << "this is i " << i <<endl;
                        //calculates the end index `j` of the current substring based on its start index i and length l
                        int j = i + l - 1; //line 8
                        //cout << i << ", " << j << endl;
                        //iterates over all possible split positions `k` within the current substring from `i` to `j - 1`.
                        for(int k = i; k <= j; k++){ //line 9
                        //    cout << "this is k " << k <<endl;

                            //checks each grammar rule of the form A → BC to find possible variable combinations.
                            
                            for(int u = 0; u < newVariables.size(); u++){ //line 10 looks at each rule
                          //      cout << "this is u " << u <<endl;

                               
                            //    cout <<" hello " <<  newVariables[u].getVariable() << endl;
                                
                                vector<string> terminalss = newVariables[u].getTerminals();
                                //cout << "---new here---" <<endl;
                                for(int qq = 0; qq < terminalss.size(); qq++){
                                    bool tOne = false; //checking if if table(i, k) contains B
                                    bool tTwo = false; //checking if table(k + 1, j) contains C
                                  //  cout << "this is q " << qq <<endl;

                                   // cout << qq <<" " << terminalss.size() << endl;
                                    if(terminalss[qq].length() == 2){
                                        //cout << " looking at " << terminalss[qq] << endl;
                                        string var = terminalss[qq].substr(0,1); //first variable
                                        string var2 = terminalss[qq].substr(1,1); //second variable
                                        string box1 = table[i][k];
                                      //  cout << table[1][1] << endl;
                                        int b = 0; //a counter  
                                      //  if(i == 1 && k == 1)
                                        //    cout << "var 1: " << var << " var2: " << var2 << " box1:" << box1 << ", i: " << i << ", j: " << j << ", k+1: " << k+1 << endl; 

                                        while(b < box1.length() && !tOne){ //Checking if table (i,k) contains B
                                           // if(i == 1 && k == 1)
                                             //   cout << "------- "<< box1.substr(b, 1) << " " << var << endl;
                                            if(box1.substr(b, 1) == var){ //if the first character in box1 is the first variable
                                                tOne = true; //table(i, k) contains B
                                                string box2 = table[k+1][j];//string in the table
                                               // if(i == 1 && k == 1)
                                                 //   cout << "^^^^^ " << box2 << endl;    
                                                //if(i <= 3)
                                                    //cout << "var 1: " << var << " var2: " << var2 << " box1:" << box1 << " box2 " << box2 << ", i: " << i << ", j: " << j << ", k+1: " << k+1 << endl; 
                                                  
                                               // cout << box1.substr(b,1) << " equals " << var << " " << box2 << endl;
    
                                                int g = 0;//initialize a counter
                                           //     cout << "hi " << box2.length() << endl;
                                              //  cout << box2
                                                while(g < box2.length() && !tTwo){
                                                    if(box2.substr(g, 1) == var2){ //Checking if table(k + 1, j) contains C
                                                        tTwo = true;// table(k + 1, j) contains C
                                                   ///     cout << box2.substr(g,1) << " equals " << var2 << endl;
                                                    }
                                                    g++;//increment g 
                                                }
                                            }
                                            b++;//increment b
                                        }
                                        if(tOne && tTwo){ //line 11
                                          //  if(i == 1 && k == 1)
                                            //cout << "var 1: " << var << " var2: " << var2 << " box1:" << box1 << endl;    
                                        //    cout << " ^^^^^^^^^adding " << newVariables[u].getVariable() << " at " << i << " " << j << endl;
                                            table[i][j].append(newVariables[u].getVariable()); //if both are true add variable A to table(i, j) if B is in table(i, k) and C is in table(k + 1, j).
                                        }
                                    }
                                }
                        }
                    }
                }
            }
                //line 12
                bool hasS = false; //accepts the input if the start variable S is in table(1, n); otherwise, it rejects.
                //cout << inputLine.length() - 1 << endl;
                string f =  table[0][inputLine.length() - 1]; //initializes f as a string in the table
                ///cout << "look " << f << endl;
                for(int i = 0; i < f.length(); i++){ //loop thru the entirety of f
                    if(f.substr(i, 1) == "S"){ //if s is found in f, hasS is true
                        hasS = true;
                    }
                }
                if(hasS){ //if S was in table(1,n) accpet
                    cout << "Accept" << endl;
                } 
                else { //if it's not, reject
                    cout << "Reject" << endl;
                }
            }
        }
    }
//run the grammar
int main() {
    Grammar().read();
    return 0;
}