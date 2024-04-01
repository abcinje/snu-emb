#include "top.h"

using namespace sc_core;
using namespace tlm;

SC_HAS_PROCESS(Top);
Top::Top(sc_module_name name)
: sc_module(name)
{
	initiator = new Initiator*[2];
	target = new Target("m_target", 0);
	ic = new Interconnector("m_ic", 0);

	for (int i = 0; i < 2; i++) {
		string module_name = "m_initiator" + to_string(i);
		initiator[i] = new Initiator(module_name.c_str(), i);
	}

	// TODO: Write your code (bind the modules)
}
