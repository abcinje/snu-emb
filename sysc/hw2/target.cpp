#include "target.h"

Target::Target(sc_module_name name, const unsigned int id)
: sc_module(name), id(id)
{
	target_socket.register_nb_transport_fw(this, &Target::nb_transport_fw);
	memory_data = new unsigned char[DATA_SIZE*1000];
}

tlm_sync_enum Target::nb_transport_fw(tlm_generic_payload &trans, tlm_phase& phase, sc_time &delay)
{
	if (phase == BEGIN_REQ)
		send_response(trans);

	return TLM_ACCEPTED;
}

void Target::send_response(tlm_generic_payload& trans)
{
	sc_dt::uint64 address = trans.get_address();
	unsigned int length = trans.get_data_length();

	tlm_phase phase;
	sc_time delay = SC_ZERO_TIME;

	// TODO: Write your code
	// nb_transport_bw to the Interconnector (phase = END_REQ)
	phase = END_REQ;
	target_socket->nb_transport_bw(trans, phase, delay);

	// Write response
	if (trans.get_command() == TLM_WRITE_COMMAND)
		// TODO: Write your code
		// Copy the trans data to memory_data (Hint: Use trans.get_data_ptr() function)
		memcpy(&memory_data[address*length], trans.get_data_ptr(), length);

	// Read response
	else
		trans.set_data_ptr(&memory_data[address*length]);

	// TODO: Write your code
	// nb_transport_bw to the Interconnector (phase = BEGIN_RESP)
	phase = BEGIN_RESP;
	target_socket->nb_transport_bw(trans, phase, delay);
}