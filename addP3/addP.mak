

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

addPLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =  -fopenmp	-O2 -g -Wall -fmessage-length=0 -I$(addPLIB_PATH)include -I$(EZ_PATH)boost

OBJS = addP.o addPIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :
 

#END OF USER MAKEFILE OPTIONS

TARGET =	addP

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(addPLIB_PATH)/libeasea.a $(EZ_PATH)boost/program_options.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp addP.png addP.dat addP.prm addP.mak Makefile addP.vcproj addP.csv addP.r addP.plot addP.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp addP.png addP.dat addP.prm addP.mak Makefile addP.vcproj addP.csv addP.r addP.plot addP.pop
endif

