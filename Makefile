
all: t_mtrace

CC:=gcc

clean:
	rm -f *.o *.so t_mtrace

libmy_mtrace.so: my_mtrace.o
	$(CC) -shared $< -o $@ -lpthread

t_mtrace: t_mtrace.o libmy_mtrace.so
	$(CC) -L. $< -o $@ -lmy_mtrace -lpthread

%.o: %.c
	$(CC) -g -fPIC -c $(CFLAGS) $(CPPFLAGS) $< -o $@

