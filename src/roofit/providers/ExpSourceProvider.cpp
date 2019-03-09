/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ExpSourceProvider.cpp
 * Author: petrstepanov
 * 
 * Created on December 5, 2018, 8:43 AM
 */

#include "RooFormulaVar.h"
#include "../pdfs/ExpPdf.h"
#include "../../model/Constants.h"
#include "../../util/StringUtils.h"
#include "ExpSourceProvider.h"

ExpSourceProvider::ExpSourceProvider(RooRealVar* _observable) : AbstractProvider(_observable) {}

ExpSourceProvider::~ExpSourceProvider() {
}

RooAbsPdf* ExpSourceProvider::initPdf(int i) {
    RooConstVar* channelWidth = Constants::getInstance()->getRooChannelWidth();
    
    // Instantiate RooRealVar parameters
    RooRealVar* tauSource = new RooRealVar(StringUtils::suffix("#tau_source",i).c_str(), StringUtils::ordinal("positron lifetime in source", i).c_str(), 0.385, 0.1, 5, "ns");
    tauSource->setConstant(kTRUE);
    RooFormulaVar* tauSourceCh = new RooFormulaVar(StringUtils::suffix("tauSourceCh",i).c_str(), StringUtils::ordinal("positron lifetime in source, channels", i).c_str(), "@0/@1", RooArgList(*tauSource, *channelWidth));

    // Instantiate model
    return new ExpPdf(StringUtils::suffix("sourceComponent",i).c_str(), StringUtils::ordinal("source component", i).c_str(), *observable, *tauSourceCh);
}