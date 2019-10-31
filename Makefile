


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




all: test_mem_trace test_new_trace

CC:=gcc
CXX:=g++

CFLAGS:=-fPIC -g
CXXFLAGS:=-fPIC -g	-std=c++11	
LDFLAGS=-rdynamic

ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif



clean:
	rm -f *.o *.so test_mem_trace test_new_trace

libmem_trace.so: mem_trace.o
	$(CC) -rdynamic -shared $< -o $@ -lpthread

libmem_trace++.so: new_trace.o libmem_trace.so
	$(CXX) -rdynamic -shared $< -o $@ -lpthread -L. -lmem_trace

test_mem_trace: test_mem_trace.o libmem_trace.so
	$(CC) -rdynamic -g -L. $< -o $@ -lmem_trace 

test_new_trace: test_new_trace.o libmem_trace++.so
	$(CXX) -rdynamic -g -L. $< -o $@ -lmem_trace++ -lmem_trace -lpthread

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

install: install_lib install_header install_script
	@echo "Installed.."


install_lib: libmem_trace.so libmem_trace++.so
	install -d $(DESTDIR)$(PREFIX)/lib/
	install -m 644 $? $(DESTDIR)$(PREFIX)/lib/


install_header: mem_trace.h
	install -d $(DESTDIR)$(PREFIX)/include/
	install -m 644 $? $(DESTDIR)$(PREFIX)/include/

install_script: check4leaks.pl
	install -d $(DESTDIR)$(PREFIX)/bin/
	install -m 755 $? $(DESTDIR)$(PREFIX)/bin/

test:
	./run.sh
	./run++.sh