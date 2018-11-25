#!/bin/bash
for pin in {0..2}
do
	gpio mode $pin out
	gpio write $pin 0
done
arg='./tempread'
	echo $#
while (("$#"));do
    echo $# $1
    arg=$arg' '$1
	shift
done
echo $arg
s=(`$arg`)
c=${s[${#s[@]}-1]}
while [ 1 == 1 ];do
	s=(`$arg`)
    t=${s[${#s[@]}-1]}
    if [ $t -gt $((c+1000)) ] && [ $t -le $((c+2000)) ];then
	    echo "1up current is: $t star is: $c"
        gpio write 0 1
        gpio write 1 0
        gpio write 2 0
    elif [ $t -gt $((c+2000)) ] && [ $t -le $((c+3000)) ];then
	echo "2up current is: $t star is: $c"
        gpio write 0 1
        gpio write 1 1
        gpio write 2 0
    elif [ $t -gt $((c+3000)) ];then
            echo "3up current is: $t star is: $c"
        gpio write 0 1
        gpio write 1 1
	gpio write 2 1
	else
        	echo "0up $t $c"
        gpio write 0 0
        gpio write 1 0
        gpio write 2 0
	fi
done
