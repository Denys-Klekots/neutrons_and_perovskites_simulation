#ifndef __SteppingAction_HH__
#define __SteppingAction_HH__

#include <G4UserSteppingAction.hh>

class GRAiNTIASteppingAction: public G4UserSteppingAction
{

public:

    GRAiNTIASteppingAction();
    virtual ~GRAiNTIASteppingAction();

    virtual void UserSteppingAction(const G4Step*);

};



#endif //__SteppingAction_HH__