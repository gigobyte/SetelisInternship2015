all: mpeg

packet.o: packet.cc packet.hh
videofile.o: videofile.cc videofile.hh packet.hh
outputfile.o: outputfile.cc outputfile.hh packet.hh
main.o: main.cc packet.hh videofile.hh outputfile.hh

mpeg: main.o packet.o videofile.o outputfile.o
	g++ main.o packet.o videofile.o outputfile.o -o mpeg

clean:
	rm -f *.o *~ mpeg