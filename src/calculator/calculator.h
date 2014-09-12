#ifndef __CALCULATOR_H_
#define __CALCULATOR_H_

#include "complex.h"
#include <map>
#include <list>
#include <string>



class calculator_c
    {
    private:
        class expression;
    /*****************************************************************/
    //functors    
        class functor
            {
            protected:    
                expression *parent;
            public:
                functor(expression *);
                virtual ~functor();
                virtual void operator() (void)=0;
            };
    
    
        class constant_copy:public functor
            {
            public:
                constant_copy(expression *);
                ~constant_copy(){};
                void operator() (void);
            };
        class variable_copy:public functor
            {
            public:
                variable_copy(expression *);
                ~variable_copy(){};
                void operator() (void);
            };
    
        class plus:public functor
            {
            public:
                plus(expression *);
                ~plus(){};
                void operator() (void);
            };
        class minus:public functor
            {
            public:
                minus(expression *);
                ~minus(){};
                void operator() (void);
            };
        class unar_plus:public functor
            {
            public:
                unar_plus(expression *);
                ~unar_plus(){};
                void operator() (void);
            };
        class unar_minus:public functor
            {
            public:
                unar_minus(expression *);
                ~unar_minus(){};
                void operator() (void);
            };
    /*****************************************************************/
    //variables    
        class variable_container
            {
            private:
                friend calculator_c;
                complex<double > * mas;
                std::map<std::string, complex<double> * > container;
            public:    
                variable_container();
                ~variable_container();
                complex<double> & operator [] (std::string);
            };
    /*****************************************************************/
    //expresion
        class expression
            {
            private:
                variable_container *variables;
                
                //for_calculation
                unsigned int *copy_stack;
                complex<double> *stack;
                complex<double> *constants;
                
                unsigned int copy_stack_position;
                unsigned int stack_position;
                std::list<functor* > actions;
                //for_compiling
            public:
                
                
                
                expression(variable_container *);
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
