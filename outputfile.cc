#include <stdio.h>
#include <inttypes.h>
using namespace std;

#include "outputfile.hh"
#include "packet.hh"

OutputFile::OutputFile(const char* filename)
: filename_(filename)
{
	file_ = fopen(filename_, "ab+");
	if(file_ == NULL) {
		fprintf(stderr, "fopen() failed\n");
	}
}

OutputFile::~OutputFile() {
	fclose(file_);
}

void
OutputFile::write_pat(Packet& pat) {
	fprintf(file_, "pat = {\n");
	fprintf(file_, "\ttable_id=%d, section_length=%d, transport_stream_id=%d\n",
					pat.table_id_, pat.section_length_, pat.transport_stream_id_);

	fprintf(file_, "\tversion_number=%d, current_next_indicator=%d, section_number=%d\n",
					pat.version_number_, pat.current_next_indicator_, pat.section_number_);

	fprintf(file_, "\tlast_section_number=%d\n", pat.last_section_number_);

	fprintf(file_, "\tpmts = {\n");

	uint16_t* pmt_ids = pat.get_pmt_ids();
	uint16_t* prog_nums = pat.get_program_numbers();

	for(int i = 0; i < pat.get_program_count(); i++) {
		fprintf(file_, "\t\t[%d,%d", pmt_ids[i], prog_nums[i]);
		if(prog_nums[i] == 0) {
			fprintf(file_, " (nit)]\n");
		} else {
			fprintf(file_, "]\n");
		}
	}

	fprintf(file_, "\t}\n}\n\n");
}

void
OutputFile::write_pmt(Packet& p) {
	fprintf(file_, "pmt with pid %d = {\n", p.get_pid());
	fprintf(file_, "\ttable_id=%d, section_syntax_indicator=%d, section_length=%d\n",
					p.table_id_, p.section_syntax_indicator_, p.section_length_);

	fprintf(file_, "\tprogram_number=%d, version_number=%d, current_next_indicator=%d\n",
					p.program_number_, p.version_number_, p.current_next_indicator_);

	fprintf(file_, "\tsection_number=%d, last_section_number=%d, pcr_pid=%d, program_info_length=%d\n",
					p.section_number_, p.last_section_number_, p.pcr_pid_, p.program_info_length_);

	fprintf(file_, "\tstreams = {\n");

	uint16_t* epids        = p.get_elementary_pids();
	uint16_t* infolens     = p.get_es_info_lengths();
	uint16_t* stream_types = p.get_stream_types();

	for(int i = 0; i < p.get_program_count(); i++) {
		fprintf(file_, "\t\tstream_type=%d, elem_pid=%d, es_info_len=%d\n",
						stream_types[i], epids[i], infolens[i]);
	}

	fprintf(file_, "\t}\n}\n\n");
}