#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "calculator_c.h"


int main(int argc,char **argv)
    {
    calculator_c calc;
    try
        {
        calc.variables["t"]=complex<double>(0,0);
        //calc.expressions.add("-1.35e-2*a1+a2*1.25e+1*exp(8.31+i*0.65e-1)*i+e*26e+2/exp(i+3.45e-1)-a3");
        calc.expressions.add("-17e-1+i*exp(45e+1)");
        }
    catch(const std::invalid_argument& ia)
        {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    return 0;
    }
