#!/bin/bash

 export LD_LIBRARY_PATH=.
 export LD_BIND_NOW=1
 LD_DEBUG_OUTPUT=sym.log LD_DEBUG=bindings ./t_newtrace
