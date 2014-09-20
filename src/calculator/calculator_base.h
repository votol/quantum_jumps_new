#ifndef __CALCULATOR_BASE_H_
#define __CALCULATOR_BASE_H_

#include "complex.h"
#include <map>
#include <list>
#include <vector>
#include <string>

class calculator_base
    {
    public:
    /*****************************************************************/
    ///functors    
        class functor
            {
            public:
                functor(){};
                virtual ~functor(){};
                virtual void operator() (void)=0;
            };
    /*****************************************************************/
        typedef std::map<std::string,std::pair<unsigned char,functor* > > functions;
    ///compilation class
        class for_compilation
            {
            private:
                size_t peri1,peri2;
                std::string str1,str2,str3; 
                for_compilation *compil_per;
                char sm;
                bool get_name_l(const std::string &,std::string &, std::string &);
                bool get_name_r(const std::string &,std::string &, std::string &);
                bool get_number_l(const std::string &,std::string &, std::string &);
                bool get_number_r(const std::string &,std::string &, std::string &);
                void change_down(for_compilation*,for_compilation*);
                void arifm_right(void);
                void plus_minus(void);
                void mult_div(void);
                void brackets(void);
            public:
                int num;
                ///type values: 0 - functions and brakets
                ///             1 - +-*/
                ///             2 - variables
                ///             3 - constant
                char type;
                std::string name;
                std::string in_str;
                
                functions * funcs;
                
                for_compilation *left;
                for_compilation *right;
                for_compilation *up;
                std::vector<for_compilation *> down;
                
                
                for_compilation(functions *,const std::string &);
                ~for_compilation();
                void init(void);
                void check(void);
                
                
                void out(int,int);
                void make_string();
            };
        calculator_base(){};
        ~calculator_base(){};
    };

#endif
