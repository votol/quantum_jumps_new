#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "complex.h"
#include <map>
#include <list>
#include <vector>
#include <string>



class calculator_c
    {
    private:
        class calculation_data;
        class expression;
    /*****************************************************************/
    //functors    
        class functor
            {
            protected:    
                calculation_data *parent;
            public:
                functor(calculation_data *);
                virtual ~functor();
                virtual void operator() (void)=0;
            };
    
    
        class constant_copy:public functor
            {
            public:
                constant_copy(calculation_data *);
                ~constant_copy(){};
                void operator() (void);
            };
        class variable_copy:public functor
            {
            public:
                variable_copy(calculation_data *);
                ~variable_copy(){};
                void operator() (void);
            };
    
        class plus:public functor
            {
            public:
                plus(calculation_data *);
                ~plus(){};
                void operator() (void);
            };
        class minus:public functor
            {
            public:
                minus(calculation_data *);
                ~minus(){};
                void operator() (void);
            };
        class unar_plus:public functor
            {
            public:
                unar_plus(calculation_data *);
                ~unar_plus(){};
                void operator() (void);
            };
        class unar_minus:public functor
            {
            public:
                unar_minus(calculation_data *);
                ~unar_minus(){};
                void operator() (void);
            };
    /*****************************************************************/
    //variables    
        class variable_container
            {
            private:
                friend calculator_c;
                friend expression;
                complex<double > * mas;
                std::map<std::string, complex<double> * > container;
            public:    
                variable_container();
                ~variable_container();
                complex<double> & operator [] (std::string);
            };
    /*****************************************************************/
    //expresion
    
    //special class where data for calculation lies    
        class calculation_data
            {
            public:
                unsigned int *copy_stack;
                complex<double> *stack;
                complex<double> *constants;
                complex<double> **variables_value;
                
                
                unsigned int copy_stack_position;
                unsigned int stack_position;
                
                
                calculation_data(){};
                ~calculation_data(){};
            };
        
    //compilation class
        class for_compilation
            {
            private:
                bool get_name_l(const std::string &,std::string &, std::string &);
                bool get_name_r(const std::string &,std::string &, std::string &);
                bool get_number_l(const std::string &,std::string &, std::string &);
                bool get_number_r(const std::string &,std::string &, std::string &);
            public:
                ///type values: 0 - functions and brakets
                ///             1 - +-*/
                ///             2 - variables
                ///             3 - constant
                char type;
                std::string name;
                std::string in_str;
                
                expression * parent;
                
                for_compilation *left;
                for_compilation *right;
                for_compilation *up;
                std::vector<for_compilation *> down;
                
                
                for_compilation(expression *,const std::string &);
                ~for_compilation();
                void init(void);
            };
    //main expression class    
        class expression:private calculation_data
            {
            private:
                friend for_compilation;
                variable_container *variables;
                
                std::map<std::string,std::pair<unsigned char,functor* > > functions;
                std::list<functor* > actions;
            public:
                expression(variable_container *,complex<double> **);
                ~expression();
                void operator =(const std::string &);
                complex<double> calculate(void);
            };
    /*****************************************************************/
    //expression_container
        class expression_container
            {
            private:
                variable_container *variables;
                expression **mas;
                unsigned int size;
            public:
                expression_container(variable_container *);
                ~expression_container();
                void add(const std::string &);
                void remove(unsigned int);
                expression & operator [](unsigned int);
            };
    /*****************************************************************/
    public:
        variable_container variables;
        expression_container expressions;
        calculator_c();
        ~calculator_c();
    };

#endif
