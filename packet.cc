#include <stdio.h>
#include <inttypes.h>

#include "packet.hh"

using namespace std;
typedef uint8_t byte;

Packet::Packet()
: size_(0),
  buf_(new uint8_t[188]),
  pid_(-1),
  program_count_(0)
{}

Packet::~Packet() {
	delete[] buf_;
}

void
Packet::push_back(uint8_t& e) {
	buf_[size_++] = e;
}

void
Packet::pretty_print() {
	for(int i = 0; i < size_; ++i) {
		printf("%X ", buf_[i]);
	}

	printf("\n");
}

void
Packet::clear() {
	delete[] buf_;
	size_ = 0;
	buf_ = new uint8_t[188];
}

void
Packet::set_pid() {
	//pid_ = (buf_[1] << 8) | (buf_[2] & 0xff);
	pid_ = ((buf_[1] & 31) << 8 | buf_[2]);
}

void
Packet::set_psi() {
	psi_ = (buf_[1] & 0x40) >> 6;
}

int
Packet::get_pid() {
	return pid_;
}

int
Packet::get_size() {
	return size_;
}

int
Packet::valid() {
	return buf_[0] == 0x47;
}

uint8_t
Packet::operator[](int index) {
	return buf_[index];
}

void
Packet::parse() {
	if(pid_ == 0x0) {
		table_id_ = buf_[5];
		section_length_ = buf_[7];
		transport_stream_id_ = (buf_[8] << 8 ) | (buf_[9] & 0xff);

		version_number_ = (buf_[10] << 2);
		version_number_ = version_number_ >> 3;

		current_next_indicator_ = buf_[10] << 7;
		current_next_indicator_ = current_next_indicator_ >> 7;

		section_number_ = buf_[11];
		last_section_number_ = buf_[12];

		int stop = 0;
		while(buf_[stop++] != 0xFF);

		printf("table_id_ = %d\n", table_id_);
		printf("section_length_ = %d\n", section_length_);
		printf("transport_stream_id_ = %d\n", transport_stream_id_);
		printf("version_number_ = %d\n", version_number_);
		printf("current_next_indicator_ = %d\n", current_next_indicator_);
		printf("section_number_ = %d\n", section_number_);
		printf("last_section_number_ = %d\n", last_section_number_);
		printf("\n\n");

		for(int i = 13; i < stop-8; i+=4, program_count_++);

		pmts = new uint16_t[program_count_];
		program_nums = new uint8_t[program_count_];
		int j = 0;

		for(int i = 13; i < stop-8; i+=4, j++) {
			pmts[j] = static_cast<uint16_t>(buf_[i+3]) | (static_cast<uint16_t>(buf_[i+2] & 0x1F) << 8);
			program_nums[j] = (buf_[i] << 8 ) | (buf_[i+1] & 0xff);
		}

		printf("CRC: %X %X %X %X\n", buf_[stop-5], buf_[stop-4],
									 buf_[stop-3], buf_[stop-2]);
	}
}