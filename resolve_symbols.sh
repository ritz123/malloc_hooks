#!/bin/bash
# MIT License

# Copyright (c) 2019 Biplab Sarkar

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

TOP=$(dirname $0)
[ $# != 3 ] && echo "Usage: $0 <memory-report.txt> <exec-path> <exec-pid>" && exit 1
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