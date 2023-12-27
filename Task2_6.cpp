#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <cctype>

/*This is Task 2- Team 6
--------------------------------
In my code i handle taking an input of a logical expression using '&' for AND, '|' for OR, and '!' for NOT.

Our original circuit was: (!(A |!B) & (A & B) ) & C ,
but because it is a contradiction that will always return false (unsatisfiable),
our code handles this by changing the first AND gate with an OR gate and try again checking satisfiability

here is a test case you can also run:
expression1: (!(A |!B) & (A & B) ) | C
expression 2: C
these have to be equivilant and satisfiable showing the input values that makes both expressions satisfiable

-The user is asked to enter 2 expressions and the variables may be "lower/uppercase"... both are handled to be "Generic"
-Also the user can input "any number of variables not just 3", so as the function is "Generic"
-The user can also "use any letter".. it is not a must to start with a, b, c... they may be x, y and z and everything will still be output
and managed accordingly.. they dont have to be consecutive too...
TRYING MY BEST TO MAKE THE PROGRAM AS GENERIC AS POSSIBLE ...
AND HERE COMES THE CODE...
*/



// Function to evaluate a logical expression
bool evaluateExpression(const std::string& expr, const std::unordered_map<char, bool>& inputs) {
    bool result = false;
    bool negation = false;
    bool andOperation = false;

    // Iterating through each character in the expression
    for (char c : expr) {
        if (std::isspace(c)) {
            continue; // Skip spaces
        }
        if (c == '!') {
            negation = true; // Set negation flag for NOT operation
        }
        else if (c == '&') {
            andOperation = true; // Set AND flag
        }
        else if (c == '|') {
            andOperation = false; // Reset AND flag for OR operation
        }
        else if (std::isalpha(c)) {
            char variable = std::toupper(c);  // Convert variable to uppercase
            bool value = inputs.at(variable); // Get value from inputs based on variable

            // Evaluate based on the operation and flags
            if (negation) {
                result = result && !value; // Apply negation if '!'
                negation = false; // Reset negation flag after usage
            }
            else if (andOperation) {
                result = result && value; // Apply '&' (AND) operation
            }
            else {
                result = result || value; // Apply '|' (OR) operation
            }
        }
    }

    return result;
}

// Function to replace the first occurrence of a gate in the expression
void replaceFirstGate(std::string& expression, char gateToReplace, char replacementGate) {
    size_t pos = expression.find(gateToReplace);
    if (pos != std::string::npos) {
        expression[pos] = replacementGate;
    }
}

// Function to check if the expression is satisfiable
bool isSatisfiable(const std::string& expr, const std::unordered_map<char, bool>& inputs) {
    // Check if there is at least one combination that results in true
    for (int i = 0; i < (1 << inputs.size()); ++i) {
        int mask = 1;
        std::unordered_map<char, bool> inputValues;
        for (const auto& input : inputs) {
            inputValues[input.first] = i & mask;
            mask <<= 1;
        }

        if (evaluateExpression(expr, inputValues)) {
            return true;  // At least one output is equal to one -> thus the expression will be satisfiable
        }
    }
    return false;  // All outputs are equal to zero -> thus the expression will be unsatisfiable
}

// Function to generate the truth table and check equivalence of expressions
void generateTruthTable(const std::string& expr1, const std::string& expr2, int recursionLimit = 10) {
    std::cout << "Truth Table:\n";

    // Create a map to store input variables
    std::unordered_map<char, bool> inputVariables;

    // Identify unique input variables from the expressions
    for (char c : expr1 + expr2) {
        if (std::isalpha(c) && inputVariables.find(std::toupper(c)) == inputVariables.end()) {
            inputVariables[std::toupper(c)] = false;
        }
    }

    // Display input variable headers
    for (const auto& input : inputVariables) {
        std::cout << input.first << "\t";
    }
    std::cout << "\tExpr1\t\tExpr2\n";

    int numInputs = inputVariables.size();
    int totalCombinations = 1 << numInputs;

    bool satisfiable1 = false;
    bool satisfiable2 = false;


    // Generate truth table
    for (int i = 0; i < totalCombinations; ++i) {
        int mask = 1;
        for (auto& input : inputVariables) {
            input.second = i & mask;
            mask <<= 1;
        }

        // Display input combinations
        for (const auto& input : inputVariables) {
            std::cout << input.second << "\t";
        }

        // Evaluate expressions and display results
        bool result1 = evaluateExpression(expr1, inputVariables);
        bool result2 = evaluateExpression(expr2, inputVariables);

        std::cout << "\t" << result1 << "\t\t" << result2 << "\n";

        // Check if expression 1 is satisfiable
        if (!satisfiable1 && result1) {
            satisfiable1 = true;
        }

        // Check if expression 2 is satisfiable
        if (!satisfiable2 && result2) {
            satisfiable2 = true;
        }
    }
   

    // Display whether expressions are satisfiable or not
    if (!satisfiable1 && !satisfiable2) { //modify both expressions
        std::cout << "Expr1 is unsatisfiable. Modifying...\n";

        // Modify the first expression to make it satisfiable
        std::string modifiedExpr1 = expr1;
        replaceFirstGate(modifiedExpr1, '&', '|');  // Replace the first AND with OR

        // Display modified expression
        std::cout << "Modified Expression 1 to: " << modifiedExpr1 << "\n";

        // Display new truth table for modified expression
        std::cout << "Truth Table for Modified Expression 1:\n";
        generateTruthTable(modifiedExpr1, expr2);


        //------------modify second expression
        std::cout << "Expr2 is unsatisfiable. Modifying...\n";

        // Modify the second expression to make it satisfiable
        std::string modifiedExpr2 = expr2;
        replaceFirstGate(modifiedExpr2, '&', '|');  // Replace the first AND with OR

        // Display modified expression
        std::cout << "Modified Expression 2 to: " << modifiedExpr2 << "\n";

        // Display new truth table for modified expression
        std::cout << "Truth Table for Modified Expression 1:\n";
        generateTruthTable(expr1, modifiedExpr2);


    }

    else {
        if(satisfiable1 && satisfiable2){
            // Check if expressions are equivalent
            bool equivalent = true;
            for (int i = 0; i < totalCombinations; ++i) {
                int mask = 1;
                for (auto& input : inputVariables) {
                    input.second = i & mask;
                    mask <<= 1;
                }

                bool result1 = evaluateExpression(expr1, inputVariables);
                bool result2 = evaluateExpression(expr2, inputVariables);

                if (result1 != result2) {
                    equivalent = false;
                    break;
                }
            }

            if (equivalent) {
                std::cout << "The expressions are equivalent.\n";
            }
            else {
                std::cout << "The expressions are not equivalent.\n";
            }
            std::cout << "\nValues of inputs making both expressions satisfiable:\n";
            
            bool satisfyingInputFound = false;
            std::cout << "Both expressions are satisfiable.\n";
            // Check the satisfying input values for both expressions

            for (int i = 0; i < totalCombinations; ++i) {
                int mask = 1;
                for (auto& input : inputVariables) {
                    input.second = i & mask;
                    mask <<= 1;
                }

                bool result1 = evaluateExpression(expr1, inputVariables);
                bool result2 = evaluateExpression(expr2, inputVariables);

                if (result1 && result2) {
                    satisfyingInputFound = true;
                    std::cout << "Inputs: ";
                    for (const auto& input : inputVariables) {
                        std::cout << input.first << "=" << input.second << " ";
                    }
                    std::cout << "\n";
                }
            }
            // Stop the function as both expressions are satisfiable
            return;
    }
        if (satisfiable1) {
            std::cout << "Expr1 is satisfiable.\n";
            
        }
        else if(!satisfiable1) {
            std::cout << "Expr1 is unsatisfiable. Modifying...\n";

            // Modify the first expression to make it satisfiable
            std::string modifiedExpr1 = expr1;
            replaceFirstGate(modifiedExpr1, '&', '|');  // Replace the first AND with OR

            // Display modified expression
            std::cout << "Modified Expression 1 to: " << modifiedExpr1 << "\n";

            // Display new truth table for modified expression
            std::cout << "Truth Table for Modified Expression 1:\n";
            generateTruthTable(modifiedExpr1, expr2);

            return;  // End the function to avoid duplicate messages
        }

        if (satisfiable2) {
            std::cout << "Expr2 is satisfiable.\n";
            return;
        }
        else if (!satisfiable2) {
            std::cout << "Expr2 is unsatisfiable. Modifying...\n";

            // Modify the second expression to make it satisfiable
            std::string modifiedExpr2 = expr2;
            replaceFirstGate(modifiedExpr2, '&', '|');  // Replace the first AND with OR

            // Display modified expression
            std::cout << "Modified Expression 2 to: " << modifiedExpr2 << "\n";

            // Display new truth table for modified expression
            std::cout << "Truth Table for Modified Expression 1:\n";
            generateTruthTable(expr1, modifiedExpr2);

            return;  // End the function to avoid duplicate messages

        }
    }
    // Check if expressions are equivalent
    bool equivalent = true;
    for (int i = 0; i < totalCombinations; ++i) {
        int mask = 1;
        for (auto& input : inputVariables) {
            input.second = i & mask;
            mask <<= 1;
        }

        bool result1 = evaluateExpression(expr1, inputVariables);
        bool result2 = evaluateExpression(expr2, inputVariables);

        if (result1 != result2) {
            equivalent = false;
            break;
        }
    }

    if (equivalent) {
        std::cout << "The expressions are equivalent.\n";
    }
    else {
        std::cout << "The expressions are not equivalent.\n";
    }
    std::cout << "\nValues of inputs making both expressions satisfiable:\n";
    std::cout << "Inputs for both expressions:\n";

    bool satisfyingInputFound = false;

    // Check the satisfying input values for both expressions
    for (int i = 0; i < totalCombinations; ++i) {
        int mask = 1;
        for (auto& input : inputVariables) {
            input.second = i & mask;
            mask <<= 1;
        }

        bool result1 = evaluateExpression(expr1, inputVariables);
        bool result2 = evaluateExpression(expr2, inputVariables);

        if (result1 && result2) {
            satisfyingInputFound = true;
            std::cout << "Inputs: ";
            for (const auto& input : inputVariables) {
                std::cout << input.first << "=" << input.second << " ";
            }
            std::cout << "\n";
        }
    }
    if (!satisfyingInputFound) {
        std::cout << "No input values found that satisfy both expressions.\n";
    }
}

int main() {

    std::cout << "Please enter your logical expressions using '&' for AND, '|' for OR, and '!' for NOT... \n";
    std::string expression1, expression2;

    std::cout << "Enter the first logical expression: ";
    std::getline(std::cin, expression1);

    std::cout << "Enter the second logical expression: ";
    std::getline(std::cin, expression2);

    generateTruthTable(expression1, expression2);

    return 0;
}
//-------------------------------------this is the code on github we did




