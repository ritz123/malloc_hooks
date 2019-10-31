#!/usr/bin/env perl
# script to compare malloc and free

%mm = ();
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
		delete($mm{$1});
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