#multicrab

dataset = {
  'dataset1': '/MET/Run2017B-31Mar2018-v1/MINIAOD',
  'dataset2': '/MET/Run2017C-31Mar2018-v1/MINIAOD',
  'dataset3': '/MET/Run2017D-31Mar2018-v1/MINIAOD',
  'dataset4':'/MET/Run2017E-31Mar2018-v1/MINIAOD',
  'dataset5':'/MET/Run2017F-31Mar2018-v1/MINIAOD'
}

if __name__ == '__main__':
 from CRABAPI.RawCommand import crabCommand

def submit(config):
 res = crabCommand('submit', config = config)

from CRABClient.UserUtilities import config
config = config()
name = 'Zprime_Ntuples2017_Aug2'
config.General.workArea = 'crab_'+name
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.Data.publication = False
config.Site.storageSite = 'T2_US_Wisconsin'
config.JobType.psetName = 'run_data_94X.py'
config.JobType.outputFiles = ['ggtree_data.root']
#config.JobType.inputFiles = ['Summer16_23Sep2016AllV4_DATA.db','Summer16_23Sep2016BCDV4_DATA_L2Relative_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L3Absolute_AK8PFchs.txt','Summer16_23Sep2016BCDV4_DATA_L2L3Residual_AK8PFchs.txt']
config.section_('Data') 
#config.Data.inputDBS = 'global'
config.Data.splitting = 'Automatic'
#config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON.txt'
#Already submitted:
listOfSamples = ['dataset1','dataset2','dataset3','dataset4']
#listOfSamples = ['dataset5']
for sample in listOfSamples:  
  config.General.requestName = sample
  config.Data.inputDataset = dataset[sample]
  config.Data.unitsPerJob = 180
  config.Data.totalUnits = -1
  config.Data.outLFNDirBase = '/store/user/uhussain/'+name
  submit(config)
