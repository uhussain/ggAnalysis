#include "ggAnalysis/JetWidthCalculator/interface/JetWidthCalculator.hh"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include <math.h>
JetWidthCalculator::JetWidthCalculator(const pat::Jet& jet) {
  jet.pt();
  jet.eta();
  jet.phi();
  //float jetet = jet.et();
  double pfCand1pt = 0;
  double pfCand2pt = 0;  
  double etSum = 0;
  double etaSum = 0;
  double etaSqSum = 0;
  double phiSum = 0;
  double phiSqSum = 0;
  /*double etSumInECal = 0;
  double etaSumInECal = 0;
  double etaSqSumInECal = 0;
  double phiSumInECal = 0;
  double phiSqSumInECal = 0;
  double etSumInHCal = 0;
  double etaSumInHCal = 0;
  double etaSqSumInHCal = 0;
  double phiSumInHCal = 0;
  double phiSqSumInHCal = 0;
  */
  double packedCands = jet.numberOfDaughters();
  //std::cout<<"No. of packedCands/Constituents of a jet: "<<packedCands<<std::endl;
 // double nPhotons = 0;
 // double nCHPions = 0;
 // double nMiscParticles=0;
  for(uint32_t i = 0; i < packedCands;  i++) {
    const reco::Candidate *pfCand = jet.daughter(i);
    //std::cout<<i+1<<")"<<"PfCand constituent of Jet: "<< pfCand->pdgId()<<std::endl;
    if (pfCand->pdgId() == 211 || pfCand->pdgId() == -211){
    nCHPions++;
    }
    else if (pfCand->pdgId() == 22){
    nPhotons++;
    }
    else{
    nMiscParticles++;
    PID.push_back(pfCand->pdgId());
    //std::cout<<"PfCand constituent of Jet: "<< pfCand->pdgId()<<std::endl;
    }
    ptSum +=pfCand->pt();
    etSum += pfCand->et();
    //float frac = (etSum/jetet);
    //if (frac >= 0.90){
    //std::cout<<"nPFCand carrying "<< frac*100 <<" of jet energy: "<<i+1<<std::endl;
    //}
    etaSum += (pfCand->eta() * pfCand->et());
    etaSqSum += (pfCand->eta() * pfCand->eta() * pfCand->et());
    phiSum += (pfCand->phi() * pfCand->et());
    phiSqSum += (pfCand->phi() * pfCand->phi() * pfCand->et());
   /* etSumInECal += pfCand->ecalEnergy();
    etaSumInECal += (pfCand->eta() * pfCand->ecalEnergy());
    etaSqSumInECal += (pfCand->eta() * pfCand->eta() * pfCand->ecalEnergy());
    phiSumInECal += (pfCand->phi() * pfCand->ecalEnergy());
    phiSqSumInECal += (pfCand->phi() * pfCand->phi() * pfCand->ecalEnergy());
    etSumInHCal += pfCand->hcalEnergy();
    etaSumInHCal += (pfCand->eta() * pfCand->hcalEnergy());
    etaSqSumInHCal += (pfCand->eta() * pfCand->eta() * pfCand->hcalEnergy());
    phiSumInHCal += (pfCand->phi() * pfCand->hcalEnergy());
    phiSqSumInHCal += (pfCand->phi() * pfCand->phi() * pfCand->hcalEnergy());
  */
    }
  if (packedCands>1){
      pfCand1pt = jet.daughter(0)->pt();
      pfCand2pt = jet.daughter(1)->pt();
     // std::cout<<"pfCand1pt("<<jet.daughter(0)->pdgId()<<"): " <<pfCand1pt<<std::endl;
     // std::cout<<"pfCand2pt("<<jet.daughter(1)->pdgId()<<"): " <<pfCand2pt<<std::endl;
      }
  else{
      pfCand1pt = jet.daughter(0)->pt(); 
     // std::cout<<"pfCand1pt("<<jet.daughter(0)->pdgId()<<"): " <<pfCand1pt<<std::endl;
      }
  pfCand12PtSum = pfCand1pt + pfCand2pt;
  //std::cout<<"ptSum: " <<ptSum<<std::endl;
  //std::cout<<"pfCand12PtSum: "<<pfCand12PtSum<<std::endl;
  pt12ratio = (pfCand12PtSum/ptSum);
  //std::cout<<"pt12ratio: "<<pt12ratio<<std::endl; 
  if(etSum < 0.000001) etSum = 0.000001; // To avoid NaNs
  double etaAve = etaSum / etSum;
  double etaSqAve = etaSqSum / etSum;
  etaWidth = sqrt(etaSqAve - etaAve * etaAve);
  double phiAve = phiSum / etSum;
  double phiSqAve = phiSqSum / etSum;
  phiWidth = sqrt(phiSqAve - phiAve * phiAve);
 /* if(etSumInECal < 0.000001) etSumInECal = 0.000001; // To avoid NaNs
  double etaAveInECal = etaSumInECal / etSumInECal;
  double etaSqAveInECal = etaSqSumInECal / etSumInECal;
  etaWidthInECal = sqrt(etaSqAveInECal - etaAveInECal * etaAveInECal);
  double phiAveInECal = phiSumInECal / etSumInECal;
  double phiSqAveInECal = phiSqSumInECal / etSumInECal;
  phiWidthInECal = sqrt(phiSqAveInECal - phiAveInECal * phiAveInECal);
  if(etSumInECal < 0.000001) etSumInHCal = 0.000001; // To avoid NaNs
  double etaAveInHCal = etaSumInHCal / etSumInHCal;
  double etaSqAveInHCal = etaSqSumInHCal / etSumInHCal;
  etaWidthInHCal = sqrt(etaSqAveInHCal - etaAveInHCal * etaAveInHCal);
  double phiAveInHCal = phiSumInHCal / etSumInHCal;
  double phiSqAveInHCal = phiSqSumInHCal / etSumInHCal;
  phiWidthInHCal = sqrt(phiSqAveInHCal - phiAveInHCal * phiAveInHCal);
  */
  //std::cout<<"Type of pfCands/Constituents:"<<std::endl;
  //std::cout <<"nPhotons: " <<nPhotons<<","<<" nCHPions: "<<nCHPions<<","<<" OtherMesons: "<<nMiscParticles<<std::endl;
 // std::cout<<"etaSum: "<<etaSum<<std::endl;
  //std::cout<<"etSum: "<<etSum<<std::endl;
  //std::cout<<"jet Et: "<<jetet<<std::endl;
  //std::cout<<"etaSqSum: "<<etaSqSum<<std::endl;
 // std::cout<<"phiSum: "<<phiSum<<std::endl;
 // std::cout<<"phiSqSum: "<<phiSqSum<<std::endl;
}

JetWidthCalculator::~JetWidthCalculator() {;}
