#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include <inttypes.h>
#include "packet.hh"

class VideoFile {
	const char* filename_;
	uint8_t* buf_;
	uint8_t* curr_byte_;
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
	void get_next_packet(Packet& p);
	void reset_packet_counter();
	void find_packet(Packet& p, uint16_t pid);
};

#endif
