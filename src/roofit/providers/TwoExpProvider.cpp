/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TwoExpProvider.cpp
 * Author: petrstepanov
 * 
 * Created on December 5, 2018, 8:43 AM
 */

#include "TwoExpProvider.h"
#include "RooRealVar.h"
#include "RooFormulaVar.h"
#include "../pdfs/TwoExpPdf.h"
#include "../../model/Constants.h"
#include "../../util/StringUtils.h"
#include <iostream>

TwoExpProvider::TwoExpProvider(RooRealVar* _observable) : AbstractProvider(_observable) {}

TwoExpProvider::~TwoExpProvider() {
}

RooAbsPdf* TwoExpProvider::initPdf(int i) {
    RooConstVar* channelWidth = Constants::getInstance()->getRooChannelWidth();
    
    // Instantiate RooRealVar parameters
    RooRealVar* tau1 = new RooRealVar("#tau1", "1st positron lifetime", 0.2, 0.1, 2, "ns");
    RooFormulaVar* tau1Ch = new RooFormulaVar("tau1Ch", "1st positron lifetime, channels", "@0/@1", RooArgList(*tau1, *channelWidth));

    RooRealVar* tau2 = new RooRealVar("#tau2", "2nd positron lifetime", 0.5, 0.3, 5, "ns");
    RooFormulaVar* tau2Ch = new RooFormulaVar("tau2Ch", "2nd positron lifetime, channels", "@0/@1", RooArgList(*tau2, *channelWidth));

    RooRealVar* int2 = new RooRealVar("Int2", "2nd exponent fraction", 1, 0, 20, "%");
    RooFormulaVar* int2Norm = new RooFormulaVar("int2Norm", "@0/100", *int2);

    // Instantinate model
    return new TwoExpPdf("twoExpPdf", "two exponential component", *observable, *tau1Ch, *tau2Ch, *int2Norm);
}
