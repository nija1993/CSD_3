CC = g++
OFLAGS = -Wall
CFLAGS = -c
SOURCES = ARF.cpp Reserve_Stat.cpp ALU.cpp ROB.cpp RRF.cpp inst.cpp Store_Q.cpp Main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
ECOMMANDS = -shared -Wl,--hash-style=sysv -Wl,-Bsymbolic -Wl,--version-script=pin-2.13-65163-gcc.4.4.7-linux/source/include/pin/pintool.ver
EXECUTABLE = final

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)
	
.cpp.o : 
	$(CC) $(OFLAGS) $(CFLAGS) $< -o $@

clean : 
	rm -rf $(OBJECTS) $(EXECUTABLE)
