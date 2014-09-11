#include "calculator.h" 
#include <iostream>
#include <stdexcept>

/**********************************************************************
 *********************************************************************/
//complex calculator

/*********************************************************************/
//functors
calculator_c::functor::functor(expression *in)
    {
    parent=in;
    }

virtual calculator_c::functor::~functor()
    {
    }

calculator_c::constant_copy::constant_copy(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    parent->stack[parent->stack_position]=parent->constants[parent->copy_stack[parent->copy_stack_position]];
    parent->stack_position++;
    parent->copy_stack_position++;
    }

calculator_c::variable_copy::variable_copy(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    }

calculator_c::plus::plus(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    }

calculator_c::minus::minus(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    }

calculator_c::unar_plus::unar_plus(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    }

calculator_c::unar_minus::unar_minus(expression *in)
    {
    parent=in;
    }

void calculator_c::constant_copy::operator (void)
    {
    }

/*********************************************************************/
//variable_container

calculator_c::variable_container::variable_container()
    {
    container["i"]=complex<double>(0,1);
    container["pi"]=complex<double>(M_PI,0);
    }

calculator_c::variable_container::~variable_container()
    {
    }

complex<double> & calculator_c::variable_container::operator [](std::string id)
    {
    if(id=="i"||id=="pi"||id.find_first_of("()+-*/,")!=std::string::npos)
        {
        throw std::invalid_argument(id+" is invalid variable name"); 
        }
    return container[id];
    }

/*********************************************************************/
//epression
calculator_c::expression::expression(variable_container *in)
    {
    variables=in;
    }

calculator_c::expression::~expression()
    {
    }

void calculator_c::expression::operator =(const std::string &in)
    {
    }

complex<double> calculator_c::expression::calculate(void)
    {
    }

/*********************************************************************/
//expression_container
calculator_c::expression_container::expression_container(variable_container *in)
    {
    variables=in;
    mas=NULL;
    size=0;
    }

calculator_c::expression_container::~expression_container()
    {
    if(mas!=NULL)delete mas; 
    }

void calculator_c::expression_container::add(const std::string &in)
    {
    expression **per=new expression*[size+1];
    for(unsigned int j=0;j<size;j++)
        per[j]=mas[j];
    per[size]=new expression(variables);   
    *(per[size])=in;
    if(mas!=NULL)delete mas;
    mas=per;
    size++;
    }

void calculator_c::expression_container::remove(unsigned int num)
    {
    if(num>=size)
        {
        throw std::invalid_argument("Can't remove nonexisting expression");
        }
    delete mas[num];
    if(size==1)
        {
        delete mas;
        mas=NULL;
        size=0;
        }
    else
        {
        expression **per=new expression*[size-1];
        for(unsigned int j=0;j<num;j++)
            {
            per[j]=mas[j];
            }
        for(unsigned int j=num+1;j<size;j++)
            {
            per[j-1]=mas[j];
            }
        if(mas!=NULL)delete mas;
        mas=per;
        size--;
        }
    }

calculator_c::expression & calculator_c::expression_container::operator [](unsigned int num)
    {
    if(num>=size)
        {
        throw std::invalid_argument("Expression doesn't exist");
        }
    return *(mas[num]);
    }
/*********************************************************************/
//calculator_c
calculator_c::calculator_c():expressions(&variables)
    {
    }
    
calculator_c::~calculator_c()
    {
    }

/**********************************************************************
 *********************************************************************/    

