all: tct nasa pdt

tct: TimeCode.cpp TimeCodeTests.cpp TimeCode.h
	g++ -Wall -g -O0 TimeCode.cpp TimeCodeTests.cpp -o tct

nasa: TimeCode.cpp NasaLaunchAnalysis.cpp TimeCode.h
	g++ -Wall -g -O0 TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa

pdt: TimeCode.cpp PaintDryTimer.cpp TimeCode.h
	g++ -Wall -g -O0 TimeCode.cpp PaintDryTimer.cpp -o pdt

clean:
	rm -f tct nasa pdt
