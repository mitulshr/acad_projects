warmup1:  my402list.o warmup1.o
	gcc -o warmup1 -g warmup1.o my402list.o

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c 


warmup1.o: warmup1.c  my402list.h
	gcc -g -c -Wall warmup1.c


clean:
	rm *.o warmup1
