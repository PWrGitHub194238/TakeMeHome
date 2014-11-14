print "Changing 9th DIMACS Implementation Challenge to GraphViz format...\n\nSource file:\t$ARGV[1]\nTarget file:\t$ARGV[2]\n\nStart processing...\n";
open(INPUT, "<".$ARGV[1]) or die $!;
open(OUTPUT, ">".$ARGV[2]) or die $!;
print OUTPUT "digraph G {\n";
while($line = <INPUT>) {
	if ($line =~ /^(a (\d+) (\d+) (\d+))$/) {
		$out = $2." -> ".$3." [ label = \"".$4."\"];";
		$line =~ s/$1/$out/;
		print OUTPUT "\t".$line
	}
}
print OUTPUT "}";
print "Complete.\n";
close INPUT;
close OUTPUT;
