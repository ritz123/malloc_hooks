#!/bin/bash

TOP=$(dirname $0)
[ $# != 3 ] && echo "Usage: $0 <memeory-report.txt> <exec-path> <exec-pid>" && exit 1
REPORT=$1
BINARY=$2
PID_BIN=$3
T_F=/tmp/resolve_symbols_$$.txt
LEAKS=/tmp/check4leaks_$$.txt
rm -f ${T_F}
$TOP/check4leaks.pl ${REPORT} > ${LEAKS}
$TOP/resolve_symbols.pl ${LEAKS} > ${T_F}


gdb -x ${T_F} -q -n -batch -p ${PID_BIN}  ${BINARY} 
rm -f ${T_F} ${LEAKS}