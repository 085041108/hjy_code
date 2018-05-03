
.PHONY: all
all: mysql_query

CC = g++
PATHL = $(PWD)/../bin/

#LIBS =  -L/usr/lib/mysql -lmysqlclient -lpthread -ldl -lrt
INCLUDES = -I/usr/local/mysql-5.6.24-linux-glibc2.5-x86_64/include

LIBS = -L/usr/local/mysql-5.6.24-linux-glibc2.5-x86_64/lib -lmysqlclient -ldl -rdynamic

c_libsrcs = $(wildcard ./*.c)
cplus_libsrcs = $(wildcard ./*.cpp)

c_libobjs = $(c_libsrcs:.c=.o)
cplus_libobjs = $(cplus_libsrcs:.cpp=.o)


CPPFLAGS = -O0 -w -g -c -Wall

%.o: %.cpp
	$(CC) $(INCLUDES) $(CPPFLAGS) -o $@ $<
%.o: %.c
	gcc $(INCLUDES) $(CPPFLAGS) -o $@ $<

mysql_query: $(c_libobjs) $(cplus_libobjs)
	$(CC) $^ -o $(PATHL)$@  $(LIBS)
.PHONY: clean
clean:
	rm -f $(c_libobjs) $(cplus_libobjs) mysql_query






