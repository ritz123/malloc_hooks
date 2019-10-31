#!/usr/bin/env perl
# resolve symbols using gdb

while(<>) {
	$line = $_;
	chomp($line);

	# malloc
   	if ($line =~ /\[\s+(.*?)\]/) {
   		my $str = $1;
   		my @words = split /\s+/, $str;
   		print("echo $line\\n\n");
   		map {print("info symbol $_\n")} @words;
   		print("echo \\n\n")
	}

}

