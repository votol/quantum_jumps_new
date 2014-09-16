#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "calculator.h"


int main(int argc,char **argv)
    {
    calculator_c calc;
    try
        {
        calc.variables["t"]=complex<double>(0,0);
        calc.expressions.add("+5.34e-4+4.56e-12*(8.51-3.14e-1)-8.16*i*(6.45e2+i*5.31e1)");
        //calc.expressions.add("a1*a2*(a3*a4)*a5*a6*(a7*a8)");
        }
    catch(const std::invalid_argument& ia)
        {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    return 0;
    }
