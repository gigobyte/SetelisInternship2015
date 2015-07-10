#ifndef PACKET_H
#define PACKET_H

#include <inttypes.h>

class Packet {
	int size_;
	int psi_;
	int program_count_;

	uint8_t*  buf_;
	uint16_t* program_nums_;
	uint16_t* pmt_ids_;
	uint16_t* elementary_pids_;
	uint16_t* es_info_lengths_;
	uint16_t* es_descriptors_;
	uint16_t* stream_types_;

	uint8_t  nit_;
	uint16_t  pid_;

public:
	uint8_t  table_id_;
	uint8_t  section_syntax_indicator_;
	uint8_t  section_number_;
	uint8_t  last_section_number_;
	uint8_t  current_next_indicator_;
	uint8_t  transport_stream_id_;
	uint8_t  version_number_;
	uint16_t section_length_;
	uint16_t program_number_;
	uint16_t pcr_pid_;
	uint16_t program_info_length_ ;

	Packet();
	~Packet();

	void push_back(uint8_t& e);
	void pretty_print();
	void clear();
	void set_pid();
	void set_pid(uint16_t pid);
	void set_psi();
	void parse();
	int  get_pid() const;
	int  get_size() const;
	int  get_program_count() const;
	int  valid();
	uint8_t operator[](int index);
	uint16_t* get_program_numbers() const;
	uint16_t* get_pmt_ids() const;
	uint16_t* get_elementary_pids() const;
	uint16_t* get_es_info_lengths() const;
	uint16_t* get_stream_types() const;
};

#endif