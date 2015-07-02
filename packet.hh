#ifndef PACKET_H
#define PACKET_H

typedef unsigned char byte;

class Packet {
	byte* buf_;
	int size_;
	int pid_;

public:
	Packet();
	~Packet();

	void push_back(byte& e);
	void pretty_print();
	void clear();
	void set_pid();
	int get_pid();
	int get_size();
};

#endif