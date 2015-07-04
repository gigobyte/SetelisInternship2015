#include <stdio.h>

#include "packet.hh"

using namespace std;
typedef unsigned char byte;

Packet::Packet()
: size_(0),
  buf_(new byte[188]),
  pid_(-1)
{}

Packet::~Packet() {
	delete[] buf_;
}

void
Packet::push_back(byte& e) {
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
	buf_ = new byte[188];
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

byte
Packet::operator[](int index) {
	return buf_[index];
}