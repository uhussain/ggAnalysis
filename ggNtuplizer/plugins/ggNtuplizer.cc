#include "ggAnalysis/ggNtuplizer/interface/ggNtuplizer.h"

using namespace std;
using namespace edm;

void setbit(UShort_t& x, UShort_t bit) {
  UShort_t a = 1;
  x |= (a << bit);
}

ggNtuplizer::ggNtuplizer(const edm::ParameterSet& ps) :
  hltPrescaleProvider_(ps, consumesCollector(), *this)
{

  development_               = ps.getParameter<bool>("development");
  addFilterInfoAOD_          = ps.getParameter<bool>("addFilterInfoAOD");
  addFilterInfoMINIAOD_      = ps.getParameter<bool>("addFilterInfoMINIAOD");
  doNoHFMET_                 = ps.getParameter<bool>("doNoHFMET");

  doGenParticles_            = ps.getParameter<bool>("doGenParticles");
  runOnParticleGun_          = ps.getParameter<bool>("runOnParticleGun");
  runOnSherpa_               = ps.getParameter<bool>("runOnSherpa");
  dumpPhotons_               = ps.getParameter<bool>("dumpPhotons");
  dumpJets_                  = ps.getParameter<bool>("dumpJets");
  dumpSubJets_               = ps.getParameter<bool>("dumpSubJets");
  dumpSoftDrop_              = ps.getParameter<bool>("dumpSoftDrop");
  dumpTaus_                  = ps.getParameter<bool>("dumpTaus");
  dumpPDFSystWeight_         = ps.getParameter<bool>("dumpPDFSystWeight");
  dumpGenScaleSystWeights_   = ps.getParameter<bool>("dumpGenScaleSystWeights");
  dumpMuonsPairs_            = ps.getParameter<bool>("dumpMuonsPairs");
  dumpZPairs_                = ps.getParameter<bool>("dumpZPairs");
  dumpIsoTracks_             = ps.getParameter<bool>("dumpIsoTracks");
  isAOD_                     = ps.getParameter<bool>("isAOD");
  runHFElectrons_            = ps.getParameter<bool>("runHFElectrons");

  trgFilterDeltaPtCut_       = ps.getParameter<double>("trgFilterDeltaPtCut");
  trgFilterDeltaRCut_        = ps.getParameter<double>("trgFilterDeltaRCut");
  
  isoPtLeptoncut_            = ps.getParameter<double>("isoPtLeptoncut");
  isoPtcut_                  = ps.getParameter<double>("isoPtcut");
  isoPtcutnoIso_             = ps.getParameter<double>("isoPtcutnoIso");
  isoDRcut_                  = ps.getParameter<double>("isoDRcut");
  isoIsoDZcut_               = ps.getParameter<double>("isoIsoDZcut");
  isoMiniIsoParams_          = ps.getParameter<vector<double>>("isoMiniIsoParams");
  if (isoMiniIsoParams_.size() != 3) throw cms::Exception("ParameterError") << "isoMiniIsoParams must have exactly 3 elements.\n";
  isoChIsocut_               = ps.getParameter<double>("isoChIsocut");
  isoLepOverlapDR_           = ps.getParameter<double>("isoLepOverlapDR");
  isoOverlapPtMin_           = ps.getParameter<double>("isoOverlapPtMin");

  vtxLabel_                  = consumes<reco::VertexCollection>        (ps.getParameter<InputTag>("VtxLabel"));
  vtxBSLabel_                = consumes<reco::VertexCollection>        (ps.getParameter<InputTag>("VtxBSLabel"));
  rhoLabel_                  = consumes<double>                        (ps.getParameter<InputTag>("rhoLabel"));
  rhoCentralLabel_           = consumes<double>                        (ps.getParameter<InputTag>("rhoCentralLabel"));
  trgEventLabel_             = consumes<trigger::TriggerEvent>         (ps.getParameter<InputTag>("triggerEvent"));
  triggerObjectsLabel_       = consumes<pat::TriggerObjectStandAloneCollection>(ps.getParameter<edm::InputTag>("triggerEvent"));
  trgResultsLabel_           = consumes<edm::TriggerResults>           (ps.getParameter<InputTag>("triggerResults"));
  patTrgResultsLabel_        = consumes<edm::TriggerResults>           (ps.getParameter<InputTag>("patTriggerResults"));
  trgResultsProcess_         =                                          ps.getParameter<InputTag>("triggerResults").process();
  generatorLabel_            = consumes<GenEventInfoProduct>           (ps.getParameter<InputTag>("generatorLabel"));
  lheEventLabel_             = consumes<LHEEventProduct>               (ps.getParameter<InputTag>("LHEEventLabel"));
  puCollection_              = consumes<vector<PileupSummaryInfo> >    (ps.getParameter<InputTag>("pileupCollection"));
  genParticlesCollection_    = consumes<vector<reco::GenParticle> >    (ps.getParameter<InputTag>("genParticleSrc"));
  pfMETlabel_                = consumes<View<pat::MET> >               (ps.getParameter<InputTag>("pfMETLabel"));  
  altpfMETlabel_                = consumes<View<pat::MET> >               (ps.getParameter<InputTag>("altpfMETLabel"));
  electronCollection_        = consumes<View<pat::Electron> >          (ps.getParameter<InputTag>("electronSrc"));
  calibelectronCollection_   = consumes<View<pat::Electron> >          (ps.getParameter<InputTag>("calibelectronSrc"));
  gsfTracks_                 = consumes<View<reco::GsfTrack>>          (ps.getParameter<InputTag>("gsfTrackSrc"));

  BadChCandFilterToken_      = consumes<bool>                          (ps.getParameter<InputTag>("BadChargedCandidateFilter"));
  BadPFMuonFilterToken_      = consumes<bool>                          (ps.getParameter<edm::InputTag>("BadPFMuonFilter"));

  photonCollection_          = consumes<View<pat::Photon> >            (ps.getParameter<InputTag>("photonSrc"));
  calibphotonCollection_     = consumes<View<pat::Photon> >            (ps.getParameter<InputTag>("calibphotonSrc"));
  muonCollection_            = consumes<View<pat::Muon> >              (ps.getParameter<InputTag>("muonSrc"));
  ebReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("ebReducedRecHitCollection"));
  eeReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("eeReducedRecHitCollection"));
  esReducedRecHitCollection_ = consumes<EcalRecHitCollection>          (ps.getParameter<InputTag>("esReducedRecHitCollection")); 
  recophotonCollection_      = consumes<reco::PhotonCollection>        (ps.getParameter<InputTag>("recoPhotonSrc"));
  tracklabel_                = consumes<reco::TrackCollection>         (ps.getParameter<InputTag>("TrackLabel"));
  gsfElectronlabel_          = consumes<reco::GsfElectronCollection>   (ps.getParameter<InputTag>("gsfElectronLabel"));
  tauCollection_             = consumes<vector<pat::Tau> >             (ps.getParameter<InputTag>("tauSrc"));
  pfAllParticles_            = consumes<reco::PFCandidateCollection>   (ps.getParameter<InputTag>("PFAllCandidates"));
  pckPFCandidateCollection_  = consumes<pat::PackedCandidateCollection>(ps.getParameter<InputTag>("packedPFCands"));
  pckPFCdsLabel_             = consumes<vector<pat::PackedCandidate>>  (ps.getParameter<InputTag>("packedPFCands"));
  recoCdsLabel_              = consumes<View<reco::Candidate>>         (ps.getParameter<InputTag>("packedPFCands"));

  jetsAK4Label_              = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak4JetSrc"));
  jetsAK8Label_              = consumes<View<pat::Jet> >               (ps.getParameter<InputTag>("ak8JetSrc"));
  //boostedDoubleSVLabel_      = consumes<reco::JetTagCollection>        (ps.getParameter<InputTag>("boostedDoubleSVLabel"));
  newparticles_              =                                          ps.getParameter< vector<int > >("newParticles");
  jecAK8PayloadNames_        =                                          ps.getParameter<std::vector<std::string> >("jecAK8PayloadNames"); 

  //pfLooseId_                 = ps.getParameter<ParameterSet>("pfLooseId");

  cicPhotonId_ = new CiCPhotonID(ps);
  egmScaler_   = new EnergyScaleCorrection_class("EgammaAnalysis/ElectronTools/data/ScalesSmearings/Moriond17_23Jan_ele");

  // electron ID 
  eleVetoIdMapToken_       = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleVetoIdMap"));
  eleLooseIdMapToken_      = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleLooseIdMap"));
  eleMediumIdMapToken_     = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleMediumIdMap"));
  eleTightIdMapToken_      = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleTightIdMap"));
  eleHLTIdMapToken_        = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleHLTIdMap"));
  eleHEEPIdMapToken_       = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("eleHEEPIdMap"));
  eleMVAValuesMapToken_    = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("eleMVAValuesMap"));
  eleMVAHZZValuesMapToken_ = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("eleMVAHZZValuesMap"));
  elePFClusEcalIsoToken_   = mayConsume<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("elePFClusEcalIsoProducer"));
  elePFClusHcalIsoToken_   = mayConsume<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("elePFClusHcalIsoProducer"));

  // Photon ID in VID framwork 
  phoLooseIdMapToken_             = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoLooseIdMap"));
  phoMediumIdMapToken_            = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoMediumIdMap"));
  phoTightIdMapToken_             = consumes<edm::ValueMap<bool> >(ps.getParameter<edm::InputTag>("phoTightIdMap"));
  phoMVAValuesMapToken_           = consumes<edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoMVAValuesMap")); 
  phoChargedIsolationToken_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation"));
  phoNeutralHadronIsolationToken_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation"));
  phoPhotonIsolationToken_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation"));
  phoWorstChargedIsolationToken_  = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoWorstChargedIsolation"));

  phoChargedIsolationToken_CITK_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation_CITK"));
  phoPhotonIsolationToken_CITK_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation_CITK"));
  phoNeutralHadronIsolationToken_CITK_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation_CITK"));
  
  phoChargedIsolationToken_PUPPI_       = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoChargedIsolation_PUPPI"));
  phoNeutralHadronIsolationToken_PUPPI_ = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoNeutralHadronIsolation_PUPPI"));
  phoPhotonIsolationToken_PUPPI_        = consumes <edm::ValueMap<float> >(ps.getParameter<edm::InputTag>("phoPhotonIsolation_PUPPI"));

  Service<TFileService> fs;
  tree_    = fs->make<TTree>("EventTree", "Event data (tag V08_00_26_06)");
  hEvents_ = fs->make<TH1F>("hEvents",    "total processed and skimmed events",   2,  0,   2);

  branchesGlobalEvent(tree_);

  if (doGenParticles_) {
    branchesGenInfo(tree_, fs);
    branchesGenPart(tree_);
  }

  branchesMET(tree_);
  branchesPhotons(tree_);
  branchesElectrons(tree_);
  branchesMuons(tree_);
  if (dumpPhotons_)    branchesPFPhotons(tree_);
  if (runHFElectrons_) branchesHFElectrons(tree_);
  if (dumpTaus_)       branchesTaus(tree_);
  if (dumpJets_)       branchesJets(tree_);
  if (dumpMuonsPairs_) branchesMuonPairs(tree_);
  if (dumpZPairs_)     branchesZPairs(tree_);
  if (dumpIsoTracks_)  branchesIsoTracks(tree_);
}

ggNtuplizer::~ggNtuplizer() {
  cleanupPhotons();
  delete cicPhotonId_;
}

void ggNtuplizer::analyze(const edm::Event& e, const edm::EventSetup& es) {

  hEvents_->Fill(0.5);

  if (doGenParticles_) {
    jetResolution_   = JME::JetResolution::get(es, "AK4PFchs_pt");
    jetResolutionSF_ = JME::JetResolutionScaleFactor::get(es, "AK4PFchs");
    AK8jetResolution_   = JME::JetResolution::get(es, "AK8PFchs_pt");
    AK8jetResolutionSF_ = JME::JetResolutionScaleFactor::get(es, "AK8PFchs");
  }

  edm::Handle<reco::VertexCollection> vtxHandle;
  e.getByToken(vtxLabel_, vtxHandle);

  reco::Vertex vtx;

  // best-known primary vertex coordinates
  math::XYZPoint pv(0, 0, 0);
  for (vector<reco::Vertex>::const_iterator v = vtxHandle->begin(); v != vtxHandle->end(); ++v) {
    // replace isFake() for miniAOD since it requires tracks while miniAOD vertices don't have tracks:
    // Vertex.h: bool isFake() const {return (chi2_==0 && ndof_==0 && tracks_.empty());}
    bool isFake = isAOD_ ? v->isFake() : (v->chi2() == 0 && v->ndof() == 0);

    if (!isFake) {
      pv.SetXYZ(v->x(), v->y(), v->z());
      vtx = *v;
      break;
    }
  }

  initTriggerFilters(e);

  fillGlobalEvent(e, es);
  if (!e.isRealData()) {
    fillGenInfo(e);
    if (doGenParticles_)
      fillGenPart(e);
  }

  fillMET(e, es);
  fillPhotons(e, es); // FIXME: photons have different vertex (not pv)
  fillPFPhotons(e, es);
  fillElectrons(e, es, pv);
  fillMuons(e, pv, vtx);

  if (runHFElectrons_ ) fillHFElectrons(e);
  if (dumpTaus_)        fillTaus(e);
  if (dumpJets_)        fillJets(e,es);
  if (dumpMuonsPairs_)  fillMuonsPairs(e, es, pv, vtx);
  if (dumpZPairs_)      fillZPairs(e, es, pv, vtx);
  if (dumpIsoTracks_)   fillIsoTracks(e);

  hEvents_->Fill(1.5);
  tree_->Fill();

}


// void ggNtuplizer::fillDescriptions(edm::ConfigurationDescriptions& descriptions)
// {
//   //The following says we do not know what parameters are allowed so do no validation
//   // Please change this to state exactly what you do use, even if it is no parameters
//   edm::ParameterSetDescription desc;
//   desc.setUnknown();
//   descriptions.addDefault(desc);
// }

DEFINE_FWK_MODULE(ggNtuplizer);
