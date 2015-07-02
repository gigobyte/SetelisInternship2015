#ifndef PACKET_H
#define PACKET_H

typedef unsigned char byte;

class Packet {
	byte* buf_;
	int size_;
	int pid_;
	int psi_;

public:
	Packet();
	~Packet();

	void push_back(byte& e);
	void pretty_print();
	void clear();
	void set_pid();
	void set_psi();
	int get_pid();
	int get_size();
	int valid();
};

#endif