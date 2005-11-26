#ifndef CaloTrkProcessing_H
#define CaloTrkProcessing_H

#include "DetectorDescription/Core/interface/DDsvalues.h"
#include "SimG4Core/Notification/interface/Observer.h"
#include "SimG4Core/SensitiveDetector/interface/SensitiveCaloDetector.h"

#include "G4VTouchable.hh"

#include <map>
#include <vector>
#include <string>
#include <iostream>

class BeginOfEvent;
class EndOfTrack;
class G4Step;

class CaloTrkProcessing : public SensitiveCaloDetector, 
			  public Observer<const BeginOfEvent *>,
			  public Observer<const EndOfTrack *>, 
			  public Observer<const G4Step *> {

public:

  CaloTrkProcessing(G4String aSDname, const DDCompactView & cpv,
		    edm::ParameterSet const & p);
  virtual ~CaloTrkProcessing();
  virtual void             Initialize(G4HCofThisEvent * ) {}
  virtual void             clearHits() {}
  virtual bool             ProcessHits(G4Step * , G4TouchableHistory * ) {
    return true;
  }
  virtual uint32_t         setDetUnitId(G4Step * step) {return 0;}
  virtual void             EndOfEvent(G4HCofThisEvent * ) {}
  void                     fillHits(edm::PCaloHitContainer&, std::string ) {}

private:

  void                     update(const BeginOfEvent * evt);
  void                     update(const EndOfTrack * trk);
  void                     update(const G4Step *);
  std::vector<std::string> getNames(G4String, const DDsvalues_type&);
  bool                     isItCalo(std::string);
  bool                     isItInside(std::string);

  // Utilities to get detector levels during a step
  int                      detLevels(const G4VTouchable*) const;
  G4String                 detName(const G4VTouchable*, int, int) const;
  void                     detectorLevel(const G4VTouchable*, int&, int*,
					 G4String*) const;

  int                      verbosity;
  bool                     testBeam;
  double                   eMin;
  int                      lastTrackID;
  std::vector<std::string> caloNames;
  std::vector<std::string> insideNames;

};

#endif








