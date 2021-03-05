CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -Wno-unused-parameter
OBJS = xmod.o permissions.o
EXEC = xmod

$(EXEC): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lm -o $@

%.o: %.c %.h $(XHDRS)
	@$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean :
	@-rm -f *.o $(EXEC) 