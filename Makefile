# wordfreq 

# wordfreq.sh
# Programmierbeispiel C++ 
# Erwin Nindl, 01.07.2014
# Email: <erwin@nindl.eu>


CC=g++
RM=rm -f
CFLAGS=-Wall -std=c++11 
LDFLAGS=
INCLUDE=
LIBS=-lboost_system -lboost_program_options -lboost_thread

#--------------------------------------------------------

OBJECTS    = main.o fileReader.o 
HEADER     = main.h myException.h fileReader.h 
EXECUTABLE = wordfreq 

#--------------------------------------------------------

all::   $(EXECUTABLE)

clean:  
	$(RM) $(OBJECTS)
	$(RM) $(EXECUTABLE)
	$(RM) *~

$(OBJECTS): $(HEADER) $(OBJECTS:.o=.cpp)
	-$(CC) -c $(CFLAGS) $(INCLUDE) $(OBJECTS:.o=.cpp)

$(EXECUTABLE): $(OBJECTS)
	-$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LIBS)

test:
	bash test.sh Sample2.txt Sample.txt Sample2.txt
