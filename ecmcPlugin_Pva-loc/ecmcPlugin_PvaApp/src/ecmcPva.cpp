/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcPva.cpp
*
*  Created on: May 12, 2020
*      Author: anderssandstrom
*      Credits to  https://github.com/sgreg/dynamic-loading 
*
\*************************************************************************/

#include "exprtk.hpp"
#include "pva/client.h"

template <typename T>
struct pvget : public exprtk::igeneric_function<T>
{
public:

  typedef typename exprtk::igeneric_function<T> igfun_t;
  typedef typename igfun_t::parameter_list_t    parameter_list_t;
  typedef typename igfun_t::generic_type        generic_type;
  typedef typename generic_type::string_view    string_t;

  using exprtk::igeneric_function<T>::operator();

  pvget()
  : exprtk::igeneric_function<T>("S")
  { 
    printf("pvget constructs 1\n"); 
  }

  inline T operator()(parameter_list_t parameters)
  {
    string_t pvName(parameters[0]);
    printf("pvget call: %s\n",&pvName[0]);
    try{
      pvac::ClientProvider provider("pva");  // move to constructor
      pvac::ClientChannel  channel(provider.connect(&pvName[0]));
      std::cout << channel.name() << " : " << channel.get() << "\n";
    }
    catch(std::exception &e){
      std::cerr << "Error: " << e.what() << "\n";
    }
    return T(1000);
  }

private:

  //  inline T rnd()
  //  {
  //     // Note: Do not use this in production
  //     // Result is in the interval [0,1)
  //     return T(::rand() / T(RAND_MAX + 1.0));
  //  }
};

template <typename T>
struct pvput : public exprtk::igeneric_function<T>
{
public:

  typedef typename exprtk::igeneric_function<T> igfun_t;
  typedef typename igfun_t::parameter_list_t    parameter_list_t;
  typedef typename igfun_t::generic_type        generic_type;
  typedef typename generic_type::string_view    string_t;
  typedef typename generic_type::scalar_view    scalar_t;
  using exprtk::igeneric_function<T>::operator();

  pvput()
  : exprtk::igeneric_function<T>("ST")
  { 
    printf("pvput constructs 1\n"); 
  }

  inline T operator()(parameter_list_t parameters)
  {
    string_t pvName(parameters[0]);
    scalar_t val(parameters[1]);    
    printf("pvput call: %s, value: %lf\n",&pvName[0],val());
    return T(val()*val());
  }

private:

  //  inline T rnd()
  //  {
  //     // Note: Do not use this in production
  //     // Result is in the interval [0,1)
  //     return T(::rand() / T(RAND_MAX + 1.0));
  //  }
};
