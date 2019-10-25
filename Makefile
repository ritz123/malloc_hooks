
all: t_mtrace

CC:=gcc

clean:
	rm -f *.o *.so t_mtrace

libmy_malloc.so: my_malloc.o
	$(CC) -shared $< -o $@ -lpthread

t_mtrace: t_mtrace.o libmy_malloc.so
	$(CC) -L. $< -o $@ -lmy_malloc -lpthread

%.o: %.c
	$(CC) -g -fPIC -c $(CFLAGS) $(CPPFLAGS) $< -o $@

