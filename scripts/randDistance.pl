$minRange = int($ARGV[0]);
$range = int($ARGV[1]);
$maxRange = $minRange + $range - 1;
open(INPUT, "<".$ARGV[2]) or die $!;
open(OUTPUT, ">".$ARGV[3]) or die $!;

print "Changing 9th DIMACS Implementation Challenge params...\nChange distance labels between nodes to random numbers...\n\nNew range:\t[$minRange\t:\t$maxRange]\nSource file:\t$ARGV[2]\nTarget file:\t$ARGV[3]\n\nStart processing...\n";

while($line = <INPUT>) {
	if ($line =~ /^(a (\d+) (\d+) (\d+))$/) {
		$out = "a ".$2." ".$3." ".int(rand($range)+$minRange)."\n";
		print OUTPUT $out
	} else {
		print OUTPUT $line
	}
}
print "Complete.\n";
close INPUT;
close OUTPUT;
