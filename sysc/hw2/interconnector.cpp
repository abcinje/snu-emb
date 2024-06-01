#include "interconnector.h"

Interconnector::Interconnector(sc_module_name name, const unsigned int id)
: sc_module(name), id(id)
{
	initiator_socket.register_nb_transport_bw(this, &Interconnector::nb_transport_bw);
	target_socket.register_nb_transport_fw(this, &Interconnector::nb_transport_fw);
}

tlm_sync_enum Interconnector::nb_transport_fw(int id, tlm_generic_payload& trans, tlm_phase& phase, sc_time& t) {
	// TODO: Write your code
	initiator_socket->nb_transport_fw(trans, phase, t);

	return TLM_ACCEPTED;
}

tlm_sync_enum Interconnector::nb_transport_bw(int id, tlm_generic_payload& trans, tlm_phase& phase, sc_time& t) {
	// TODO: Write your code
	target_socket->nb_transport_bw(trans, phase, t);

	return TLM_ACCEPTED;
}
