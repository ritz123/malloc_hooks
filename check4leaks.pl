#!/usr/bin/env perl

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

# script to compare malloc and free

%mm = ();
%ff = ();
while(<>){
	$line = $_;
	chomp($line);

	# malloc
   	if ($line =~ /^==\s+m\s+\S+\s+ptr:\s+(\S+).*$/) {
		$mm{$1} = $line;
		next;
	}

	# free
	if ($line =~ /^==\s+f\s+ptr:\s+(\S+).*$/) {
		$mm_key = $1;
		if (exists($mm{$mm_key})){
			delete($mm{$mm_key});
		} else {
			# double delete
			$ff{$mm_key} = $line;
		}
		next;
	}

	# realloc
	if ($line =~ /^==\s+r\s+\S+\s+optr:\s+(\S+)\s+ptr:\s+(\S+).*$/) {
		delete($mm{$1});
		$mm{$2} = $line;
		next;
	}

}



print map { "$mm{$_}\n" } keys %mm;
print map { "$ff{$_}\n" } keys %ff;