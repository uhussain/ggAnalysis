##### To work with CMSSW_9_4_4 you do :

cd CMSSW_9_4_4/src 
cmsenv 
git cms-init 
git cms-merge-topic lsoffi:CMSSW_9_4_0_pre3_TnP 
git cms-merge-topic guitargeek:ElectronID_MVA2017_940pre3 
scram b -j8 
cd $CMSSW_BASE/external/slc6_amd64_gcc630 
git clone https://github.com/lsoffi/RecoEgamma-PhotonIdentification.git data/RecoEgamma/PhotonIdentification/data
cd data/RecoEgamma/PhotonIdentification/data 
git checkout CMSSW_9_4_0_pre3_TnP 
cd $CMSSW_BASE/external/slc6_amd64_gcc630/ 
git clone https://github.com/lsoffi/RecoEgamma-ElectronIdentification.git data/RecoEgamma/ElectronIdentification/data 
cd data/RecoEgamma/ElectronIdentification/data 
git checkout CMSSW_9_4_0_pre3_TnP 
cd $CMSSW_BASE/src 
git cms-merge-topic cms-egamma:EGM_94X_v1 
cd EgammaAnalysis/ElectronTools/data 
git clone https://github.com/ECALELFS/ScalesSmearings.git 
cd ScalesSmearings/ 
git checkout Run2017_17Nov2017_v1 
cd $CMSSW_BASE/src 
git clone https://github.com/cmkuo/HiggsAnalysis.git 

git clone -b Zprime2017 git@github.com:uhussain/ggAnalysis.git <br>

scram b -j 10 <br>


The above code stores the decision in 64 integer. Each bit represents a decision<br>
for ELECRON ID: 5 IDs (Veto, Loose, Medium, Tight and HEEP) so only 5 bits are imp for us (59 bits of this integer  we are not using so may be we can change that to 16 bit integer later)<br>
Representing that integer in 5 bits: b4 b3 b2 b1 b0<br>
b0: Veto; b1: Loose; b2: Medium; b3: Tight and b4: HEEP<br>
To access the decision for <br>
(a) veto: eleIDbit[]>>0&1 ---> gives 0 or 1. if 0--> this eID is failed. if 1--> this eID is passed<br>
(b) Loose: eleIDbit[]>>1&1<br>
(c) Medium: eleIDbit[]>>2&1<br>
(d) Tight: eleIDbit[]>>3&1<br>
(e) HEEP: eleIDbit[]>>4&1<br>

for photons it is done the same way: it has 3 IDs<br>
so 3 bits represent the decision<br>
Representing that integer in 3 bits:  b2 b1 b0<br>
b0: Loose; b1: Medium; b2: Tight<br>
To access the decision for <br>
(a) Loose: phoIDbit[]>>0&1 ---> gives 0 or 1. if 0--> this phoID is failed. if 1--> this phoID is passed<br>
(b) Medium: phoIDbit[]>>1&1<br>
(c) Tight: phoIDbit[]>>2&1<br>

to access the MC status flag with GEN particles <br>
(a) fromHardProcessFinalState : mcStatusFlag[]>>0&1 ---> gives 0 (no) or 1 (yes). <br>
(b) isPromptFinalState        : mcStatusFlag[]>>1&1 ---> gives 0 (no) or 1 (yes). <br>
(c) fromHardProcessBeforeFSR  : mcStatusFlag[]>>2&1 ---> gives 0 (no) or 1 (yes). <br>

