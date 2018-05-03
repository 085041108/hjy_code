
.PHONY: all
all: mysql_server

CC = g++
PATHL = $(PWD)/../bin/

INCLUDES = -I/usr/local/mysql-5.6.24-linux-glibc2.5-x86_64/include -I/home/xzy/glog-master/src -I/usr/local/include/thrift/

LIBS = -L/usr/local/mysql-5.6.24-linux-glibc2.5-x86_64/lib -lmysqlclient -L/usr/local/lib -lglog -lthrift -ldl -rdynamic -L/home/xzy/jsoncpp-src-0.5.0/libs/linux-gcc-4.4.7 -ljson_linux-gcc-4.4.7_libmt

c_libsrcs = $(wildcard ./*.c)
cplus_libsrcs = $(wildcard ./*.cpp)
server_libsrcs = $(wildcard ../gen-cpp/*.cpp)

c_libobjs = $(c_libsrcs:.c=.o)
cplus_libobjs = $(cplus_libsrcs:.cpp=.o)
server_libobjs = $(server_libsrcs:.cpp=.o)


CPPFLAGS = -O0 -w -g -c -Wall

%.o: %.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS)  -o $@ $<
%.o: %.c
	gcc $(INCLUDES) $(CPPFLAGS) -o $@ $<

mysql_server: $(c_libobjs) $(cplus_libobjs) $(server_libobjs)
	$(CC) $^ -o $(PATHL)$@  $(LIBS)
.PHONY: clean
clean:
	rm -f $(c_libobjs) $(cplus_libobjs) $(server_libobjs) mysql_server






