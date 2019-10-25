# malloc_hooks
Malloc hooks for linux + gcc based on 
https://stackoverflow.com/questions/17803456/an-alternative-for-the-deprecated-malloc-hook-functionality-of-glibc

Implemented custom malloc() and free() with backtrace for easy debugging.


This creates a dynamic library whch has to be linked into the calling program.
In the calling program call "mtrace()".

