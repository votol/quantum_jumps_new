#include "calculator.h" 
#include <iostream>
#include <stdexcept>
#include <ctype.h>


/**********************************************************************
 *********************************************************************/
///complex calculator

/*********************************************************************/
///functors
calculator_c::functor::functor(calculation_data *in)
    {
    parent=in;
    }

calculator_c::functor::~functor()
    {
    }

calculator_c::constant_copy::constant_copy(calculation_data *in):functor(in)
    {
    }

void calculator_c::constant_copy::operator() (void)
    {
    parent->stack[parent->stack_position]=parent->constants[parent->copy_stack[parent->copy_stack_position]];
    parent->stack_position++;
    parent->copy_stack_position++;
    }

calculator_c::variable_copy::variable_copy(calculation_data *in):functor(in)
    {
    }

void calculator_c::variable_copy::operator() (void)
    {
    parent->stack[parent->stack_position]=(*(parent->variables_value))[parent->copy_stack[parent->copy_stack_position]];
    parent->stack_position++;
    parent->copy_stack_position++;
    }

calculator_c::plus::plus(calculation_data *in):functor(in)
    {
    }

void calculator_c::plus::operator() (void)
    {
    parent->stack[parent->stack_position-2]+=parent->stack[parent->stack_position-1];
    parent->stack_position--;
    }

calculator_c::minus::minus(calculation_data *in):functor(in)
    {
    }

void calculator_c::minus::operator() (void)
    {
    parent->stack[parent->stack_position-2]=parent->stack[parent->stack_position-1]-parent->stack[parent->stack_position-2];
    parent->stack_position--;
    }

calculator_c::unar_plus::unar_plus(calculation_data *in):functor(in)
    {
    }

void calculator_c::unar_plus::operator() (void)
    {
    }

calculator_c::unar_minus::unar_minus(calculation_data *in):functor(in)
    {
    }

void calculator_c::unar_minus::operator() (void)
    {
    parent->stack[parent->stack_position-1]=-parent->stack[parent->stack_position-1];
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

/*********************************************************************/
///for_compilation
bool calculator_c::for_compilation::get_name_l(const std::string &stri,std::string &str1, std::string &str2)
    {
    str1.clear();
    str2.clear();
    str1=stri;
    while(1)
        {
        if(str1.length()==0)
            return true;
        if(str1[0]!='+'&&str1[0]!='-' &&str1[0]!='*' &&str1[0]!='/')
            {
            str2.push_back(str1[0]);
            str1.erase(0,1);
            }
        else
            return true;
        }
    }

bool calculator_c::for_compilation::get_name_r(const std::string &stri,std::string &str1, std::string &str2)
    {
    char chr;
    str1.clear();
    str2.clear();
    str1=stri;
    while(1)
        {
        if(str1.length()==0)
            return true;
        chr=str1[str1.length()-1];
        if(chr!='+'&&chr!='-' &&chr!='*' &&chr!='/')
            {
            str2.insert(0,1,chr);
            str1.pop_back();
            }
        else
            return true;
        }
    }

bool calculator_c::for_compilation::get_number_l(const std::string &stri,std::string &str1, std::string &str2)
    {
    char state=0;
    char chr;
    str1.clear();
    str2.clear();
    str2=stri;
    while(1)
        {
        //std::cout<<str1<<"  "<<str2<<std::endl;
        if(str2.length()==0)
            {
            if(stri.length()==0)
                return false;
            else
                return true;
            }
        chr=str2[0];
        switch(state)
            {
            case 0:
                if(isdigit(chr)==0)
                    {
                    if(chr=='.')
                        {
                        if(str1.length()!=0)
                            {
                            state=1;
                            break;
                            }
                        else
                            {
                            str2.clear();
                            return false;
                            }
                        }
                    else if(chr=='e')
                        {
                        if(str1.length()!=0)
                            {
                            state=2;
                            break;
                            }
                        else
                            {
                            str2.clear();
                            return false;
                            }
                        }
                    else if(chr=='+'||chr=='-'||chr=='*'||chr=='/')
                        {
                        if(str1.length()==0)
                            {
                            str2.clear();
                            return false;
                            }
                        return true;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                break;
            case 1:
                if(isdigit(chr)==0)
                    {
                    str1.clear();
                    str2.clear();
                    return false;
                    }
                state=3;
                break;
            case 2:
                if(isdigit(chr)==0)
                    {
                    if(chr=='+'||chr=='-')
                        {
                        state=5;
                        break;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                state=4;
                break;
            case 3:
                if(isdigit(chr)==0)
                    {
                    if(chr=='e')
                        {
                        state=2;
                        break;
                        }
                    else if(chr=='+'||chr=='-'||chr=='*'||chr=='/')
                        {
                        return true;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                break;
            case 4:
                if(isdigit(chr)==0)
                    {
                    if(chr=='+'||chr=='-'||chr=='*'||chr=='/')
                        {
                        return true;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                break;
            case 5:
                if(isdigit(chr)==0)
                    {
                    str1.clear();
                    str2.clear();
                    return false;
                    }
                state=4;    
                break;
            }
        str1.push_back(chr);
        str2.erase(0,1);
        }
    }

bool calculator_c::for_compilation::get_number_r(const std::string &stri,std::string &str1, std::string &str2)
    {
    char state=0;
    char chr;
    str1.clear();
    str2.clear();
    str1=stri;
    while(1)
        {
        //std::cout<<str1<<"  "<<str2<<std::endl;
        if(str1.length()==0)
            {
            if(stri.length()==0)
                return false;
            else
                return true;
            }
        chr=str1[str1.length()-1];
        switch(state)
            {
            case 0:
                if(isdigit(chr)==0)
                    {
                    if(chr=='.')
                        {
                        if(str2.length()!=0)
                            {
                            state=4;
                            break;
                            }
                        else
                            {
                            str1.clear();
                            return false;
                            }
                        }
                    else if(chr=='e')
                        {
                        if(str2.length()!=0)
                            {
                            state=2;
                            break;
                            }
                        else
                            {
                            str1.clear();
                            return false;
                            }
                        }
                    else if(chr=='+'||chr=='-')
                        {
                        if(str2.length()==0)
                            {
                            str1.clear();
                            return false;
                            }
                        if(str1.length()>=2)
                            {
                            if(str1[str1.length()-2]=='e')
                                {
                                state=1;
                                break;
                                }
                            }
                        return true;
                        }
                    else if(chr=='*'||chr=='/')
                        {
                        if(str2.length()==0)
                            {
                            str1.clear();
                            return false;
                            }
                        return true;
                        }
                    else 
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                break;
            case 1:
                state=2;
                break;
            case 2:
                if(isdigit(chr)==0)
                    {
                    str1.clear();
                    str2.clear();
                    return false;
                    }
                state=3;
                break;
            case 3:
                if(isdigit(chr)==0)
                    {
                    if(chr=='.')
                        {
                        state=4;
                        break;
                        }
                    else if(chr=='+'||chr=='-'||chr=='*'||chr=='/')
                        {
                        return true;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }
                break;
            case 4:
                if(isdigit(chr)==0)
                    {
                    str1.clear();
                    str2.clear();
                    return false;
                    }
                state=5;
                break;
            case 5:
                if(isdigit(chr)==0)
                    {
                    if(chr=='+'||chr=='-'||chr=='*'||chr=='/')
                        {
                        return true;
                        }
                    else
                        {
                        str1.clear();
                        str2.clear();
                        return false;
                        }
                    }   
                break;
            }
        str1.pop_back();
        str2.insert(0,1,chr);
        }
    }

calculator_c::for_compilation::for_compilation(expression *in1,const std::string &in2)
    {
    type=-1;
    parent=in1;
    in_str=in2;
    
    left=NULL;
    right=NULL;
    up=NULL;
    }

calculator_c::for_compilation::~for_compilation()
    {
    for(auto it=down.begin();it!=down.end();++it)
        delete *it;
    }

void calculator_c::for_compilation::init(void)
    {
    size_t peri1,peri2,peri3;
    bool left_i=false,right_i=false;
    std::string str1,str2,str3; 
    std::cout<<in_str<<std::endl;
    if(in_str.length()==0)
        throw std::invalid_argument("Wrong expression");
    /*****************************************************************/
    peri1=in_str.find_first_of("(");
    if(peri1!=std::string::npos)
        {
        unsigned char input_number,perc1;
        char chr;
        type=0;
        get_name_r(in_str.substr(0,peri1),str1,name);
        if(name.length()==0)
            {
            input_number=1;
            }
        else
            {
            if(parent->functions.find(name)==parent->functions.end())
                {
                throw std::invalid_argument("Unknown function "+name);
                }
            input_number=parent->functions[name].first;
            }
        if(str1.length()!=0)
            {
            for_compilation *left_per;
            left_per=new for_compilation(parent,str1);
            left_per->right=this;
            left_per->left=left;
            left=left_per;
            left_i=true;
            }
        else if(left!=NULL)
            {
            throw std::invalid_argument("Wrong expression");
            }
            
        down.resize(input_number);
        in_str.erase(0,peri1+1);
        peri1=1;
        for(perc1=0;perc1<input_number;perc1++)
            {
            str1.clear();
            peri2=0;
            while(1)
                {
                if(in_str.length()==0)
                    throw std::invalid_argument("Not enough input arguments ");
                chr=in_str[peri2];
                if(chr=='(')
                    {
                    peri1++;
                    }
                else if(chr==')')
                    {
                    peri1--;
                    }
                else if(chr==','&&peri1==1)
                    {
                    break;
                    }
                if(peri1==0)
                    {
                    if(perc1==input_number-1)
                        break;
                    else
                        throw std::invalid_argument("Not enough input arguments ");
                    }
                str1.push_back(chr);
                peri2++;
                }
            in_str.erase(0,peri2+1);
            down[perc1]=new for_compilation(parent,str1);
            down[perc1]->up=this;
            down[perc1]->init();
            }
        if(in_str.length()!=0)
            {
            for_compilation *right_per;
            right_per=new for_compilation(parent,in_str);
            right_per->left=this;
            right_per->right=right;
            right=right_per;
            right_i=true;
            }
        else if(right!=NULL)
            {
            throw std::invalid_argument("Wrong expression");
            }
        in_str.clear();
        if(left!=NULL&&left_i==true)    
            left->init();
        if(right!=NULL&&right_i==true)
            right->init();
        return;
        }
    /*****************************************************************/
    peri1=in_str.find_first_of("*");
    peri2=in_str.find_first_of("/");
    if(peri1!=std::string::npos||peri2!=std::string::npos)
        {
        type=1;
        if(peri1!=std::string::npos&&peri2==std::string::npos)
            {
            name="*";
            }
        else if(peri1==std::string::npos&&peri2!=std::string::npos)
            {
            name="/";
            peri1=peri2;
            }
        else if(peri1!=std::string::npos&&peri2!=std::string::npos)
            {
            if(peri1>peri2)
                {
                name="/";
                peri1=peri2;
                }
            else
                {
                name="*";
                }
            }
        down.resize(2);
        ///left term
        if(peri1==0)
            {
            
            if(left==NULL)
                throw std::invalid_argument("Wrong expression");
            down[0]=left;
            left=down[0]->left;
            if(left!=NULL)
                left->right=this;
            down[0]->up=this;
            down[0]->left=NULL;
            down[0]->right=NULL;
            }
        else if(get_number_r(in_str.substr(0,peri1),str1,str2)==true)
            {
            down[0]=new for_compilation(parent,"");
            down[0]->type=3;
            down[0]->up=this;
            down[0]->name=str2;
            if(str1.length()!=0)
                {
                for_compilation *left_per;
                left_per=new for_compilation(parent,str1);
                left_per->right=this;
                left_per->left=left;
                left=left_per;
                left_i=true;
                }
            else if(left!=NULL)
                {
                throw std::invalid_argument("Wrong expression");
                }
            }
        else
            {
            get_name_r(in_str.substr(0,peri1),str1,str2);
            down[0]=new for_compilation(parent,"");
            down[0]->type=2;
            down[0]->up=this;
            down[0]->name=str2;
            if(str1.length()!=0)
                {
                for_compilation *left_per;
                left_per=new for_compilation(parent,str1);
                left_per->right=this;
                left_per->left=left;
                left=left_per;
                left_i=true;
                }
            else if(left!=NULL)
                {
                throw std::invalid_argument("Wrong expression");
                }
            }
        in_str.erase(0,peri1+1);
        ///right term
        if(in_str.length()==0)
            {
            if(right==NULL)
                throw std::invalid_argument("Wrong expression");
            down[1]=right;
            right=down[1]->right;
            if(right!=NULL)    
                right->left=this;
            down[1]->up=this;
            down[1]->left=NULL;
            down[1]->right=NULL;
            }
        else if(get_number_l(in_str,str1,str2)==true)
            {
            down[1]=new for_compilation(parent,"");
            down[1]->type=3;
            down[1]->up=this;
            down[1]->name=str1;
            if(str2.length()!=0)
                {
                for_compilation *right_per;
                right_per=new for_compilation(parent,str2);
                right_per->left=this;
                right_per->right=right;
                right=right_per;
                right_i=true;
                }
            else if(right!=NULL)
                {
                throw std::invalid_argument("Wrong expressio");
                }
            }
        else
            {
            get_name_l(in_str.substr(0,peri1),str1,str2);
            down[1]=new for_compilation(parent,"");
            down[1]->type=2;
            down[1]->up=this;
            down[1]->name=str1;
            if(str2.length()!=0)
                {
                for_compilation *right_per;
                right_per=new for_compilation(parent,str2);
                right_per->left=this;
                right_per->right=right;
                right=right_per;
                right_i=true;
                }
            else if(right!=NULL)
                {
                throw std::invalid_argument("Wrong expression");
                }
            }
        
        in_str.clear();
        
            
        if(left!=NULL/*&&left_i==true*/)    
            left->init();
        if(right!=NULL/*&&right_i==true*/)
            right->init();
        return;
        }
    }
///epression
calculator_c::expression::expression(variable_container *in, complex<double> ** var_val)
    {
    variables=in;
    
    copy_stack=NULL;
    stack=NULL;
    constants=NULL;
    variables_value=var_val;
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
    for_compilation *compil=new for_compilation(this,in);
    compil->init();
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

