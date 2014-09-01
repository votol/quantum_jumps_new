#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "complex.h"
#include <map>

class calculator_c
    {
    private:
        class variable_container
            {
                complex<double> a;
            public:    
                variable_container();
                ~variable_container();
                double & operator [] (int);
            };
    public:
        variable_container variables;
        
        calculator_c();
        ~calculator_c();
        int add_variable(const char*);
    
    };

#endif
