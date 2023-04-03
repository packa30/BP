CXX=g++
CXXFLAGS=-O2 -g -Wall -pedantic -std=c++11 -pthread
LDFLAGS=-Wl,-rpath=/usr/local/lib/gcc49/

all: mapping dos_attack dos_connect

mapping:standard.cpp dos_attack.cpp mapping.cpp attacks.cpp
	$(CXX) -DE_FIRST -o dosattack $(CXXFLAGS) $^

dos_attack: standard.cpp dos_attack.cpp mapping.cpp attacks.cpp
	$(CXX) -DE_SECOND -o mapping $(CXXFLAGS) $^

dos_connect: standard.cpp dos_attack.cpp mapping.cpp connectDoS.cpp attacks.cpp
	$(CXX) -DE_THIRD -o dosconnect $(CXXFLAGS) $^

clean:
	rm -f dosattacks
	rm -f mapping
	rm -f dosconnect
