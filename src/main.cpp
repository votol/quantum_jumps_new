#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "calculator_c.h"


int main(int argc,char **argv)
    {
    calculator_c calc;
    try
        {
        calc.variables["t"]=complex<double>(0,0);
        //calc.expressions.add("-1.35e-2*a1+a2*1.25e+1*exp(8.31+i*0.65e-1)*i+e*26e+2/exp(i+3.45e-1)-a3");
        calc.expressions.add("pi*e+i*exp(pi-e)");
        complex<double> a;
        boost::posix_time::time_duration diff,diff1;
        boost::posix_time::ptime t;
        t=boost::posix_time::microsec_clock::local_time();
        for(volatile int j=0;j<10000000;j++)    
            {
            a=calc.expressions[0].calculate();
            }
        diff=boost::posix_time::microsec_clock::local_time()-t;
        std::cout<<"My calculator time:"<<diff.total_microseconds()<<std::endl;
        
        
        complex<double> b,i,e,pi;
        i=complex<double>(0,1);
        e=complex<double>(M_E,0);
        pi=complex<double>(M_PI,0);
        t=boost::posix_time::microsec_clock::local_time();
        
        for(volatile int j=0;j<10000000;j++)    
            {
            b=pi*e+i*exp(pi-e);
            }
        diff1=boost::posix_time::microsec_clock::local_time()-t;
        std::cout<<"C++ calculator time:"<<diff1.total_microseconds()<<std::endl;
        std::cout<<"Ratio:"<<double(diff.total_microseconds())/double(diff1.total_microseconds())<<std::endl;
        
        std::cout<<a.__re<<":"<<a.__im<<std::endl;
        std::cout<<a.__re-b.__re<<":"<<a.__im-b.__im<<std::endl;
        }
    catch(const std::invalid_argument& ia)
        {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        }
    return 0;
    }
