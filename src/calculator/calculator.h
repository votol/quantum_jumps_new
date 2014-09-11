#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "complex.h"
#include <map>
#include <string>


class calculator_c
    {
    private:
        class many_complex_pointer
            {
            
            public:
                many_complex_pointer();
                ~many_complex_pointer();
            };
        class variable_container
            {
                std::map<std::string, many_complex_pointer* > container;
            public:    
                variable_container();
                ~variable_container();
                many_complex_pointer & operator [] (string);
            };
    public:
        variable_container variables;
        
        calculator_c();
        ~calculator_c();
        int add_variable(std::string);
    
    };

#endif
