#include "calculator_base.h"
#include <iostream>
#include <stdexcept>
#include <ctype.h>

/**********************************************************************
 *********************************************************************/
///base calculator

/*********************************************************************/
///for_compilation
bool calculator_base::for_compilation::get_name_l(const std::string &stri,std::string &str1, std::string &str2)
    {
    str1.clear();
    str2.clear();
    str2=stri;
    while(1)
        {
        if(str2.length()==0)
            return true;
        if(str2[0]!='+'&&str2[0]!='-' &&str2[0]!='*' &&str2[0]!='/')
            {
            str1.push_back(str2[0]);
            str2.erase(0,1);
            }
        else
            return true;
        }
    }

bool calculator_base::for_compilation::get_name_r(const std::string &stri,std::string &str1, std::string &str2)
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

bool calculator_base::for_compilation::get_number_l(const std::string &stri,std::string &str1, std::string &str2)
    {
    char state=0;
    char chr;
    str1.clear();
    str2.clear();
    str2=stri;
    while(1)
        {
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

bool calculator_base::for_compilation::get_number_r(const std::string &stri,std::string &str1, std::string &str2)
    {
    char state=0;
    char chr;
    str1.clear();
    str2.clear();
    str1=stri;
    while(1)
        {
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


void calculator_base::for_compilation::change_down(for_compilation* in1,for_compilation* in2)
    {
    for(auto it=down.begin();it!=down.end();++it)
        {
        if(*it==in1)
            {
            *it=in2;
            break;
            }
        }
    }
void calculator_base::for_compilation::arifm_right(void)
    {
    if(in_str.length()==0)
        {
        if(right==NULL)
            throw std::invalid_argument("Wrong expression");
        down[1-sm]=right;
        right=down[1-sm]->right;
        if(right!=NULL)    
            right->left=this;
        if(up==NULL)    
            {
            up=down[1-sm]->up;
            if(up!=NULL)
                up->change_down(down[1-sm],this);
            }
        down[1-sm]->up=this;
        down[1-sm]->left=NULL;
        down[1-sm]->right=NULL;
        }
    else if(get_number_l(in_str,str1,str2)==true)
        {
        down[1-sm]=new for_compilation(funcs,"");
        down[1-sm]->type=3;
        down[1-sm]->up=this;
        down[1-sm]->name=str1;
        if(str2.length()!=0)
            {
            compil_per=new for_compilation(funcs,str2);
            compil_per->left=this;
            compil_per->right=right;
            right=compil_per;
            }
        else if(right!=NULL)
            {
            throw std::invalid_argument("Wrong expression");
            }
        in_str.clear();
        }
    else
        {
        get_name_l(in_str,str1,str2);
        down[1-sm]=new for_compilation(funcs,"");
        down[1-sm]->type=2;
        down[1-sm]->up=this;
        down[1-sm]->name=str1;
        if(str2.length()!=0)
            {
            compil_per=new for_compilation(funcs,str2);
            compil_per->left=this;
            compil_per->right=right;
            right=compil_per;
            }
        else if(right!=NULL)
            {
            throw std::invalid_argument("Wrong expression");
            }
        in_str.clear();
        }
    }


void calculator_base::for_compilation::plus_minus(void)
    {
    if(in_str.length()==0&&type==-1)
        throw std::invalid_argument("Wrong expression");
    peri1=in_str.find_first_of("+",0);
    peri2=in_str.find_first_of("-",0);
    while(1)    
        {
        if(peri1!=std::string::npos||peri2!=std::string::npos)    
            {
            if(peri1!=std::string::npos&&peri2==std::string::npos)
                {
                str3="+";
                }
            else if(peri1==std::string::npos&&peri2!=std::string::npos)
                {
                str3="-";
                peri1=peri2;
                }
            else
                {
                if(peri1>peri2)
                    {
                    peri1=peri2;
                    str3="-";
                    }
                else
                    {
                    str3="+";
                    }
                }
            if(peri1>=2)
                {
                if(in_str[peri1-1]=='e'&&isdigit(in_str[peri1-2])!=0)
                    {
                    peri1=in_str.find_first_of("+",peri1+1);
                    peri2=in_str.find_first_of("-",peri1+1);
                    continue;
                    }
                }
            }
        break;
        }
    if(peri1!=std::string::npos)    
        {
        sm=0;
        if(peri1==0)
            {
            type=1;
            if(left==NULL)
                {
                name=str3+"!";
                down.resize(1);
                sm=1;
                }
            else
                {
                name=str3;
                down.resize(2);
                down[0]=left;
                left=down[0]->left;
                if(left!=NULL)
                    left->right=this;
                if(up==NULL)    
                    {
                    up=down[0]->up;
                    if(up!=NULL)
                        up->change_down(down[0],this);
                    }
                down[0]->up=this;
                down[0]->left=NULL;
                down[0]->right=NULL;
                }
            in_str.erase(0,peri1+1);
            arifm_right();
            }
        else if(get_number_r(in_str.substr(0,peri1),str1,str2)==true)
            {
            if(str1.length()!=0)
                {
                compil_per=new for_compilation(funcs,str2+in_str.substr(peri1,in_str.length()));
                compil_per->left=this;
                compil_per->right=right;
                right=compil_per;
                in_str=str1;
                }
            else
                {
                name=str3;
                type=1;
                down.resize(2);
                down[0]=new for_compilation(funcs,"");
                down[0]->type=3;
                down[0]->up=this;
                down[0]->name=str2;
                in_str.erase(0,peri1+1);
                arifm_right();
                }
            }
        else
            {
            get_name_r(in_str.substr(0,peri1),str1,str2);
            if(str1.length()!=0)
                {
                compil_per=new for_compilation(funcs,str2+in_str.substr(peri1,in_str.length()));
                compil_per->left=this;
                compil_per->right=right;
                right=compil_per;
                in_str=str1;
                }
            else
                {
                name=str3;
                type=1;
                down.resize(2);
                down[0]=new for_compilation(funcs,"");
                down[0]->type=2;
                down[0]->up=this;
                down[0]->name=str2;
                in_str.erase(0,peri1+1);
                arifm_right();
                }
            }
        }
    if(right!=NULL)
        right->plus_minus();
    }

void calculator_base::for_compilation::mult_div(void)
    {
    if(in_str.length()==0&&type==-1)
        throw std::invalid_argument("Wrong expression");
    peri1=in_str.find_first_of("*");
    peri2=in_str.find_first_of("/");
    if(peri1!=std::string::npos||peri2!=std::string::npos)
        {
        if(peri1!=std::string::npos&&peri2==std::string::npos)
            {
            str3="*";
            }
        else if(peri1==std::string::npos&&peri2!=std::string::npos)
            {
            str3="/";
            peri1=peri2;
            }
        else if(peri1!=std::string::npos&&peri2!=std::string::npos)
            {
            if(peri1>peri2)
                {
                str3="/";
                peri1=peri2;
                }
            else
                {
                str3="*";
                }
            }
        ///left term
        sm=0;
        if(peri1==0)
            {
            name=str3;
            type=1;
            down.resize(2);
            if(left==NULL)
                throw std::invalid_argument("Wrong expression");
            down[0]=left;
            left=down[0]->left;
            if(left!=NULL)
                left->right=this;
            if(up==NULL)    
                {
                up=down[0]->up;
                if(up!=NULL)
                    up->change_down(down[0],this);
                }
            down[0]->up=this;
            down[0]->left=NULL;
            down[0]->right=NULL;
            in_str.erase(0,peri1+1);
            arifm_right();
            }
        else if(get_number_r(in_str.substr(0,peri1),str1,str2)==true)
            {
            if(str1.length()!=0)
                {
                compil_per=new for_compilation(funcs,str2+in_str.substr(peri1,in_str.length()));
                compil_per->left=this;
                compil_per->right=right;
                right=compil_per;
                in_str=str1;
                }
            else
                {
                name=str3;
                type=1;
                down.resize(2);
                down[0]=new for_compilation(funcs,"");
                down[0]->type=3;
                down[0]->up=this;
                down[0]->name=str2;
                in_str.erase(0,peri1+1);
                arifm_right();
                }
            }
        else
            {
            get_name_r(in_str.substr(0,peri1),str1,str2);
            if(str1.length()!=0)
                {
                compil_per=new for_compilation(funcs,str2+in_str.substr(peri1,in_str.length()));
                compil_per->left=this;
                compil_per->right=right;
                right=compil_per;
                in_str=str1;
                }
            else
                {
                name=str3;
                type=1;
                down.resize(2);
                down[0]=new for_compilation(funcs,"");
                down[0]->type=2;
                down[0]->up=this;
                down[0]->name=str2;
                in_str.erase(0,peri1+1);
                arifm_right();
                }
            }
        }
    if(right!=NULL)
        right->mult_div();
    }

void calculator_base::for_compilation::brackets(void)
    {
    if(in_str.length()==0&&type==-1)
        throw std::invalid_argument("Wrong expression");
    peri1=in_str.find_first_of("(");
    if(peri1!=std::string::npos)
        {
        unsigned char input_number,perc1;
        char chr;
        get_name_r(in_str.substr(0,peri1),str1,str2);
        if(str1.length()!=0)
            {
            compil_per=new for_compilation(funcs,str2+in_str.substr(peri1,in_str.length()));
            compil_per->left=this;
            compil_per->right=right;
            right=compil_per;
            in_str=str1;
            }
        else
            {
            if(str2.length()==0)
                {
                input_number=1;
                }
            else
                {
                if(funcs->find(str2)==funcs->end())
                    {
                    throw std::invalid_argument("Unknown function "+str2);
                    }
                input_number=(*funcs)[str2].first;
                }
            down.resize(input_number);
            name=str2;
            type=0;
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
                down[perc1]=new for_compilation(funcs,str1);
                down[perc1]->up=this;
                down[perc1]->init();
                }
            if(peri1!=0)
                throw std::invalid_argument("Unbalansed brackets ");
            if(in_str.length()!=0)
                {
                compil_per=new for_compilation(funcs,in_str);
                compil_per->left=this;
                compil_per->right=right;
                right=compil_per;
                }
            else if(right!=NULL)
                {
                throw std::invalid_argument("Wrong expression");
                }
            in_str.clear();
            }
        }
    if(right!=NULL)
        right->brackets();
    }

calculator_base::for_compilation::for_compilation(functions *in1,const std::string &in2)
    {
    type=-1;
    funcs=in1;
    in_str=in2;
    
    left=NULL;
    right=NULL;
    up=NULL;
    }

calculator_base::for_compilation::~for_compilation()
    {
    for(auto it=down.begin();it!=down.end();++it)
        delete *it;
    }

void calculator_base::for_compilation::init(void)
    {
    brackets();
    mult_div();
    plus_minus();
    if(name.length()==0)
        {
        name=in_str;
        in_str.clear();
        if(get_number_r(name,str1,str2)==true)
            type=3;
        else
            type=2;
        }
    }
void calculator_base::for_compilation::check(void)
    {
    if(left!=NULL ||right!=NULL)
        throw std::invalid_argument("Wrong expression");
    else
        {
        for(auto it=down.begin();it!=down.end();++it)
            (*it)->check();
        }
    }
void calculator_base::for_compilation::out(int in,int in1)
    {
    /*std::cout<<in<<":"<<num<<":";
    if(up!=NULL)
        std::cout<<up->num;
    std::cout<<":"<<in1<<":"<<name<<":"<<in_str<<std::endl;
    
    for(auto it=down.begin();it!=down.end();++it)
        (*it)->out(in+1,num);
    */
    }
void calculator_base::for_compilation::make_string(void)
    {
    switch(type)
        {
        case 0:
            std::cout<<name<<"(";
            for(auto it=down.begin();it!=down.end();++it)
                {
                (*it)->make_string();
                if(it+1!=down.end())    
                    std::cout<<",";
                }
            std::cout<<")";
            break;
        case 1:
            if(name.find_first_of("!")!=std::string::npos)
                {
                std::cout<<name[0];
                down[0]->make_string();
                }
            else
                {
                down[0]->make_string();
                std::cout<<name;
                down[1]->make_string();
                }
            break;
        case 2:
            
        case 3:
            std::cout<<name;
            break;
        }
    }
