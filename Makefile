
all: t_mtrace

CC:=gcc

clean:
	rm -f *.o t_mtrace

t_mtrace: t_mtrace.o
	$(CC) $< -o $@

%.o: %.c
	$(CC) -g -c $(CFLAGS) $(CPPFLAGS) $< -o $@