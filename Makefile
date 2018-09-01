wideml:	$(patsubst %.cpp,%.o,$(wildcard *.cpp)) symbol.o
	g++ -std=c++11 -Wall -O2 -o $@ $^

%.o:	%.cpp	$(wildcard *.h)
	g++ -std=c++11 -Wall -O2 -o $@ -c $<

%.cpp:	%.re
	~/re2c-1.0.1/re2c $< > $@.tmp
	mv $@.tmp $@
