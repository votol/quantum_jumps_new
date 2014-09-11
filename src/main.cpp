#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "calculator.h"


int main(int argc,char **argv)
    {
    calculator_c calc;
    try
        {
        calc.variables["e"]=complex<double>(0,0);
        calc.expressions.add("asdgaegaqdg");
        calc.expressions.add("asdgaega");
        calc.expressions.add("asdgaegaqdgdwwf");
        calc.expressions[3]="5+sin(3)";
        calc.expressions.remove(2);
        calc.expressions.remove(0);
        }
    catch(const std::invalid_argument& ia)
        {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    return 0;
    }
