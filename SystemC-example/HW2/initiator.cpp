#include "initiator.h"

Initiator::Initiator(sc_module_name name, const unsigned int id)
: sc_module(name), id(id)
{
	initiator_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);
	SC_THREAD(initiator_thread);
}

tlm_generic_payload* Initiator::gen_trans(bool is_read, uint64_t address, unsigned char* data) {
	tlm_generic_payload *trans;
	trans = m_mm.allocate();	
	trans->set_address(address);
	trans->set_data_length(DATA_SIZE);
	if (is_read)
		trans->set_command(TLM_READ_COMMAND);
	else {
		trans->set_command(TLM_WRITE_COMMAND);
		trans->set_data_ptr(data);
	}
	return trans;
}

void Initiator::initiator_thread()
{
	uint64_t w_addr = BASE_ADDR;
	uint64_t r_addr = BASE_ADDR;

	tlm_phase phase = BEGIN_REQ;
	sc_time delay = SC_ZERO_TIME;

	for(int i = 0; i < TRANS_NUM; i++)
	{
		// Write request
		if (id == 0) {
			// Data
			unsigned char* data = new unsigned char[DATA_SIZE];
			for (int j = 0; j < DATA_SIZE; j++)
				data[j] = i+j;

			// TODO: Write your code
			// Generate trans using gen_trans function and transport it to the Interconnector
			tlm_generic_payload *trans = gen_trans(false, w_addr, data);
			initiator_socket->nb_transport_fw(*trans, phase, delay);

			wait(5, SC_NS);
			w_addr++;
		}
		
		// Read request
		if (id == 1) {
			// TODO: Write your code
			// Generate trans using gen_trans function and transport it to the Interconnector
			tlm_generic_payload *trans = gen_trans(true, r_addr, nullptr);
			initiator_socket->nb_transport_fw(*trans, phase, delay);

			wait(5, SC_NS);
			r_addr++;
		}
	}
}

tlm_sync_enum Initiator::nb_transport_bw(tlm_generic_payload& trans, tlm_phase& phase, sc_time& delay)
{
	sc_dt::uint64 address = trans.get_address();

	if (trans.get_command() == TLM_WRITE_COMMAND) {
		if (phase == BEGIN_RESP)
		{
			// Send final phase transition to target
			phase = END_RESP;
			tlm_sync_enum status = initiator_socket->nb_transport_fw(trans, phase, delay);
		}
		return TLM_ACCEPTED;
	}
	else {
		if (phase == BEGIN_RESP)
		{
			cout << "[Initiator1] Read response received.\n";
			cout << "> Address:" << address << '\n';

			unsigned char *data = trans.get_data_ptr();
			for (int i = 0; i < 64; i++)
				cout << (int)data[i] << " ";
			cout << endl;

			// Send final phase transition to target
			phase = END_RESP;
			tlm_sync_enum status = initiator_socket->nb_transport_fw(trans, phase, delay);
		}
		return TLM_ACCEPTED;
	}
}