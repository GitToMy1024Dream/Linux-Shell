cc=gcc
cli=client
ser=server
cliSrc=comm.c client.c
serSrc=comm.c server.c

.PHONY:all
all:$(cli) $(ser)
$(cli):$(cliSrc)
	$(cc) -o $@ $^
$(ser):$(serSrc)
	$(cc) -o $@ $^
.PHONY:clean
clean:
	rm -f $(cli) $(ser)