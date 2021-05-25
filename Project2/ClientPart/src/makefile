all: s c

s: server_class/server.o server_class/lib.o server_class/delay.c server_class/delay.h
	gcc -Wall -DDELAY=100 -o s server_class/delay.c server_class/lib.o server_class/server.o -pthread

c: client/client.c
	gcc -Wall -o c client/client.c client/communication.c client/tasks.c client/fifo.c client/utils.c -pthread

# server.o: server.c common.h
# 	gcc -Wall -c -o server.o server.c

# lib.o: lib.c lib.h
# 	gcc -Wall -c -o lib.o lib.c

clean:
	rm -f s c
