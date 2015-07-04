#ifndef PATPACKET_H
#define PATPACKET_H

#include "packet.hh"

typedef unsigned char byte;

class PATPacket: public Packet {
	byte* buf_;
	int size_;
	int pid_;
	int psi_;
	int pos_;
	byte table_id_;
	byte section_length_;
	byte transport_stream_id_;
	byte version_number_;
	byte current_next_indicator_;
	byte section_number_;
	byte last_section_number_;

public:
	void parse_header();
	byte read_byte();
};

#endif