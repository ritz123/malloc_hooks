# malloc_hooks
Malloc hooks for linux + gcc/g++ for multi-threaded application


Implements custom malloc() and free() with backtrace for easy debugging.
Uses pthread based mutex for multi threaded application.

If yhe environment variable MTRACE_FULL is defined a detailed backtrace will be provided with all symbols resolved. Out put is written to STDERR.


This creates a dynamic library whch has to be linked into the calling program.
In the calling program call "mtrace()" and include "my_mtrace.h". Link the binary with LDFLAGS set to "-rdynamic"



