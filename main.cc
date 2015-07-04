#include <stdio.h>
#include <iostream>

#include "packet.hh"
#include "patpacket.hh"
#include "videofile.hh"
using namespace std;

int main() {
	VideoFile vf("sample.ts");
	vf.setup();

	PATPacket pat;

	do {
		pat.clear();
		vf.get_next_packet(pat);
	} while(pat.get_pid() != 0x0);

	pat.pretty_print();
	pat.parse_header();
}