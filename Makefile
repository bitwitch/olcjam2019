LIBRARIES = -framework Cocoa -framework Quartz -framework OpenGL -lcocoawindowing_s -lpng
LIBDIR = -L ./bin
INCLUDEDIR = -I ./include

all:
	clang++ -arch x86_64 -std=c++14 -O2 -Wall $(LIBRARIES) $(LIBDIR) $(INCLUDEDIR) *.cpp -o game
clean:
	-rm game
