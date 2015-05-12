warmup2:  warmup2.o my402list.o packetArrival.o tokenDeposit.o server1.o server2.o handler.o
	
	gcc -o warmup2 -pthread -lrt -g warmup2.o my402list.o packetArrival.o tokenDeposit.o server1.o server2.o handler.o -lm


warmup2.o: warmup2.c  warm2.h my402list.h 
	gcc -g -c -Wall warmup2.c

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c 
	
packetArrival.o: packetArrival.c  warm2.h my402list.h
	gcc -g -c -Wall packetArrival.c
	
tokenDeposit.o: tokenDeposit.c  warm2.h my402list.h
	gcc -g -c -Wall tokenDeposit.c
	
server1.o: server1.c  warm2.h my402list.h
	gcc -g -c -Wall server1.c

server2.o: server2.c  warm2.h my402list.h
	gcc -g -c -Wall server2.c
	
handler.o: handler.c  warm2.h my402list.h
	gcc -g -c -Wall handler.c
	
clean:
	rm -f *.o warmup2
