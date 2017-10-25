#multicrab

dataset = {
  'dataset1': '/SingleMuon/Run2016G-03Feb2017-v1/MINIAOD',
  'dataset2': '/SingleElectron/Run2016G-03Feb2017-v1/MINIAOD',
  'dataset3': '/DoubleEG/Run2016G-03Feb2017-v1/MINIAOD',
  'dataset4':'/DoubleMuon/Run2016G-03Feb2017-v1/MINIAOD'
  #'dataset5':'/MET/Run2016H-03Feb2017_ver2-v1/MINIAOD'
}

if __name__ == '__main__':
 from CRABAPI.RawCommand import crabCommand

def submit(config):
 res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
config = config()
name = 'ZprimeCR_Ntuples_Oct16'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.publication = False
config.Site.storageSite = 'T2_US_Wisconsin'
config.JobType.psetName = 'run_data_80X_SingleMu.py'
config.JobType.outputFiles = ['ggtree_data.root']
config.JobType.inputFiles = ['Summer16_23Sep2016AllV4_DATA.db','Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt']
config.section_('Data') 
#config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
#Already submitted:
#listOfSamples = ['dataset1','dataset2','dataset3','dataset4']
listOfSamples = ['dataset1','dataset4']
for sample in listOfSamples:  
  config.General.requestName = sample
  config.Data.inputDataset = dataset[sample]
  config.Data.unitsPerJob = 15
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/uhussain/'+name
  submit(config)
