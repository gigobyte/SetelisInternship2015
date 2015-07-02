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
			//curr_byte_--;
			break;
		}
	}
}

void
VideoFile::setup() {
	set_file_size();
	read_file();
	find_first_syncbyte();
}

void
VideoFile::get_next_packet(Packet& p) {
	while(1) {
		p.push_back(*curr_byte_);

		if(*(++curr_byte_) == 0x47) {
			break;
		}
	}

	p.set_pid();
}