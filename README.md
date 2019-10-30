# malloc_hooks
Malloc hooks for linux + gcc/g++ for multi-threaded application


Implements custom malloc() and free() with backtrace for easy debugging.
Uses pthread based mutex for multi threaded application.

If the environment variable MTRACE_FULL is defined a detailed backtrace
will be provided with all symbols resolved. Output is written to STDERR.


This creates a dynamic library whch has to be linked into the calling program.
In the calling program call "enable_mem_trace()" and include "mem_trace.h".
Link the binary with LDFLAGS set to "-rdynamic". For c programs link the executable
to libmem_trace.so and libpthread.so. For cpp programs link the executable to
libmem_trace++.so, libmem_trace.so and libpthread.so



