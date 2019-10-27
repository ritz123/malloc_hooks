
all: t_mtrace t_newtrace

CC:=gcc
CXX:=g++

CFLAGS:=-fPIC -g
CXXFLAGS:=-fPIC -g	-std=c++11	
LDFLAGS=-rdynamic

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
