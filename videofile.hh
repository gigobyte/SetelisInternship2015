#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include "packet.hh"

typedef unsigned char byte;

class VideoFile {
	const char* filename_;
	byte* buf_;
	byte* curr_byte_;
	FILE* file_ = NULL;
	Packet pat_;

	long end_;
	int position_;

public:
	VideoFile(const char* filename);
	~VideoFile();

	void set_file_size();
	void read_file();
	void find_first_syncbyte();
	void setup();
	void get_next_packet(Packet& p);
	void reset_packet_counter();
	void set_pat();
	Packet& get_pat();
};

#endif