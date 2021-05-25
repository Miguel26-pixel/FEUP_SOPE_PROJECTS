all: s c

s: ServerPart/src/server/server.c
	gcc -Wall -DDELAY=100 -o s ServerPart/src/server/server.c ServerPart/src/server/communication.c ServerPart/src/server/fifo.c ServerPart/src/server/lib.c ServerPart/src/server/delay.c ServerPart/src/server/queue.c ServerPart/src/server/register.c ServerPart/src/server/tasks.c ServerPart/src/server/utils.c -pthread

c: ClientPart/src/client/client.c
	gcc -Wall -o c ClientPart/src/client/client.c ClientPart/src/client/communication.c ClientPart/src/client/tasks.c ClientPart/src/client/fifo.c ClientPart/src/client/utils.c -pthread

clean:
	rm -f s c name*