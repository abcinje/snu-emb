#include "target.h"

SC_HAS_PROCESS(Target);
Target::Target(sc_module_name name, const unsigned int id)
: sc_module(name), id(id)
{
	target_socket.register_nb_transport_fw(this, &Target::nb_transport_fw);
	count = 0;
}

tlm_sync_enum Target::nb_transport_fw(tlm_generic_payload &trans, tlm_phase& phase, sc_time &delay)
{
	if (phase == BEGIN_REQ)
		send_response(trans);
	else if (phase == END_RESP)
	{
		count++;
		if (count == TRANS_NUM)
			return TLM_COMPLETED;
	}
	return TLM_ACCEPTED;
}

void Target::send_response(tlm_generic_payload& trans)
{
	sc_dt::uint64 address = trans.get_address();
	unsigned int length = trans.get_data_length();
	unsigned char* data = trans.get_data_ptr();
	sc_time delay = SC_ZERO_TIME;

    tlm_phase phase = END_REQ;
	cout << "[Target] Write request received. (Addr:" << address << ")\n";
    tlm_sync_enum status = target_socket->nb_transport_bw(trans, phase, delay);
	assert(status == TLM_ACCEPTED);

	// Process with the data
	for (int i = 0; i < length; i++)
		data[i]++;

    phase = BEGIN_RESP;
	cout << "[Target] Write response. (Addr:" << address << ")\n";

    status = target_socket->nb_transport_bw(trans, phase, delay);
	assert(status == TLM_ACCEPTED);
}
