all: s c

s: server/server.c server/utils.c server/fifo.c server/tasks.c server/communication.c server/queue.c server/lib.c server/register.c server/delay.c
	gcc -Wall -DDELAY=0 -o s server/server.c server/utils.c server/fifo.c server/tasks.c server/communication.c server/queue.c server/lib.c server/register.c server/delay.c -pthread 

c: client_class/common.h client_class/client.c
	gcc -Wall -o c client_class/client.c -pthread

clean:
	rm -f s c