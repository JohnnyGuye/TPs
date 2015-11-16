echo -----------------------------------------------------------
echo Tests de non-régression TP C++n°2 : \(programme : $1\)
echo -----------------------------------------------------------

nTestCount=0
nSuccesfulTests=0
nStrResult="$1 "

echo ADD.1
let "nTestCount=$nTestCount+1"
./$1 < testNR/add.1.in > testNR/temp1.txt
grep -v '^#' testNR/temp1.txt > testNR/temp2.txt
diff -wB testNR/add.1.out testNR/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo STATS_C.1
let "nTestCount=$nTestCount+1"
./$1 < testNR/stats_c.1.in > testNR/temp1.txt
grep -v '^#' testNR/temp1.txt > testNR/temp2.txt
diff -wB testNR/stats_c.1.out testNR/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo STATS_D7.1
let "nTestCount=$nTestCount+1"
./$1 < testNR/stats_d7.1.in > testNR/temp1.txt
grep -v '^#' testNR/temp1.txt > testNR/temp2.txt
diff -wB testNR/stats_d7.1.out testNR/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo JAM_DH.1
let "nTestCount=$nTestCount+1"
./$1 < testNR/jam_dh.1.in > testNR/temp1.txt
grep -v '^#' testNR/temp1.txt > testNR/temp2.txt
diff -wB testNR/jam_dh.1.out testNR/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi

echo OPT.1
let "nTestCount=$nTestCount+1"
./$1 < testNR/opt.1.in > testNR/temp1.txt
grep -v '^#' testNR/temp1.txt > testNR/temp2.txt
diff -wB testNR/opt.1.out testNR/temp2.txt
if [ $? -eq 0 ]
        then
		echo PASSED
            	let "nSuccesfulTests=$nSuccesfulTests+1"
		nStrResult=$nStrResult" 1"
	else
		echo FAILED
		nStrResult=$nStrResult" 0"
fi
echo -----------------------------------------------------------
echo RESULTS
echo -----------------------------------------------------------
echo Results: $nSuccesfulTests/$nTestCount
echo CSVLine: $nStrResult
echo $nStrResult >> testNR/results.txt
