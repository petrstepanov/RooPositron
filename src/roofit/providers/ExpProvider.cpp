/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExpProvider.cpp
 * Author: petrstepanov
 * 
 * Created on December 5, 2018, 8:43 AM
 */

#include "ExpProvider.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "../pdfs/ExpPdf.h"
#include "../../model/Constants.h"
#include "../../util/StringUtils.h"
#include <iostream>

ExpProvider::ExpProvider(RooRealVar* _observable) : AbstractProvider(_observable) {}

ExpProvider::~ExpProvider() {
}

RooAbsPdf* ExpProvider::initPdf(int i) {
    RooConstVar* channelWidth = Constants::getInstance()->getRooChannelWidth();
    
    // Instantiate RooRealVar parameters
    Double_t tauVal=0.2;
    if(i==2) tauVal=0.5;
    if(i==3) tauVal=1.0;

    RooRealVar* tau = new RooRealVar(StringUtils::suffix("#tau", i).c_str(), StringUtils::ordinal("positron lifetime", i).c_str(), tauVal, 0.1, 5, "ns");
    RooFormulaVar* tauCh = new RooFormulaVar(StringUtils::suffix("tauCh", i).c_str(), StringUtils::ordinal("positron lifetime, channels", i).c_str(), "@0/@1", RooArgList(*tau, *channelWidth));
    
    // Instantinate model
    return new ExpPdf(StringUtils::suffix("exp", i).c_str(), StringUtils::ordinal("exponential pdf", i).c_str(), *observable, *tauCh);
}
