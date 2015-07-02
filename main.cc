#include <stdio.h>
#include <iostream>

#include "packet.hh"
#include "videofile.hh"
using namespace std;



int main() {
	VideoFile vf("sample.ts");
	Packet p;

	vf.setup();

	vf.get_next_packet(p);

	p.pretty_print();
}
