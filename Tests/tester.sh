#!/bin/tcsh

if ( ! -f ./sudoku) then
	echo "sudoku file not found"
endif

set testNum = 1

echo "" > tester_input.txt
./sudoku 0 <tester_input.txt> tester_output.txt
./HW3 0 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "81\n" > tester_input.txt
./sudoku 0 <tester_input.txt> tester_output.txt
./HW3 0 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "66\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "15\nset 2 1 4\nset 2 1   5\n" > tester_input.txt
./sudoku 3 <tester_input.txt> tester_output.txt
./HW3 3 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "15\nset 2 1 4\nset 2 1 5\n" > tester_input.txt
./sudoku 3 <tester_input.txt> tester_output.txt
./HW3 3 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "15\nsat 2 1 4\n  sey 2 1   5  \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "15\nset 2 1 4 2 4\n  set 2 1   5  1 100 \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "15\nset 2 1 4 i\n  set 2 1   5  s e bbb \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "20\nexit\n" > tester_input.txt
./sudoku 3 <tester_input.txt> tester_output.txt
./HW3 3 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\nvalidate\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "0\nvalidate\nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "15\nvalidate\nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "15\n   validate   s\n  exit  \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "10\nvalidate\nexit\n" > tester_input.txt
./sudoku 331 <tester_input.txt> tester_output.txt
./HW3 331 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "0\n  validatee \nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "50\n validatee\nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "15\n   validate e   s\n  exit  \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\nrestart\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "50\n         \n   \n\n\n   \n !!!!\n   1312\n se  1 2 3\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "50\nhint 1 1\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "50\n  h  int 1 1 \n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "50\nset	 1 1 0\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "50\n	hint	 1 2 i validate\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "50\n	hint	 1 2 i validate\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "50\n	hint	\n 1 2 i validate\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\nhint 5 9\nset 5 9 1\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "80\nset 5 9 2\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "80\nset 5 9 2\nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\nset 5 9 5\nvalidate\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "80\nset 5 9 2\nset 4 2 5\n set 9 9 4\n validate\n set 4 4 2\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "20\nset 1 1 3\nset 3 7 4\n set 2 1 5\nset 5 5 3\nvalidate\n set 4 4 2\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


echo "20\nrestart\n50\nexit\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++



echo "20\nset 1 1 3\nset 3 7 4\n set 2 1 5\nset 5 5 3\nvalidate\nrestart\n30\nset 2 2 1\n set 4 4 2\nhint 4 4\n" > tester_input.txt
./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++

echo "20\nset 1 1 3\nset 3 7 4\n set 2 1 5\nset 5 5 3\nvalidate\nrestart\n30\nset 2 2 1\n set 4 4 2\nhint 4 4\n	exit	\n" > tester_input.txt
valgrind --leak-check=full  --show-leak-kinds=all ./sudoku 256 <tester_input.txt> tester_output.txt
./HW3 256 <tester_input.txt> tester_expected.txt

if ("`diff tester_expected.txt tester_output.txt`" != "") then
	echo "\nfail test $testNum"
	echo "-------- input --------"
	cat tester_input.txt
	echo "---- expected output ----"
	cat tester_expected.txt
	echo "---- actual output ----"
	cat tester_output.txt
	echo ""
	echo "---- diff output ----"
	diff tester_expected.txt tester_output.txt
	echo ""
else
	echo "test $testNum success"
endif
@ testNum++


rm tester_input.txt
rm tester_output.txt
rm tester_expected.txt
exit
