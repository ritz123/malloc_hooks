#!/bin/bash

 export MALLOC_TRACE=/tmp/t
 export MALLOC_TRACE_LEVEL=15
 ./t_mtrace
 #mtrace ./t_mtrace $MALLOC_TRACE