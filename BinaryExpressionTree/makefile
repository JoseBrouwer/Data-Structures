proj4.x: BET.o proj4_driver.o
	g++6 BET.o proj4_driver.o -o proj4.x

BET.o: BET.cpp BET.h
	g++6 -c BET.cpp

proj4_driver.o: proj4_driver.cpp BET.h
	g++6 -c proj4_driver.cpp

clean:
	rm -rf *.o proj4.x
