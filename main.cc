#include <stdio.h>

#include "packet.hh"
#include "videofile.hh"
#include "outputfile.hh"
using namespace std;

int main() {
	VideoFile vf("sample.ts");
	OutputFile out("out.txt");
	vf.setup();

	Packet pat;
	//"TS Packets containing PAT information
	//always have PID 0x0000."
	vf.find_packet(pat, 0x0);

	pat.parse();

	out.write_pat(pat);

	uint16_t* pmt_ids = pat.get_pmt_ids();
	uint16_t* prog_nums = pat.get_program_numbers();

	for(int i = 0; i < pat.get_program_count(); i++) {
		if(prog_nums[i] != 0) {
			Packet p;
			vf.find_packet(p, pmt_ids[i]);
			p.parse();
			out.write_pmt(p);
			p.clear();
		}
	}
}