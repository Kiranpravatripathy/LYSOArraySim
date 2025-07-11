#include "LYSOHit.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<LYSOHit>* LYSOHitAllocator = nullptr;

LYSOHit::LYSOHit() : edep(0.) {}
LYSOHit::~LYSOHit() {}

LYSOHit::LYSOHit(const LYSOHit& right) : G4VHit() {
    edep = right.edep;
}

const LYSOHit& LYSOHit::operator=(const LYSOHit& right) {
    edep = right.edep;
    return *this;
}

G4bool LYSOHit::operator==(const LYSOHit& right) const {
    return edep == right.edep;
}

void* LYSOHit::operator new(size_t) {
    if (!LYSOHitAllocator)
        LYSOHitAllocator = new G4Allocator<LYSOHit>;
    return LYSOHitAllocator->MallocSingle();
}

void LYSOHit::operator delete(void* hit) {
    LYSOHitAllocator->FreeSingle((LYSOHit*)hit);
}

