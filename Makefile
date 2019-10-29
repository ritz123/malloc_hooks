
all: t_mtrace t_newtrace

CC:=gcc
CXX:=g++

CFLAGS:=-fPIC -g
CXXFLAGS:=-fPIC -g	-std=c++11	
LDFLAGS=-rdynamic

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif



clean:
	rm -f *.o *.so t_mtrace t_newtrace

libmy_mtrace.so: my_mtrace.o
	$(CC) -rdynamic -shared $< -o $@ -lpthread

libmy_mtrace++.so: my_new.o libmy_mtrace.so
	$(CXX) -rdynamic -shared $< -o $@ -lpthread -L. -lmy_mtrace

t_mtrace: t_mtrace.o libmy_mtrace.so
	$(CC) -rdynamic -g -L. $< -o $@ -lmy_mtrace 

t_newtrace: t_newtrace.o libmy_mtrace++.so
	$(CXX) -rdynamic -g -L. $< -o $@ -lmy_mtrace++ -lmy_mtrace -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

install: install_lib install_header
	@echo "Installed.."


install_lib: libmy_mtrace.so libmy_mtrace++.so
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $? $(DESTDIR)$(PREFIX)/lib/


install_header: my_mtrace.h
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 $? $(DESTDIR)$(PREFIX)/include/


test:
	./run.sh
	./run++.sh