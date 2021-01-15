#ifndef _mmapToAssy__h___
#define  _mmapToAssy__h___

typedef struct _DataLink DataLink;
struct _DataLink {
	uint8_t byte;
	DataLink* next;
};

typedef struct _Segment Segment;
struct _Segment {
	int segment_id;
	uint32_t starting_dest_address;
	uint32_t segment_length;
	DataLink* data_head;
	DataLink* data_tail;
	Segment* next;
};
Segment* makeSegment(int id, uint32_t starting_dest_addr);
void addDataLink(Segment* s, uint8_t data);




#endif
