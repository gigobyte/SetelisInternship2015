#include <stdio.h>
#include <inttypes.h>
using namespace std;

#include "videofile.hh"
#include "packet.hh"

VideoFile::VideoFile(const char* filename)
: filename_(filename)
{
	file_ = fopen(filename_, "rb");
	if(file_ == NULL) {
		fprintf(stderr, "fopen() failed\n");
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
	buf_ = new uint8_t[end_];
	fread(buf_, end_, 1, file_);
	curr_byte_ = buf_;
}

void
VideoFile::find_first_syncbyte() {
	while(1) {
		if(*curr_byte_ == 0x47) {
			break;
		} else {
			curr_byte_++;
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
VideoFile::find_packet(Packet& p, uint16_t pid) {
	do {
		p.clear();
		get_next_packet(p);
	} while(p.get_pid() != pid);
}