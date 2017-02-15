GXX = g++
GXXFLAGS = -Wall -g -std=c++11

TS_GA: main.o ts_ga.o ts_genotype.o functions.o city.o
	$(GXX) $(GXXFLAGS) -o TS_GA main.o ts_ga.o ts_genotype.o functions.o city.o

main.o: main.cpp ts_ga.h
	$(GXX) $(GXXFLAGS) -c main.cpp

ts_ga.o: ts_ga.h city.h comparators.h functions.h
	$(GXX) $(GXXFLAGS) -c ts_ga.cpp

ts_genotype.o: ts_genotype.h functions.h
	$(GXX) $(GXXFLAGS) -c ts_genotype.cpp

functions.o: functions.h
	$(GXX) $(GXXFLAGS) -c functions.cpp

city.o: city.h
	$(GXX) $(GXXFLAGS) -c city.cpp
