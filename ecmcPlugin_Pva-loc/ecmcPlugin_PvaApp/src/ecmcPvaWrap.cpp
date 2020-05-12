/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcPvaWrap.cpp
*
*  Created on: Mar 22, 2020
*      Author: anderssandstrom
*      Credits to  https://github.com/sgreg/dynamic-loading 
*
\*************************************************************************/

// Needed to get headers in ecmc right...
#define ECMC_IS_PLUGIN


#include "ecmcPvaWrap.h"
#include "ecmcPva.cpp"

// pvget<double> pvgetobject_cpp;
// pvput<double> pvputobject_cpp;

 void* getPvGetObj() {
   return (void*) new pvget<double>();
 }

 void* getPvPutObj() {
   return (void*) new pvput<double>();
 }
