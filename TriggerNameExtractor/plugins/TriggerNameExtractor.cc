// -*- C++ -*-
//
// Package:    TriggerNameEDAnalyzer/TriggerNameExtractor
// Class:      TriggerNameExtractor
//
/**\class TriggerNameExtractor TriggerNameExtractor.cc TriggerNameEDAnalyzer/TriggerNameExtractor/plugins/TriggerNameExtractor.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Pritam Kalbhor
//         Created:  Thu, 22 Nov 2018 16:55:19 GMT
//
//


// system include files
#include <memory>
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "FWCore/Framework/interface/global/EDProducer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include <DataFormats/Math/interface/deltaR.h>
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"


#include "FWCore/Framework/interface/TriggerReport.h"
#include "FWCore/Framework/interface/TriggerNamesService.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"


#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "TLorentzVector.h"

/*Newly added, which are needed for this to work
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include <TTree.h>
#include <vector>
*/

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


   using namespace edm;
    using namespace std;
    using namespace reco;
//   using namespace pat;

using reco::TrackCollection;

class TriggerNameExtractor : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TriggerNameExtractor(const edm::ParameterSet&);
      ~TriggerNameExtractor();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
//      edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
	
	// triggerresults                    = iConfig.getParameter<edm::InputTag>("triggerresults");
	// triggerresultsTok                 = consumes<edm::TriggerResults>(triggerresults);
 	edm::InputTag trigtag;
        edm::EDGetTokenT<edm::TriggerResults>  trigtagTok;
	//edm::EDGetTokenT<edm::View<pat::TriggerResults>>  triggerresultsTok;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerNameExtractor::TriggerNameExtractor(const edm::ParameterSet& iConfig)
//:
//trigtag(iConfig.getUntrackedParameter<edm::InputTag>("trigtag")),
//trigtagTok(consumes<edm::TriggerResults>(trigtag))
//triggerresultsTok(consumes<edm::View<pat::TriggerResults>>(triggerresults))
{
   //now do what ever initialization is needed

  trigtagTok = consumes<edm::TriggerResults> (trigtag);

}


TriggerNameExtractor::~TriggerNameExtractor()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TriggerNameExtractor::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
//   using namespace edm;

//   edm::Handle<edm::View<pat::TriggerResults>> hltresults;
//   edm::Handle<edm::TriggerResults> gettrigname;
 //  iEvent.getByToken(trigtagTok, gettrigname);
//  const  edm::TriggerNames & triggerNames_ = iEvent.triggerNames(*hltresults);
//  const edm::TriggerNames& trigNames = iEvent.triggerNames(*gettrigname);
//   int ntrigs = hltresults->size();

//   for (int itrig = 0; itrig != ntrigs; ++itrig){
//	TString trigName = triggerNames_.triggerName(itrig);
//	std::cout<<"trigname: "<< trigName<< std::endl;
//	}


















 //   Handle<TrackCollection> tracks;
//    iEvent.getByToken(tracksToken_, tracks);
/*   for(TrackCollection::const_iterator itTrack = tracks->begin();
        itTrack != tracks->end();
        ++itTrack) {
      // do something with track parameters, e.g, plot the charge.
      // int charge = itTrack->charge();
    } */

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
TriggerNameExtractor::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TriggerNameExtractor::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriggerNameExtractor::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerNameExtractor);
