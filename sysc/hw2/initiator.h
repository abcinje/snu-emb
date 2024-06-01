#ifndef _INITIATOR_H_
#define _INITIATOR_H_

#include "systemc"
#include "mm.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"

using namespace tlm;
using namespace std;
using namespace sc_core;

class Initiator : public sc_module
{
public:
	SC_HAS_PROCESS(Initiator);
	Initiator(sc_module_name name, const unsigned int id);
	void initiator_thread();
	tlm_utils::simple_initiator_socket<Initiator> initiator_socket;
	tlm_sync_enum nb_transport_bw(tlm_generic_payload& trans, tlm_phase& phase, sc_time& t);
	tlm_generic_payload* gen_trans(bool is_read, uint64_t address, unsigned char* data);

private:
	uint64_t BASE_ADDR = 0;
  	const unsigned int DATA_SIZE = 64;
	const unsigned int TRANS_NUM = 4;

	mm m_mm;
	unsigned int id;
};

#endif
