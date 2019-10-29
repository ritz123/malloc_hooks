


# MIT License

# Copyright (c) 2019 Biplab Sarkar

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.




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