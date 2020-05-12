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


/*
template <typename T>
   struct toupper : public exprtk::igeneric_function<T>
   {
      typedef exprtk::igeneric_function<T> igenfunct_t
      typedef typename igenfunct_t::generic_type generic_t;
      typedef typename igenfunct_t::parameter_list_t parameter_list_t;
      typedef typename generic_t::string_view string_t;

      toupper()
      : exprtk::igeneric_function<T>("S",igenfunct_t::e_rtrn_string)
      {}

      inline T operator()(std::string& result,
                          parameter_list_t parameters)
      {
         result.clear();

         string_t string(params[0]);

         for (std::size_t i = 0; i < string.size(); ++i)
         {
            result += std::toupper(string[i]);
         }

         return T(0);
      }
   };*/

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
   { printf("pvget constructs 1\n"); }

   inline T operator()(parameter_list_t parameters)
   {
      string_t string(parameters[0]);

//       std::size_t r0 = 0;
//       std::size_t r1 = v.size() - 1;

      printf("pvget call\n");
      // if (
      //      (1 == ps_index) &&
      //      !exprtk::rtl::vecops::helper::
      //         load_vector_range<T>::process(parameters, r0, r1, 1, 2, 0)
      //    )
      //    return T(0);

      // for (std::size_t i = r0; i <= r1; ++i) { v[i] = rnd(); }

      return T(0);      
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

   using exprtk::igeneric_function<T>::operator();

   pvput()
   : exprtk::igeneric_function<T>("ST")
      /*
         Overloads:
         0. V   - vector
         1. VTT - vector, r0, r1
      */
   { printf("pvput constructs 1\n"); }

   inline T operator()(parameter_list_t parameters)
   {
      string_t string(parameters[0]);

      // std::size_t r0 = 0;
      // std::size_t r1 = v.size() - 1;

      printf("pvput call\n");

      // if (
      //      (1 == ps_index) &&
      //      !exprtk::rtl::vecops::helper::
      //         load_vector_range<T>::process(parameters, r0, r1, 1, 2, 0)
      //    )
      //    return T(0);

      // for (std::size_t i = r0; i <= r1; ++i) { v[i] = rnd(); }

      return T(1);
   }

private:

  //  inline T rnd()
  //  {
  //     // Note: Do not use this in production
  //     // Result is in the interval [0,1)
  //     return T(::rand() / T(RAND_MAX + 1.0));
  //  }
};
