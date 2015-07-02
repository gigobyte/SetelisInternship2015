#include <stdio.h>
#include <iostream>
<<<<<<< HEAD

#include "packet.hh"
#include "videofile.hh"
using namespace std;


=======
using namespace std;

typedef unsigned char byte;

class Packet {
	byte* buf_;
	int size_;
	int pid_;

public:
	Packet()
	: size_(0),
	  buf_(new byte[188])
	{}

	~Packet() {
		delete[] buf_;
	}

	void push_back(byte& e) {
		buf_[size_++] = e;
	}

	void pretty_print() {
		printf("PID: %d\n\n", pid_);

		for(int i = 0; i < size_; ++i) {
			printf("%X ", buf_[i]);
		}

		printf("\n");
	}

	void clear() {
		delete[] buf_;
		size_ = 0;
		buf_ = new byte[188];
	}

	void set_pid() {
		pid_ = buf_[2];
	}

	int get_pid() {
		return pid_;
	}

	int get_size() {
		return size_;
	}
};

class VideoFile {
	const char* filename_;
	byte* buf_;
	byte* curr_byte_;
	FILE* file_ = NULL;

	long end_;
	int position_;

public:
	VideoFile(const char* filename)
	: filename_(filename)
	{
		file_ = fopen(filename_, "rb");
		if(file_ == NULL) {
			cerr << "fopen() failed" << endl;
		}
	}

	~VideoFile() {
		delete[] buf_;
		fclose(file_);
	}

	void set_file_size() {
		long pos_ = ftell(file_);
		fseek(file_, 0, 2);
		end_ = ftell(file_);
		fseek(file_, pos_, 0);
	}

	void read_file() {
		buf_ = new byte[end_];
		fread(buf_, end_, 1, file_);
		curr_byte_ = buf_;
	}

	void find_first_syncbyte() {
		while(1) {
			if(*(++curr_byte_) == 0x47) {
				//curr_byte_--;
				break;
			}
		}
	}

	void setup() {
		set_file_size();
		read_file();
		find_first_syncbyte();
	}

	void get_next_packet(Packet& p) {
		while(1) {
			p.push_back(*curr_byte_);

			if(*(++curr_byte_) == 0x47) {
				break;
			}
		}

		p.set_pid();
	}
};
>>>>>>> origin/master

int main() {
	VideoFile vf("sample.ts");
	Packet p;

	vf.setup();

	vf.get_next_packet(p);

	p.pretty_print();
}
