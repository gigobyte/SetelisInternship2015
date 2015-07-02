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
	pid_ = buf_[1] + buf_[2];
}

int
Packet::get_pid() {
	return pid_;
}

int
Packet::get_size() {
	return size_;
}