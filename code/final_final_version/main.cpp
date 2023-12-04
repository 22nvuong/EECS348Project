#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>

#include "MyInfixCalculator_h845w082.h"
#include "MyLinkedList_h845w082.h"

int main() {
    //MyLinkedList<string> list;
    std::string expression = "1";
    MyInfixCalculator calculator;


    while (expression != "0")
    {
    std::cout << "Enter expression to evaluate (enter '0' to exit): ";
    std::getline(std::cin, expression);
    double result = calculator.calculate(expression);
    //std::string result = calculator.calculate(expression);
   
        if (result == NULL)
        {
            if (expression == "0")
            {
                std::cout << "Goodbye!" << std::endl;
            }
            else
            {
                std::cout << "Error, Invalid Expression" << std::endl;
                result = '1';
            }
       
        }
        else
        {
            std::cout << "Result: " << result << std::endl; 
        }


    
  
    }

    return 0;
}
