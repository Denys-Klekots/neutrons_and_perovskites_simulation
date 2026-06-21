#ifndef __ActionInitialization_hh__
#define __ActionInitialization_hh__

#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization();
    virtual ~ActionInitialization();

    virtual void Build() const;
    virtual void BuildForMaster() const;
};

#endif // __ActionInitialization_hh__

    
