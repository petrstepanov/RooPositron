/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PdfHash.cpp
 * Author: petrstepanov
 * 
 * Created on December 6, 2018, 4:53 AM
 */

#include "PdfServer.h"
#include "providers/OneGaussProvider.h"
#include "providers/TwoGaussProvider.h"
#include "providers/ThreeGaussProvider.h"
#include "providers/ExpProvider.h"
#include "providers/TwoExpProvider.h"
#include "providers/ThreeExpProvider.h"
#include "providers/GrainProvider.h"
#include "providers/PowderProvider.h"
#include "providers/Powder2Provider.h"
#include "providers/ParaProvider.h"
#include "providers/TrappingProvider.h"

PdfServer::PdfServer(){};
PdfServer::~PdfServer(){};

PdfHashNames PdfServer::hashPdfName(const char* pdfName) {
	std::string name = pdfName;
	if (name == "1gauss")
		return kOneGaussPdf;
	if (name == "2gauss")
		return kTwoGaussPdf;
	if (name == "3gauss")
		return kThreeGaussPdf;
	if (name == "exp")
		return kExponentPdf;
	if (name == "2exp")
		return kTwoExponentPdf;
	if (name == "3exp")
		return kThreeExponentPdf;
	if (name == "trapping")
		return kTrappingPdf;
	if (name == "grain")
		return kGrainPdf;
	if (name == "powder")
		return kPowderPdf;
	if (name == "powder2")
		return kPowder2Pdf;
	if (name == "para")
		return kParamagneticPdf;
	return kExponentPdf;
}

RooAbsPdf* PdfServer::getPdf(const char* name, RooRealVar* observable) {
	int hashName = hashPdfName(name);
	pdfIndexes[hashName]++;

	switch (hashPdfName(name)) {
		case kOneGaussPdf: {
			OneGaussProvider* ogp = new OneGaussProvider(observable);
			return ogp->getPdf(pdfIndexes[kOneGaussPdf]);
			break;
		}
		case kTwoGaussPdf: {
			TwoGaussProvider* tgp = new TwoGaussProvider(observable);
			return tgp->getPdf(pdfIndexes[kTwoGaussPdf]);
			break;
		}
		case kThreeGaussPdf: {
			ThreeGaussProvider* tgp = new ThreeGaussProvider(observable);
			return tgp->getPdf(pdfIndexes[kThreeGaussPdf]);
			break;
		}
		case kExponentPdf: {
			ExpProvider* ep = new ExpProvider(observable);
			return ep->getPdf(pdfIndexes[kExponentPdf]);
			break;
		}
		case kTwoExponentPdf: {
			TwoExpProvider* tep = new TwoExpProvider(observable);
			return tep->getPdf(pdfIndexes[kTwoExponentPdf]);
			break;
		}
		case kThreeExponentPdf: {
			ThreeExpProvider* thep = new ThreeExpProvider(observable);
			return thep->getPdf(pdfIndexes[kThreeExponentPdf]);
			break;
		}
		case kTrappingPdf: {
			TrappingProvider* tp = new TrappingProvider(observable);
			return tp->getPdf(pdfIndexes[kTrappingPdf]);
			break;
		}
		case kGrainPdf: {
			GrainProvider* gp = new GrainProvider(observable);
			return gp->getPdf(pdfIndexes[kGrainPdf]);
			break;
		}
		case kPowderPdf: {
			PowderProvider* pp = new PowderProvider(observable);
			return pp->getPdf(pdfIndexes[kPowderPdf]);
			break;
		}
		case kPowder2Pdf: {
			Powder2Provider* pp = new Powder2Provider(observable);
			return pp->getPdf(pdfIndexes[kPowder2Pdf]);
			break;
		}
		case kParamagneticPdf: {
			ParaProvider* pp = new ParaProvider(observable);
			return pp->getPdf(pdfIndexes[kParamagneticPdf]);
			break;
		}
		default: {
			return NULL;
		}
	}
}

