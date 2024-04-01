#ifndef _TARGET_H_
#define _TARGET_H_

#include "systemc"
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"

using namespace tlm;
using namespace std;
using namespace sc_core;

class Target : public sc_module
{
public:
	SC_HAS_PROCESS(Target);
	Target(sc_core::sc_module_name name, const unsigned int id);
	tlm_utils::simple_target_socket<Target> target_socket;
	tlm_sync_enum nb_transport_fw(tlm_generic_payload& trans, tlm_phase& phase, sc_time& t);
	void send_response(tlm_generic_payload& trans);

private:
	unsigned int id;
	const unsigned int DATA_SIZE = 64;
	const unsigned int TRANS_NUM = 4;
	unsigned char *memory_data;
};

#endif
