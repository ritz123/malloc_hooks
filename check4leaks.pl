#!/usr/bin/env perl
# script to compare malloc and free

%mm = ();
while(<>){
	$line = $_;
	chomp($line);
   	if ($line =~ /^==\s+m\s+\S+\s+ptr:\s+(\S+).*$/) {
		$mm{$1} = $line;
		next;
	}

	if ($line =~ /^==\s+f\s+ptr:\s+(\S+).*$/) {
		delete($mm{$1});
		next;
	}
}



print map { "$mm{$_}\n" } keys %mm;