#include "top.h"

using namespace sc_core;
using namespace tlm;

SC_HAS_PROCESS(Top);
Top::Top(sc_module_name name)
: sc_module(name)
{
	initiator = new Initiator("m_initiator", 0);
	target = new Target("m_target", 0);

	initiator->initiator_socket.bind(target->target_socket);	
}
