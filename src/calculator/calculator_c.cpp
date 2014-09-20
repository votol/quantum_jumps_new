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
    //std::cout<<parent->copy_stack[parent->copy_stack_position]<<":"<<parent->stack_position<<std::endl;
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
    sin(parent->stack[parent->stack_position-1].__im))*exp(parent->stack[parent->stack_position-1].__re);
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
void calculator_c::expression::linearization(for_compilation *in)
    {
    switch(in->type)
        {
        case 0:
            if(in->name.length()==0)
                {
                for(auto it0=in->down.begin();it0!=in->down.end();++it0)
                    {
                    linearization(*it0);
                    }
                }
            else
                {
                for(auto it0=in->down.begin();it0!=in->down.end();++it0)
                    {
                    linearization(*it0);
                    }
                stack_num-=funcs[in->name].first-1;
                actions.push_back(funcs[in->name].second);
                }
            break;
        case 1:
            for(auto it1=in->down.begin();it1!=in->down.end();++it1)
                {
                linearization(*it1);
                }
            stack_num-=funcs[in->name].first-1;
            actions.push_back(funcs[in->name].second);
            break;
        case 2:
            {
            auto it2=variables->container.find(in->name);
            if(it2==variables->container.end())
                throw std::invalid_argument("Unknown variable "+in->name);
            else
                {
                copy_stack_list.push_back( ((unsigned long)(it2->second)-(unsigned long)(*variables_value))/sizeof(*(*variables_value)));
                actions.push_back(funcs["v-"].second);
                stack_num++;
                if(stack_num>stack_max)
                    stack_max=stack_num;
                }
            break;
            }
        case 3:
            constants_list.push_back(complex<double>(std::stod(in->name),0));
            actions.push_back(funcs["c-"].second);
            copy_stack_list.push_back(constant_num);
            constant_num++;
            stack_num++;
            if(stack_num>stack_max)
                stack_max=stack_num;
            break;
        }
    }

void calculator_c::expression::fun_per(void)
    {
    
    }

calculator_c::expression::expression(variable_container *in)
    {
    variables=in;
    
    copy_stack=NULL;
    stack=NULL;
    constants=NULL;
    variables_value=&(in->mas);
    funcs["exp"]=std::pair<unsigned char,functor* >(1,new my_exp(this));
    funcs["*"]=std::pair<unsigned char,functor* >(2,new mul(this));
    funcs["/"]=std::pair<unsigned char,functor* >(2,new div(this));
    funcs["+"]=std::pair<unsigned char,functor* >(2,new plus(this));
    funcs["-"]=std::pair<unsigned char,functor* >(2,new minus(this));
    funcs["+!"]=std::pair<unsigned char,functor* >(1,new unar_plus(this));
    funcs["-!"]=std::pair<unsigned char,functor* >(1,new unar_minus(this));
    funcs["v-"]=std::pair<unsigned char,functor* >(1,new variable_copy(this));
    funcs["c-"]=std::pair<unsigned char,functor* >(1,new constant_copy(this));
    
    constant_num=0;
    stack_num=0;
    stack_max=0;
    }

calculator_c::expression::~expression()
    {
    if(copy_stack!=NULL)delete copy_stack;
    if(stack!=NULL)delete stack;
    if(constants!=NULL)delete constants;
    actions.clear();
    for(auto it=funcs.begin();it!=funcs.end();++it)
        {
        delete it->second.second;
        }
    }

void calculator_c::expression::operator =(const std::string &in)
    {
    if(copy_stack!=NULL)delete copy_stack;
    if(stack!=NULL)delete stack;
    if(constants!=NULL)delete constants;
    actions.clear();
    ///start compiling
    for_compilation *compil=new for_compilation(&funcs,in);
    compil->init();
    while(compil->up!=NULL)
        {
        compil=compil->up;
        }
    compil->check();
    
    linearization(compil);
    
    copy_stack=new unsigned int[copy_stack_list.size()];
    stack=new complex<double>[stack_max];
    constants=new complex<double>[constant_num];
    unsigned int peri=0;
    for(auto it=copy_stack_list.begin();it!=copy_stack_list.end();++it)
        {
        copy_stack[peri]=*it;
        peri++;
        }
    peri=0;
    for(auto it=constants_list.begin();it!=constants_list.end();++it)
        {
        constants[peri]=*it;
        peri++;
        }
    constant_num=0;
    stack_num=0;
    stack_max=0;
    constants_list.clear();
    copy_stack_list.clear();
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

