
all: t_mtrace t_newtrace

CC:=gcc
CXX:=g++

CFLAGS:=-fPIC -g
CXXFLAGS:=-fPIC -g	-std=c++11	

clean:
	rm -f *.o *.so t_mtrace t_newtrace

libmy_mtrace.so: my_mtrace.o
	ld -shared $< -o $@ -lpthread

libmy_mtrace++.so: my_new.o libmy_mtrace.so
	ld -shared $< -o $@ -lpthread -L. -lmy_mtrace

t_mtrace: t_mtrace.o libmy_mtrace.so
	$(CC) -L. $< -o $@ -lmy_mtrace 

t_newtrace: t_newtrace.o libmy_mtrace++.so
	$(CXX) -L. $< -o $@ -lmy_mtrace++ -lmy_mtrace -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@
