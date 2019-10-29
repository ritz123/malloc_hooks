# malloc_hooks
Malloc hooks for linux + gcc/g++ for multi-threaded application


Implements custom malloc() and free() with backtrace for easy debugging.
Uses pthread based mutex for multi threaded application.

If the environment variable MTRACE_FULL is defined a detailed backtrace will be provided with all symbols resolved. Output is written to STDERR.


This creates a dynamic library whch has to be linked into the calling program.
In the calling program call "mtrace()" and include "my_mtrace.h". Link the binary with LDFLAGS set to "-rdynamic". For c programs link the executable to libmy_mtrace.so and libpthread.so. For cpp programs link the executable to libmy_mtrace++.so, libmy_mtrace.so and libpthread.so



