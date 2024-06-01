#ifndef _TOP_H_
#define _TOP_H_

#include "tlm.h"
#include "initiator.h"
#include "target.h"

class Top : public sc_core::sc_module
{
public:
	Top(sc_core::sc_module_name name);

private:
	Initiator *initiator; 
	Target *target;
};

#endif
