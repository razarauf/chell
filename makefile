# specify the compiler
#CC   = cc  # this is the cross platform standard C compiler
CXX  = g++
#CXX  = g++  # this is the GNU C++ compiler
#CXX = CC   # Solaris C++ compiler on hercules

FILE = chell

all : main

# Separate compilation to build object files
main.o : main.c $(FILE).h 
	$(CXX) -c main.c

$(FILE).o : $(FILE).c $(FILE).h 
	$(CXX) -c $(FILE).c

# Linking
#demo is a target which depends upon main.o and $(FILE).o 
main : main.o $(FILE).o
	$(CXX) main.o $(FILE).o -o main

# Testing
check : all
	./main

# Clean up all build targets so that one may get a clean build
clean :
	rm -f *.o main

