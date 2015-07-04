#include <stdio.h>
#include <iostream>

#include "packet.hh"
#include "videofile.hh"
using namespace std;

int main() {
	VideoFile vf("sample.ts");
	vf.setup();

	Packet pat;
	vf.find_pat(pat);

	//pat.pretty_print();
	pat.parse();
}