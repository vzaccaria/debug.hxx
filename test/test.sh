#!/usr/bin/env bash 
srcdir=`dirname $0`
srcdir=`cd $srcdir; pwd`
dstdir=`pwd`

DEBUG_COLORS=no $srcdir/../bin/test &> $srcdir/out0.tmp 
DEBUG_COLORS=no DEBUG=main $srcdir/../bin/test &> $srcdir/out1.tmp 
DEBUG=main $srcdir/../bin/test &> $srcdir/out1c.tmp 
DEBUG_COLORS=no DEBUG=* $srcdir/../bin/test &> $srcdir/out2.tmp 
DEBUG_COLORS=no DEBUG=* $srcdir/../bin/test2 &> $srcdir/out3.tmp 
DEBUG_COLORS=no $srcdir/../bin/test4 &> $srcdir/out4.tmp
DEBUG_COLORS=no DEBUG=main* $srcdir/../bin/test5  &> $srcdir/out5.tmp

function check {
	m=$1
	f1=$2
	f2=$3
	if cmp -s "$f1" "$f2"
	then
   		echo "Test $m: OK"
	else
   		echo "Test $m: KO"
	fi
}

check '1' $srcdir/out0.tmp $srcdir/out0.ref 
check '2' $srcdir/out1.tmp $srcdir/out1.ref 
check '3' $srcdir/out2.tmp $srcdir/out2.ref 
check '4' $srcdir/out3.tmp $srcdir/out3.ref
check '5' $srcdir/out1c.tmp $srcdir/out1c.ref
check '6' $srcdir/out4.tmp $srcdir/out4.ref
check '7' $srcdir/out5.tmp $srcdir/out5.ref


