#include "calculator_c.h" 
#include <iostream>
#include <stdexcept>
#include <ctype.h>

/**********************************************************************
 *********************************************************************/
///complex calculator

/*********************************************************************/
///functors
calculator_c::functor_c::functor_c(calculation_data *in)
    {
    parent=in;
    }

calculator_c::functor_c::~functor_c()
    {
    }

calculator_c::constant_copy::constant_copy(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::constant_copy::operator() (void)
    {
    parent->stack[parent->stack_position]=parent->constants[parent->copy_stack[parent->copy_stack_position]];
    parent->stack_position++;
    parent->copy_stack_position++;
    }

calculator_c::variable_copy::variable_copy(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::variable_copy::operator() (void)
    {
    parent->stack[parent->stack_position]=(*(parent->variables_value))[parent->copy_stack[parent->copy_stack_position]];
    parent->stack_position++;
    parent->copy_stack_position++;
    }

calculator_c::plus::plus(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::plus::operator() (void)
    {
    parent->stack[parent->stack_position-2]+=parent->stack[parent->stack_position-1];
    parent->stack_position--;
    }

calculator_c::minus::minus(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::minus::operator() (void)
    {
    parent->stack[parent->stack_position-2]-=parent->stack[parent->stack_position-1];
    parent->stack_position--;
    }

calculator_c::unar_plus::unar_plus(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::unar_plus::operator() (void)
    {
    }

calculator_c::unar_minus::unar_minus(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::unar_minus::operator() (void)
    {
    parent->stack[parent->stack_position-1]=-parent->stack[parent->stack_position-1];
    }


calculator_c::mul::mul(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::mul::operator() (void)
    {
    parent->stack[parent->stack_position-2]*=parent->stack[parent->stack_position-1];
    parent->stack_position--;
    }
calculator_c::div::div(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::div::operator() (void)
    {
    parent->stack[parent->stack_position-2]/=parent->stack[parent->stack_position-1];
    parent->stack_position--;
    }

calculator_c::my_exp::my_exp(calculation_data *in):functor_c(in)
    {
    }

void calculator_c::my_exp::operator() (void)
    {
    parent->stack[parent->stack_position-1]=complex<double>(cos(parent->stack[parent->stack_position-1].__im),
    cos(parent->stack[parent->stack_position-1].__im))*exp(parent->stack[parent->stack_position-1].__re);
    }
/*********************************************************************/
///variable_container

calculator_c::variable_container::variable_container()
    {
    mas=new complex<double>[3];
    mas[0]=complex<double>(0,1);
    mas[1]=complex<double>(M_PI,0);
    mas[2]=complex<double>(M_E,0);
    container["i"]=&mas[0];
    container["pi"]=&mas[1];
    container["e"]=&mas[2];
    }

calculator_c::variable_container::~variable_container()
    {
    delete []mas;
    }

complex<double> & calculator_c::variable_container::operator [](std::string id)
    {
    if(id=="i"||id=="pi"||id=="e"||id.find_first_of("()+-*/,")!=std::string::npos)
        {
        throw std::invalid_argument(id+" is invalid variable name"); 
        }
    if(container.find(id)==container.end())
        {
        container[id]=NULL;
        complex<double> *per=new complex<double>[container.size()];
        for(unsigned int j=0;j<container.size()-1;j++)
            {
            per[j]=mas[j];
            }
        for(auto it=container.begin();it!=container.end();++it)
            {
            if(it->second==NULL)
                {
                it->second=&per[container.size()-1];
                continue;
                }
            for(unsigned int j=0;j<container.size()-1;j++)
                {
                if(it->second==&mas[j])
                    {
                    it->second=&per[j];
                    break;
                    }
                }
            }
        delete []mas;
        mas=per;
        }
    return *(container[id]);
    }


///epression
calculator_c::expression::expression(variable_container *in, complex<double> ** var_val)
    {
    variables=in;
    
    copy_stack=NULL;
    stack=NULL;
    constants=NULL;
    variables_value=var_val;
    funcs["exp"]=std::pair<unsigned char,functor* >(1,new my_exp(this));
    }

calculator_c::expression::~expression()
    {
    if(copy_stack!=NULL)delete copy_stack;
    if(stack!=NULL)delete stack;
    if(constants!=NULL)delete constants;
    for(auto it=actions.begin();it!=actions.end();++it)
        {
        delete *it;
        }
    }

void calculator_c::expression::operator =(const std::string &in)
    {
    if(copy_stack!=NULL)delete copy_stack;
    if(stack!=NULL)delete stack;
    if(constants!=NULL)delete constants;
    for(auto it=actions.begin();it!=actions.end();++it)
        {
        delete *it;
        }
    actions.clear();
    ///start compiling
    for_compilation *compil=new for_compilation(&funcs,in);
    compil->init();
    while(compil->up!=NULL)
        {
        compil=compil->up;
        }
    compil->check();
    //compil->out(0,-1);
    compil->make_string();
    std::cout<<std::endl;
    }

complex<double> calculator_c::expression::calculate(void)
    {
    copy_stack_position=0;
    stack_position=0;
    for(auto it=actions.begin();it!=actions.end();++it)
        {
        (*(*it))();
        }
    return stack[0];
    }

/*********************************************************************/
///expression_container
calculator_c::expression_container::expression_container(variable_container *in)
    {
    variables=in;
    mas=NULL;
    size=0;
    }

calculator_c::expression_container::~expression_container()
    {
    if(mas!=NULL)
        {
        for(unsigned int j=0;j<size;j++)
            {
            if(mas[j]!=NULL)delete mas[j];
            }
        delete mas; 
        }
    }

void calculator_c::expression_container::add(const std::string &in)
    {
    ///Because its difficult to copy class expression we have massive of
    /// pointers on class expression 
    expression **per=new expression*[size+1];
    for(unsigned int j=0;j<size;j++)
        per[j]=mas[j];
    per[size]=new expression(variables,&(variables->mas));   
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
        ///If there is only one expression just free memory for expression massive
        delete mas;
        mas=NULL;
        size=0;
        }
    else
        {
        ///If there is more then 1 expression than make new massive of expression pointers
        ///and initalasi it using old one, after that delete old pointer
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
///calculator_c
calculator_c::calculator_c():expressions(&variables)
    {
    }
    
calculator_c::~calculator_c()
    {
    }

/**********************************************************************
 *********************************************************************/    

