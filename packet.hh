#ifndef PACKET_H
#define PACKET_H

#include <inttypes.h>

class Packet {
	int size_;
	int psi_;
	int program_count_;

	uint8_t* buf_;
	uint8_t* program_nums;
	uint16_t* pmts;

	uint8_t pid_;
	uint8_t table_id_;
	uint8_t section_syntax_indicator_;
	uint8_t section_length_;
	uint8_t section_number_;
	uint8_t last_section_number_;
	uint8_t current_next_indicator_;
	uint8_t transport_stream_id_;
	uint8_t version_number_;

public:
	Packet();
	~Packet();

	void push_back(uint8_t& e);
	void pretty_print();
	void clear();
	void set_pid();
	void set_psi();
	void parse();
	int get_pid();
	int get_size();
	int valid();
	uint8_t operator[](int index);
};

#endif