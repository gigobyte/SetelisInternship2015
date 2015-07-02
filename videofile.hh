#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include "packet.hh"

typedef unsigned char byte;

class VideoFile {
	const char* filename_;
	byte* buf_;
	byte* curr_byte_;
	FILE* file_ = NULL;

	long end_;
	int position_;

public:
	VideoFile(const char* filename);
	~VideoFile();

	void set_file_size();
	void read_file();
	void find_first_syncbyte();
	void setup();
	int get_next_packet(Packet& p);
	void reset_packet_counter();
	void pretty_print();
};

#endif