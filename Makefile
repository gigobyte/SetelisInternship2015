all: mpeg

packet.o: packet.cc packet.hh
patpacket.o: patpacket.cc patpacket.hh packet.hh
videofile.o: videofile.cc videofile.hh packet.hh
main.o: main.cc packet.hh videofile.hh

mpeg: main.o packet.o videofile.o patpacket.o
	g++ main.o packet.o patpacket.o videofile.o -o mpeg

clean:
	rm -f *.o *~ mpeg