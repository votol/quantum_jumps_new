#ifndef __CALCULATOR_C_H_
#define __CALCULATOR_C_H_


#include "calculator_base.h"




class calculator_c:private calculator_base
    {
    private:
        class calculation_data;
        class expression;
    /*****************************************************************/
    ///functors    
        class functor_c:public functor
            {
            protected:    
                calculation_data *parent;
            public:
                functor_c(calculation_data *);
                virtual ~functor_c();
            };
        class constant_copy:public functor_c
            {
            public:
                constant_copy(calculation_data *);
                ~constant_copy(){};
                void operator() (void);
            };
        class variable_copy:public functor_c
            {
            public:
                variable_copy(calculation_data *);
                ~variable_copy(){};
                void operator() (void);
            };
    
        class plus:public functor_c
            {
            public:
                plus(calculation_data *);
                ~plus(){};
                void operator() (void);
            };
        class minus:public functor_c
            {
            public:
                minus(calculation_data *);
                ~minus(){};
                void operator() (void);
            };
        class unar_plus:public functor_c
            {
            public:
                unar_plus(calculation_data *);
                ~unar_plus(){};
                void operator() (void);
            };
        class unar_minus:public functor_c
            {
            public:
                unar_minus(calculation_data *);
                ~unar_minus(){};
                void operator() (void);
            };
        class mul:public functor_c
            {
            public:
                mul(calculation_data *);
                ~mul(){};
                void operator() (void);
            };
        class div:public functor_c
            {
            public:
                div(calculation_data *);
                ~div(){};
                void operator() (void);
            };
        class my_exp:public functor_c
            {
            public:
                my_exp(calculation_data *);
                ~my_exp(){};
                void operator() (void);
            };
    /*****************************************************************/
    ///variables    
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
    ///expresion
    
    ///special class where data for calculation lies    
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
        
    
    ///main expression class    
        class expression:private calculation_data
            {
            private:
                variable_container *variables;
                
                functions funcs;
                std::list<functor* > actions;
            public:
                expression(variable_container *,complex<double> **);
                ~expression();
                void operator =(const std::string &);
                complex<double> calculate(void);
            };
    /*****************************************************************/
    ///expression_container
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
