#ifndef _INTERCONNECTOR_H_
#define _INTERCONNECTOR_H_

#include "systemc"
#include "tlm.h"
#include "tlm_utils/multi_passthrough_initiator_socket.h"
#include "tlm_utils/multi_passthrough_target_socket.h"

using namespace std;
using namespace tlm;
using namespace sc_core;

class Interconnector: public sc_module
{
public:
    SC_HAS_PROCESS(Interconnector);
	Interconnector(sc_module_name name, const unsigned int id);
	tlm_utils::multi_passthrough_initiator_socket<Interconnector> initiator_socket;
	tlm_utils::multi_passthrough_target_socket<Interconnector> target_socket;

private:
	tlm_sync_enum nb_transport_fw(int id, tlm_generic_payload& trans, tlm_phase& phase, sc_time& t);
	tlm_sync_enum nb_transport_bw(int id, tlm_generic_payload& trans, tlm_phase& phase, sc_time& t);
	unsigned int id;
};

#endif