# Compilation directives
CC = gcc
CCFLAGS = -I/usr/local/include/luajit-2.0 -L/usr/local/lib/ -O2 -Wall -Os -lluajit-5.1 -lz -ldl -lm -pagezero_size 10000 -image_base 100000000

OBJS = main.o
TARGET = test

#gcc -O2 -Wall -Wl, -o test main.cpp main.o -I/usr/local/include/luajit-2.0 -L/usr/local/lib/ -lluajit-5.1 -lm -ldl -pagezero_size 10000 -image_base 1

mingw linux macosx: $(OBJS)
	 	$(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ $<

# %.o: %.lua
# 	luajit -b $@

clean:
	rm -f $(OBJS) $(TARGET)

# luamain.o: script.lua
test: C++/main.cpp \
	C++/main.o