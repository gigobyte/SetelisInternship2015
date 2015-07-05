#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <inttypes.h>
#include "packet.hh"

class OutputFile {
	const char* filename_;
	FILE* file_ = NULL;

public:
	OutputFile(const char* filename);
	~OutputFile();
	void write_pat(Packet& pat);
	void write_pmt(Packet& pat);
};

#endif
