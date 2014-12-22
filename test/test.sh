#!/usr/bin/env bash 
srcdir=`dirname $0`
srcdir=`cd $srcdir; pwd`
dstdir=`pwd`

DEBUG_COLORS=no $srcdir/../bin/test &> $srcdir/out0.tmp 
DEBUG_COLORS=no DEBUG=main $srcdir/../bin/test &> $srcdir/out1.tmp 
DEBUG=main $srcdir/../bin/test &> $srcdir/out1c.tmp 
DEBUG_COLORS=no DEBUG=* $srcdir/../bin/test &> $srcdir/out2.tmp 
DEBUG_COLORS=no DEBUG=* $srcdir/../bin/test2 &> $srcdir/out3.tmp 

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

check '1' $srcdir/out0.tmp $srcdir/out0-ref.tmp 
check '2' $srcdir/out1.tmp $srcdir/out1-ref.tmp 
check '3' $srcdir/out2.tmp $srcdir/out2-ref.tmp 
check '4' $srcdir/out3.tmp $srcdir/out3-ref.tmp
check '5' $srcdir/out1c.tmp $srcdir/out1c-ref.tmp


