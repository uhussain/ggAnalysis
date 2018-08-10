#multicrab

dataset = {
  'dataset1': '/MET/Run2018A-PromptReco-v1/MINIAOD',
  'dataset2': '/MET/Run2018A-PromptReco-v2/MINIAOD',
  'dataset3': '/MET/Run2018A-PromptReco-v3/MINIAOD',
  'dataset4':'/MET/Run2018B-PromptReco-v1/MINIAOD',
  'dataset5':'/MET/Run2018B-PromptReco-v2/MINIAOD',
  'dataset6': '/MET/Run2018C-PromptReco-v1/MINIAOD',
  'dataset7': '/MET/Run2018C-PromptReco-v2/MINIAOD',
  'dataset8': '/MET/Run2018C-PromptReco-v3/MINIAOD',
  'dataset9': '/MET/Run2018D-PromptReco-v1/MINIAOD',
  'dataset10': '/MET/Run2018D-PromptReco-v2/MINIAOD'
}

if __name__ == '__main__':
 from CRABAPI.RawCommand import crabCommand

def submit(config):
 res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
config = config()
name = 'Zprime_Ntuples2018_Aug7'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.publication = False
config.Site.storageSite = 'T2_US_Wisconsin'
config.JobType.psetName = 'run_data_10X.py'
config.JobType.outputFiles = ['ggtree_data.root']
#config.JobType.inputFiles = ['Summer16_23Sep2016AllV4_DATA.db','Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt']
config.section_('Data') 
#config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic'
#config.Data.splitting = 'LumiBased'
#/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-318876_13TeV_PromptReco_Collisions18_JSON.txt - A dataset
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PromptReco/Cert_314472-319851_13TeV_PromptReco_Collisions18_JSON.txt'
#Already submitted:
listOfSamples = ['dataset6','dataset7','dataset8']
#listOfSamples = ['dataset1']
for sample in listOfSamples:  
  config.General.requestName = sample
  config.Data.inputDataset = dataset[sample]
  config.Data.unitsPerJob = 180
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/uhussain/'+name
  submit(config)
