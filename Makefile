all: scantxt


scantxt: scantxt.c
	gcc scantxt.c -o scantxt


clean: 
	rm -fr *.o *.a 

