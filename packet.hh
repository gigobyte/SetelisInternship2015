#ifndef PACKET_H
#define PACKET_H

#include <inttypes.h>

typedef uint8_t byte;

class Packet {
	byte* buf_;
	int size_;
	byte pid_;
	int psi_;
	byte table_id_;
	byte section_syntax_indicator_;
	byte section_length_;
	byte section_number_;
	byte last_section_number_;
	byte current_next_indicator_;
	byte transport_stream_id_;
	byte version_number_;

public:
	Packet();
	~Packet();

	void push_back(byte& e);
	void pretty_print();
	void clear();
	void set_pid();
	void set_psi();
	void parse();
	int get_pid();
	int get_size();
	int valid();
	byte operator[](int index);
};

#endif