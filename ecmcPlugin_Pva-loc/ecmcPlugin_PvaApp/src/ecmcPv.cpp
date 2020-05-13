/*************************************************************************\
* Copyright (c) 2019 European Spallation Source ERIC
* ecmc is distributed subject to a Software License Agreement found
* in file LICENSE that is included with this distribution. 
*
*  ecmcPv.cpp
*
*  Created on: May 12, 2020
*      Author: anderssandstrom
*
\*************************************************************************/
#include "ecmcPv.h"

/*

    try {
        PvaClientPtr pva= PvaClient::get("pva ca");
        exampleDouble(pva,"PVRdouble","pva");
        exampleDoubleArray(pva,"PVRdoubleArray","pva");
        PvaClientChannelPtr pvaChannel = pva->createChannel("DBRdouble00","ca");
        pvaChannel->issueConnect();
        Status status = pvaChannel->waitConnect(1.0);
        if(status.isOK()) {
            exampleDouble(pva,"DBRdouble00","pva");
            exampleDouble(pva,"DBRdouble00","ca");
            exampleDoubleArray(pva,"DBRdoubleArray","pva");
            exampleDoubleArray(pva,"DBRdoubleArray","ca");
        } else {
             cout << "DBRdouble00 not found\n";
        }
        cout << "_____examplePvaClientGet done_______\n";
    } catch (std::exception& e) {
        cerr << "exception " << e.what() << endl;
        return 1;
    }
*/

/*
    PvaClientPutPtr put = channel->put();
    PvaClientPutDataPtr putData = put->getData();
    PvaClientMonitorPtr monitor = pva->channel(channelName,providerName,2.0)->monitor("value");
    PvaClientMonitorDataPtr monitorData = monitor->getData();
    putData->putDouble(3.0); put->put();
*/

ecmcPv::ecmcPv(std::string pvName,std::string providerName) {
  
  name_         = pvName;
  providerName_ = providerName;
  errorCode_    = 0;
  try{
    pva_        = PvaClient::get("pva ca");
    pvaChannel_ = pva_->createChannel(pvName,providerName);      
    pvaChannel_->issueConnect();
    Status status = pvaChannel_->waitConnect(1.0);
    if(!status.isOK()) {
      cout << " connect failed\n"; 
      throw std::runtime_error("Error: Failed connect to:" + pvName);
    }

    get_ = pvaChannel_->createGet();
    get_->issueConnect();
    status = get_->waitConnect();
    if(!status.isOK()) {
      cout << " createGet failed\n"; return;
      throw std::runtime_error("Error: Failed create get to:" + pvName);
    }
    getData_ = get_->getData();
    //double value = getData_->getDouble();
    //cout << "as double " << value << endl;
    //cout << "__exampleDouble__ returning\n";

    put_ = pvaChannel_->put();
    putData_ = put_->getData();
    //monitor_ = pva_->channel(pvName,providerName,2.0)->monitor("value");
    //monitorData_ = monitor_->getData();

    // provider_ = new pvac::ClientProvider(providerName_);
    // channel_  = new pvac::ClientChannel(provider_->connect(name_));
    // std::cout << channel_->name() << " : " << channel_->get()->getData()->getDouble() << "\n";    
  }
  catch(std::exception &e){
    std::cerr << "Error: " << e.what() << "\n";
    errorCode_ = ECMC_PV_PUT_ERROR;
  }
}

ecmcPv::~ecmcPv() {
}

int ecmcPv::getError() {
  return errorCode_;
}

int ecmcPv::reset() {
  errorCode_ = 0;
  return 0;
}

double ecmcPv::get() {

  if(errorCode_ == ECMC_PV_GET_ERROR) {
    reset(); // reset if try again
  }

  try{
    return getData_->getDouble();
  }
  catch(std::exception &e){
    errorCode_ = ECMC_PV_GET_ERROR;
    std::cerr << "Error: " << e.what() << errorCode_ << ", " << "\n";
    return 0;
  }
  return 0;
}

void ecmcPv::put(double value) {

  if(errorCode_ == ECMC_PV_PUT_ERROR) {
    reset(); // reset if try again
  }

  try{
    putData_->putDouble(value);
    put_->put();
  }
  catch(std::exception &e){
    errorCode_ = ECMC_PV_PUT_ERROR;
    std::cerr << "Error: " << e.what() << errorCode_ << ", " << "\n";
  }
  return;
}
