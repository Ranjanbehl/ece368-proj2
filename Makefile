CFLAGS = -Wall -Werror -O3 
GCC = gcc $(CFLAGS)
VAL = valgrind --tool=memcheck --leak-check=full --show-reachable=yes

all:huff unhuff

huff:huff.o
	$(GCC) huff.o -o huff

huff.o: huff.c huff.h 
	$(GCC) -c huff.c

unhuff:unhuff.o
	$(GCC) unhuff.o -o unhuff

unhuff.o: unhuff.c unhuff.h 
	$(GCC) -c unhuff.c

encode:huff
	huff proj2_sample/input/text0.txt
	  date +"Now time is +%FT%T%z"
	huff proj2_sample/input/text1.txt
	  date +"Now time is +%FT%T%z"
	huff proj2_sample/input/text2.txt
	  date +"Now time is +%FT%T%z"
	huff proj2_sample/input/text3.txt
	  date +"Now time is +%FT%T%z"
	huff proj2_sample/input/text4.txt
	  date +"Now time is +%FT%T%z"
	huff proj2_sample/input/text5.txt
	  date +"Now time is +%FT%T%z"

decode:unhuff
	unhuff proj2_sample/input/text0.txt.huff
	unhuff proj2_sample/input/text1.txt.huff
	unhuff proj2_sample/input/text2.txt.huff
	unhuff proj2_sample/input/text3.txt.huff
	unhuff proj2_sample/input/text4.txt.huff
	unhuff proj2_sample/input/text5.txt.huff

memory: huff 
	$(VAL) huff proj2_sample/input/text5.txt

memory2: unhuff
	$(VAL) unhuff

test: all
	diff proj2_sample/input/text0.txt.huff.unhuff proj2_sample/input/text0.txt
	diff proj2_sample/input/text1.txt.huff.unhuff proj2_sample/input/text1.txt
	diff proj2_sample/input/text2.txt.huff.unhuff proj2_sample/input/text2.txt
	diff proj2_sample/input/text3.txt.huff.unhuff proj2_sample/input/text3.txt
	diff proj2_sample/input/text4.txt.huff.unhuff proj2_sample/input/text4.txt
	diff proj2_sample/input/text5.txt.huff.unhuff proj2_sample/input/text5.txt

clean:
	rm -f *.o 
	rm -f huff
	rm -f unhuff
	rm -f core.*
	rm -f *.txt.huff*
	rm -f *.txt.huff.unhuff*
	rm -f  proj2_sample/input/*.txt.huff*
	rm -f  proj2_sample/input/*.txt.huff.unhuff*
#removing useless stuff
	rm -f proj2_sample/input/test7.txt
	rm -f samplecode.c
	rm -f *test*
	rm -f Untitled.rtf
	rm -f extra2.c
	rm -f extracode.c
	rm -f samplecode.c
	rm -f sample
	rm -f huff.dms
	rm -f unhuff.dms
	