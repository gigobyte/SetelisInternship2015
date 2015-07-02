#include <iostream>
#include <stdio.h>
using namespace std;

#include "videofile.hh"
#include "packet.hh"

typedef unsigned char byte;

VideoFile::VideoFile(const char* filename)
: filename_(filename)
{
	file_ = fopen(filename_, "rb");
	if(file_ == NULL) {
		cerr << "fopen() failed" << endl;
	}
}

VideoFile::~VideoFile() {
	delete[] buf_;
	fclose(file_);
}

void
VideoFile::set_file_size() {
	long pos_ = ftell(file_);
	fseek(file_, 0, 2);
	end_ = ftell(file_);
	fseek(file_, pos_, 0);
}

void
VideoFile::read_file() {
	buf_ = new byte[end_];
	fread(buf_, end_, 1, file_);
	curr_byte_ = buf_;
}

void
VideoFile::find_first_syncbyte() {
	while(1) {
		if(*(++curr_byte_) == 0x47) {
			break;
		}
	}
}

void
VideoFile::setup() {
	set_file_size();
	read_file();
	find_first_syncbyte();
	set_pat();
}

void
VideoFile::get_next_packet(Packet& p) {
	for(int i = 0; i < 188; ++i, ++curr_byte_) {
		p.push_back(*curr_byte_);
	}

	p.set_pid();
}

void
VideoFile::reset_packet_counter() {
	curr_byte_ = buf_;
}

void
VideoFile::set_pat() {
	while(pat_.get_pid() != 0) {
		pat_.clear();
		get_next_packet(pat_);
	}

	reset_packet_counter();
}

Packet&
VideoFile::get_pat() {
	return pat_;
}