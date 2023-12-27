#include <bits/stdc++.h>
using namespace std;


//Function to check if character is a letter in the alphabet
bool isAlphabet(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//Function to extract all unique variables entered in the premises and conclusion
vector<char> ExtractVariables(vector<string>Expressions){
    set<char>UniqueVariables;
    for(int i=0;i<Expressions.size();i++)
    {
        for(int j=0;j<Expressions[i].length();j++)
        {
            if(isAlphabet(Expressions[i][j]))
                UniqueVariables.insert(Expressions[i][j]);
        }
    }
    vector<char>Variables;
    for(char element:UniqueVariables)
    {
        Variables.push_back(element);

    }
    return Variables;

}

int main(){
    string statement; //statement entered by user
    vector<string> premises; //vector to hold all premises
    string conclusion;
    vector<string>SetofStatements; // vector to hold all statements (premises and conclusion)
    //Instructions for user
    cout<<"Enter premises in the following format : O + P (type each expression in a new line,only two variables are allowed in each expression)\n";//if expression is one letter and negated it has to be written in this form: !(P)
    cout<<"Use '+' for OR,'^' for AND,'>' for conditional,':' for biconditional and '!' for NOT \n";
    cout<<"Type 'Done' to finish \n";

    //Store user input

    while(1)
    {

        if(statement=="Done")
            break;
        getline(cin,statement);

        if(statement!="Done")
            premises.push_back(statement);


    }

    cout<<"Enter Conclusion:\n";
    getline(cin,conclusion);
    cout<<"\n";

    // Insert all elements from premises at the end of SetofStatements
    SetofStatements.insert(SetofStatements.end(), premises.begin(), premises.end());
    //insert conclusion in SetofStatements
    SetofStatements.push_back(conclusion);

    vector<char>ExtractedVariables = ExtractVariables(SetofStatements);//get unique variables in expressions entered
    int VarNo = ExtractedVariables.size();//get no of variables
    int ValuesNo=pow(2,VarNo);//get no of values for truth table
    vector<vector<int>> truth_table((1<<VarNo),vector<int>(VarNo));//Variables truth table
    bool expTT[ValuesNo][SetofStatements.size()-1];//premises expressions' values
    bool concTT[ValuesNo];//conclusion values

    //generate truth table for variables
        for(int i=0;i<((1<<VarNo));i++){
            for(int j=0;j<VarNo;j++){
                if(i&(1<<j))
                    truth_table[i][j] = 1;
                else
                    truth_table[i][j] = 0;
            }
        }
        //display variable characters
        for(int i=0;i<VarNo;i++)
        {
            cout<<ExtractedVariables[i]<<' ';
        }
        //display variable truth table
        cout<<"\n";
        for(int i=0;i<(1<<VarNo);i++){
            for(int j=0;j<VarNo;j++)
                cout<<truth_table[i][j]<<' ';
            cout<<'\n';
        }

        //mapping variables to certain numbers
        map<char,int>Variables;
        for(int i=0;i<ExtractedVariables.size();i++)
        {
            Variables[ExtractedVariables[i]]=i;
        }

        //loop on each expression

        for(string expression:SetofStatements)
        {
            //setting column number to number of expression
            int column;
            for(int i=0;i<SetofStatements.size();i++)
            {
                if(expression==SetofStatements[i])
                    column=i;
            }

            vector<char>UsedVars;
            vector<bool>expressionvalues;
            char operation='\0';
            bool negatedexp=false;//flag for negated expression
            map<char, bool> NegatedVar; // map to store negated variables

            for (int i = 0; i < expression.size(); i++)
            {
                //check if negation is for whole statement or not
                if (expression[i] == '!')
                {
                    if (expression[i + 1] == '(')
                    {
                        negatedexp=true;
                    }
                    else if (isAlphabet(expression[i + 1]))
                    {
                        char negatedVariable = expression[i + 1];
                        NegatedVar[negatedVariable] = true; // Store negated variable
                    }
                }
            }

            // Update truth table for negated variables
            for (int r = 0; r < ValuesNo; r++)
            {
                for (auto &entry : NegatedVar)
                {
                    truth_table[r][Variables[entry.first]] = !truth_table[r][Variables[entry.first]];
                }
            }

            for(char letter:expression)
            {

                //find the operation symbol
                if(!isAlphabet(letter)&&letter!='!'&&letter!=' '&&letter!='('&&letter!=')')
                    operation=letter;


                // Check if the variable exists in the map
                auto it = Variables.find(letter);

                if (it != Variables.end()) {
                // Variable found in the map
                UsedVars.push_back(letter);
                }

            }

            //pick operation used
            switch(operation)
            {
            case '+':

                for(int i=0;i<ValuesNo;i++)
                {
                    bool rowresult=0;
                    for(char var:UsedVars)
                    {

                        rowresult|=truth_table[i][Variables[var]];
                    }

                    expressionvalues.push_back(rowresult);
                }


                break;
            case '^':
                for(int i=0;i<ValuesNo;i++)
                {
                    bool rowresult=1;
                    for(char var:UsedVars)
                    {
                        rowresult&=truth_table[i][Variables[var]];
                    }

                    expressionvalues.push_back(rowresult);
                }

                break;
            case ':':
                for (int i = 0; i < ValuesNo; i++) {
                    bool rowresult = 1;
                    bool temp=1;
                    for (char var : UsedVars) {
                        temp &=truth_table[i][Variables[var]];
                    }
                    for (char var : UsedVars) {
                        rowresult &=!truth_table[i][Variables[var]];
                    }
                    rowresult|=temp;


                    expressionvalues.push_back(rowresult);
                    }


                break;

            case '>':
                for(int i=0;i<ValuesNo;i++)
                {
                    bool rowresult=!truth_table[i][Variables[UsedVars[0]]];

                    rowresult=rowresult||truth_table[i][Variables[UsedVars[1]]];


                    expressionvalues.push_back(rowresult);
                }

                break;
            default:
                cout<<"Invalid operation";
            }

            //check if whole statement is negated and put values in truth table
            if(negatedexp)
            {
                for(int i=0;i<expressionvalues.size();i++)
                {
                    expressionvalues[i]=!(expressionvalues[i]);
                }
            }


            if(column==premises.size())
            {
                for(int i=0;i<expressionvalues.size();i++)
                {
                    concTT[i]=expressionvalues[i];
                }

            }
            else
            {
                for(int k=0;k<expressionvalues.size();k++)
                {
                    expTT[k][column]=expressionvalues[k];

                }

            }


        }



        cout<<"\n";

        //display premises expressions
        for(int i=0;i<premises.size();i++)
        {
            cout<<premises[i]<<' ';
        }

        cout<<"\n";

        for(int i=0;i<ValuesNo;i++)
        {
            for(int j=0;j<SetofStatements.size()-1;j++)
            {
                cout<<expTT[i][j]<<"      ";
            }
            cout<<"\n";
        }

        cout<<"\n";


        //display conclusion
        cout<<conclusion<<"\n";
        for(int i=0;i<ValuesNo;i++)
        {


            cout<<concTT[i]<<"\n";

        }


        cout<<"\n";



        //Check Satisfiability
        bool satisfiable=false;
        int critical=0;


        for(int r=0;r<ValuesNo;r++)
        {
            bool res=true;
            if(satisfiable==true)
                break;
            for(int c=0;c<VarNo;c++)
            {
                res = res && expTT[r][c];
                if(res==true)
                    critical++;
            }
            satisfiable = res && concTT[r];

        }
        if(satisfiable==true)
            cout<<"Satisfiable";
        else
            cout<<"Not Satisfiable";


        cout<<"\n";
        //Check Validity
        int counter=0;
        for(int r=0;r<ValuesNo;r++)
        {
            bool res=true;
            for(int c=0;c<VarNo;c++)
            {
                res = res && expTT[r][c];
            }
            res=res&&concTT[r];
            if(res==true)
            {
                counter++;
            }
        }
        if(satisfiable)
        {
            if(counter==critical)
                cout<<"Valid";
            else
                cout<<"Falsifiable";

        }
        else
            cout<<"Falsifiable";


}