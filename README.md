# malloc_hooks
Malloc hooks for linux + gcc/g++ for multi-threaded application

Implements custom malloc() and free() with backtrace for easy debugging.
Uses pthread based mutex for multi threaded application. Output is written to STDERR.

This creates a dynamic library whch has to be linked into the calling program.
In the calling program call "enable_mem_trace()" and include "mem_trace.h".
Link the binary with LDFLAGS set to "-rdynamic". For c programs link the 
executable to libmem_trace.so and libpthread.so. For cpp programs link the 
executable to libmem_trace++.so, libmem_trace.so and libpthread.so


The script resolve_symbols.sh can be used to parse the output file and look 
for any possible memory leaks along with the stack trace of the location 
where memory was allocated. Please run this script on the system where the 
process being analysed is running.





