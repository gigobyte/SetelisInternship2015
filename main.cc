#include <stdio.h>
#include <iostream>
using namespace std;

typedef unsigned char byte;

class TSPacket {
	byte* buf_;
	int size_;

public:
	TSPacket()
	: size_(0),
	  buf_(new byte[size_])
	{}

	~TSPacket() {
		delete[] buf_;
	}

	void push_back(byte& e) {
		buf_[size_++] = e;
	}

	void pretty_print() {
		for(int i = 0; i < size_; ++i) {
			printf("%X ", buf_[i]);
		}

		printf("\n");
	}

	int get_size() {
		return size_;
	}
};

class VideoFile {
	const char* filename_;
	byte* buf_;
	FILE* file_ = NULL;
	long pos_;
	long end_;

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
		pos_ = ftell(file_);
		fseek(file_, 0, 2);
		end_ = ftell(file_);
		fseek(file_, pos_, 0);
	}

	void read_file() {
		buf_ = new byte[end_];
		fread(buf_, end_, 1, file_);
	}

	class iterator {
		byte* e_;

		iterator(byte* ptr)
		: e_(ptr)
		{}

		friend class VideoFile;
	public:
		iterator operator++() {
			e_++;
			return *this;
		}

		bool operator==(const iterator& other) {
			return e_ == other.e_;
		}

		bool operator!=(const iterator& other) {
			return !operator==(other);
		}

		byte& operator*() {
			return *e_;
		}

		void find_first_syncbyte() {
			while(1) {
				if(*(operator++()) == 0x47) {
					break;
				}
			}
		}

		void push_packet(TSPacket& p) {
			while(1) {
				p.push_back(*e_);

				if(*(operator++()) == 0x47) {
					break;
				}
			}
		}
	};

	iterator begin() {
		return iterator(buf_);
	}

	iterator end() {
		return iterator(buf_ + end_);
	}
};

int main() {
	VideoFile vf("sample.ts");
	TSPacket p;

	vf.set_file_size();
	vf.read_file();

	VideoFile::iterator it = vf.begin();
	it.find_first_syncbyte();
	it.push_packet(p);
	
	p.pretty_print();
}
