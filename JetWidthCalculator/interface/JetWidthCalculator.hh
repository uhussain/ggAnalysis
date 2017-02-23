#ifndef JetWidthCalculator_hh
#define JetWidthCalculator_hh

// This is a simple helper class to compute energy weighted eta and phi 
// widths of a jet.  Width in ECal and HCal are available 

#include "DataFormats/PatCandidates/interface/Jet.h"
using namespace std;
class JetWidthCalculator {

public:

  JetWidthCalculator(const pat::Jet&);

  virtual ~JetWidthCalculator();

  double getEtaWidth() {return etaWidth;}
 // double getEtaWidthInECal() {return etaWidthInECal;}
 // double getEtaWidthInHCal() {return etaWidthInHCal;}

  double getPhiWidth() {return phiWidth;}
  //double getPhiWidthInECal() {return phiWidthInECal;}
  //double getPhiWidthInHCal() {return phiWidthInHCal;}

  double getPFCand12PtSum() {return pfCand12PtSum;}
  double getPFCandsPtSum() {return ptSum;}
  double getPFCand12Ratio() {return pt12ratio;} 
private:

  // No default constructor is possible

  JetWidthCalculator();

  // No copy constructor is needed

  JetWidthCalculator(const JetWidthCalculator&);

  // No equality operator is needed

  const JetWidthCalculator& operator=(const JetWidthCalculator&);

  double etaWidth;
  //double etaWidthInECal;
  //double etaWidthInHCal;

  double phiWidth;
  //double phiWidthInECal;
  //double phiWidthInHCal;
  
  double pfCand12PtSum;
  double ptSum;
  double pt12ratio;
};

#endif
