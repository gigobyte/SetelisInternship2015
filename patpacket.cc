#include <stdio.h>
#include <exception>

#include "patpacket.hh"

using namespace std;
typedef unsigned char byte;

void
PATPacket::parse_header(){
	table_id_ = read_byte();

	printf("table_id_: %X\n", table_id_);
	printf("section_length_: %X\n", section_length_);
	printf("transport_stream_id_: %X\n", transport_stream_id_);
	printf("current_next_indicator_: %X\n", current_next_indicator_);
	printf("section_number_: %X\n", section_number_);
	printf("last_section_number_: %X\n", last_section_number_);
}

byte
PATPacket::read_byte() {
	return buf_[pos_++];
}