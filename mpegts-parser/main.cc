#include <stdio.h>

#include "packet.hh"
#include "videofile.hh"
#include "outputfile.hh"
using namespace std;

int main() {
	VideoFile vf("sample.ts");
	//OutputFile out("out.txt");
	vf.setup();

	Packet pat;
	vf.find_packet(pat, 0x0);

	pat.parse();

	//out.write_pat(pat);

	uint16_t* pmt_ids = pat.get_pmt_ids();
	uint16_t* prog_nums = pat.get_program_numbers();

	Packet pmt_p;
	Packet elem_p;

	for(int i = 0; i < pat.get_program_count(); i++) {
		if(prog_nums[i] != 0) {
			
			vf.find_packet(pmt_p, pmt_ids[i]);
			pmt_p.parse();
			
			uint16_t* elementary_pids = pmt_p.get_elementary_pids();

			printf("pr: %d\n", pmt_p.get_program_count());

			for(int j = 0; j < pmt_p.get_program_count(); j++) {
				vf.find_packet(elem_p, elementary_pids[j]);

				elem_p.pretty_print();
				printf("\n\n");
				elem_p.clear();
			}
		}
	}
}