#include "initiator.h"

SC_HAS_PROCESS(Initiator);
Initiator::Initiator(sc_module_name name, const unsigned int id)
: sc_module(name), id(id)
{
	initiator_socket.register_nb_transport_bw(this, &Initiator::nb_transport_bw);
	SC_THREAD(initiator_thread);
}

void Initiator::initiator_thread()
{
	tlm_generic_payload *trans;
	sc_dt::uint64 address = BASE_ADDR;

	// Write transaction
	for(int i = 0; i < TRANS_NUM; i++)
	{
		// Data
		unsigned char* data = new unsigned char[DATA_SIZE];
		for (int j = 0; j < DATA_SIZE; j++)
			data[j] = i+j;

		// Generate transaction
		trans = m_mm.allocate();
		trans->set_command(TLM_WRITE_COMMAND);
		trans->set_address(address);
		trans->set_data_length(DATA_SIZE);
		trans->set_data_ptr(data);

		cout << "[Initiator] Write request. (Addr:" << address << ")\n";
		cout << "> Time stamp:" << sc_time_stamp() << '\n';

		tlm_phase phase = BEGIN_REQ;
		sc_time delay = SC_ZERO_TIME;

		tlm_sync_enum status = initiator_socket->nb_transport_fw(*trans, phase, delay);
		assert(status == TLM_ACCEPTED);

		address++;

		// Add delay
		wait(5, SC_NS);
	}
}

tlm_sync_enum Initiator::nb_transport_bw(tlm_generic_payload& trans, tlm_phase& phase, sc_time& delay )
{
	sc_dt::uint64 address = trans.get_address();
	if (phase == BEGIN_RESP)
	{
		cout << "[Initiator] Write response received. (Addr:" << address << ")\n";

		// Send final phase transition to target
    	tlm_phase fw_phase = END_RESP;
    	sc_time delay = SC_ZERO_TIME;
      	tlm_sync_enum status = initiator_socket->nb_transport_fw(trans, fw_phase, delay);
		if (status == TLM_COMPLETED)
      	{
			free(&trans);
			cout << "[Initiator] Write transaction done.\n";
			cout << "> Time stamp:" << sc_time_stamp() << '\n';
      	}
	}
	return TLM_ACCEPTED;
  }
