#pragma once
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"

class LYSOHit : public G4VHit {
public:
    LYSOHit();
    virtual ~LYSOHit();
    LYSOHit(const LYSOHit&);
    const LYSOHit& operator=(const LYSOHit&);
    G4bool operator==(const LYSOHit&) const;

    void* operator new(size_t);
    void operator delete(void*);

    void SetEdep(G4double val) { edep = val; }
    G4double GetEdep() const { return edep; }

private:
    G4double edep;
};

typedef G4THitsCollection<LYSOHit> LYSOHitsCollection;

