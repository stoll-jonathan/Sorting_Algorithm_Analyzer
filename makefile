driver: driver.o
	g++ driver.o -o driver

driver.o: driver.cpp sorter.cpp
	g++ -c driver.cpp

clean_csv:
	rm *.csv

clean:
	rm *.o driver