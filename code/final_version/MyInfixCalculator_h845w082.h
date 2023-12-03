#ifndef __MYINFIXCALCULATOR_H__
#define __MYINFIXCALCULATOR_H__

#include <algorithm>
#include <string>

#include "MyStack_h845w082.h"
#include "MyVector_h845w082.h"
#include <cmath> // For pow function

std::string invalid;
class MyInfixCalculator{

  public:
    
    MyInfixCalculator()
    {

    }

    ~MyInfixCalculator()
    {
     
    }

    double calculate(const std::string& s)
    {
        // code begins
        MyVector<std::string> infix;
        MyVector<std::string> postfix;
        
        tokenize(s, infix);
        
        infixToPostfix(infix, postfix);
        
        return calPostfix(postfix);
        // code ends
    }

  private:

    // returns operator precedance; the higher the number the higher precedence
    // returns -1 if the operator is invalid
    // does not consider parenthesis
    int operatorPrec(const char c) const
    {
        switch(c)
        {

            case '^':
                return 4;
            case '*':
                return 3;
            case '/':
                return 3;
            case '%':
                return 3;
            case '+':
                return 2;
            case '-':
                return 2;
            default:
                return -1;
        }
    }

    // checks if a character corresponds to a valid parenthesis
    bool isValidParenthesis(const char c) const
    {
        switch(c)
        {
            case '(':
                return true;
            case ')':
                return true;
            default:
                return false;
        }
    }

    // checks if a character corresponds to a valid digit
    bool isDigit(const char c) const
    {
        if(c >= '0' && c <= '9')
            return true;
        return false;
    }

    bool isOperator(const char c) const
    {
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%')
        {
            return true;
        }
        return false;
    }

    // computes binary operation given the two operands and the operator in their string form
    
    double computeBinaryOperation(const std::string& ornd1, const std::string& ornd2, const std::string& opt) const
    {
         
        double o1 = std::stod(ornd1);
        double o2 = std::stod(ornd2);
        switch(opt[0])
        {
            case '+':
                return o1 + o2;
            case '-':
                return o1 - o2;
            case '*':
                return o1 * o2;
            case '/':{
                if (o2 == 0)
                {
                    //std::cout << "Error: Divide by 0" << std::endl;

                    return NULL;
                }
                else{
                    return o1 / o2; 
                }
                //return o1 / o2;
            }
            case '^': //added this case for exponential function
                return std::pow(o1, o2);
            case '%':{
                int num1 = int(o1);
                int num2 = int(o2);
                return std::fmod(num1, num2);
                break;
            }
            default:
                std::cout << "Error: unrecognized operator: " << opt << std::endl;
                return 0.0;
        }
    }


    // tokenizes an infix string s into a set of tokens (operands or operators)

/*
void tokenize(const std::string& s, MyVector<std::string>& tokens) {
    std::string num = "";

    for (size_t i = 0; i < s.length(); ++i) {
        char c = s[i];

        if (isspace(c)) {
            if (!num.empty()) {
                tokens.push_back(num);
                num = "";
            }
            continue;
        }

        if (isDigit(c) || c == '.') {
            num += c;
        } else if (c == '-' && (i == 0 || s[i + 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '^' || s[i - 1] == '%')) {
            num += c;  // Treat '-' as part of a negative number
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num = "";
            }
            if (c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
                tokens.push_back(std::string(1, c));
            } else {
                // Invalid character detected
                //throw std::invalid_argument("Invalid character found: " + std::string(1, c));
               
                invalid += c;

                
            }
        }
    }

    if (!num.empty())
     {
         
        std::string new_num="";
        for (int i = 0; i < num.length(); i++)
        {
        char temp = num[i];
        if (temp != '(' && temp != ')') {
            new_num += temp;
        }
    }
    
    
        
        tokens.push_back(new_num);
    }
}
*/

void tokenize(const std::string& s, MyVector<std::string>& tokens) {
    std::string num = "";

    for (size_t i = 0; i < s.length(); ++i) {
        char c = s[i];

        if (isspace(c)) {
            if (!num.empty()) {
                tokens.push_back(num);
                num = "";
            }
            continue;
        }

        if (isDigit(c) || c == '.') {
            num += c;
        } else if (c == '-') {
            // Check if '-' is part of a negative number or an operator
            if (num.empty() && (i == 0 || s[i - 1] == '(' || s[i - 1] == '+' || s[i - 1] == '-' || s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '^' || s[i - 1] == '%')) {
                num += c;  // Treat '-' as part of a negative number
            } else {
                if (!num.empty()) {
                    tokens.push_back(num);
                    num = "";
                }
                tokens.push_back(std::string(1, c)); // Add '-' as a separate token for subtraction
            }
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num = "";
            }
            if (c == '(' || c == ')' || c == '+' || c == '*' || c == '/' || c == '^' || c == '%') {
                tokens.push_back(std::string(1, c));
            } else {
                // Invalid character detected
                //throw std::invalid_argument("Invalid character found: " + std::string(1, c));
                invalid += c;
            }
        }
    }

     if (!num.empty())
     {
         
        std::string new_num="";
        for (int i = 0; i < num.length(); i++)
        {
        char temp = num[i];
        if (temp != '(' && temp != ')') {
            new_num += temp;
        }
    }
    
    
        
        tokens.push_back(new_num);
    }
}










   
    // converts a set of infix tokens to a set of postfix tokens
    void infixToPostfix(MyVector<std::string>& infix_tokens, MyVector<std::string>& postfix_tokens)
    {
        MyStack <std::string> opStack;

        for(int i = 0; i < infix_tokens.size(); i++)
        {
            if (infix_tokens[i] == "(")
            {
                opStack.push(infix_tokens[i]);
            } 
            else if (infix_tokens[i] == ")")
            {
                while (!opStack.empty() && opStack.top() != "(")
                {
                    postfix_tokens.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.pop();
            } 
            else if(infix_tokens[i] == "+" || infix_tokens[i] == "-" || infix_tokens[i] == "*" || infix_tokens[i] == "/" || infix_tokens[i] == "^" || infix_tokens[i] == "%")
            {
                while(!opStack.empty() && operatorPrec(opStack.top()[0]) >= operatorPrec(infix_tokens[i][0]))
                {
                    postfix_tokens.push_back(opStack.top());
                    opStack.pop();
                }
                opStack.push(infix_tokens[i]);
            }
            else    //Operands
            {
                /*
                if(isDigit(infix_tokens[i][0]))
                {
                    postfix_tokens.push_back(infix_tokens[i]);
                }
                else
                {
                    continue;
                }
                */
                
                
               postfix_tokens.push_back(infix_tokens[i]);
            
            
            }

        }   

        while (!opStack.empty() )   //Adds leftover operators from OpStack
            {
                postfix_tokens.push_back(opStack.top());
                opStack.pop();
            }

    }

    // calculates the final result from postfix tokens
   double calPostfix(const MyVector<std::string>& postfix_tokens) const
    {
        MyStack <std::string> myOperands;
        if (invalid.empty())
        {
            for(int i = 0; i < postfix_tokens.size();i++)
            {
                if(postfix_tokens[i] == "+" || postfix_tokens[i] == "-" || postfix_tokens[i] == "*" || postfix_tokens[i] == "/" || postfix_tokens[i] == "^" || postfix_tokens[i] == "%")        // code ends
                {
                    std::string op2 = myOperands.top();
                    myOperands.pop();
                    std::string op1 = myOperands.top();
                    myOperands.pop();
                
                    myOperands.push(std::to_string(computeBinaryOperation(op1, op2, postfix_tokens[i])));
                } 
                else
                {
                myOperands.push(postfix_tokens[i]);
                }
            
            }
            return (std::stod(myOperands.top()));
        }

        return NULL;
            
        //return (myOperands.top());
    }
};

#endif // __MYINFIXCALCULATOR_H__
