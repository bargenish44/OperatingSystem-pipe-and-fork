Pipes :	pipes.c md5.h
	g++ pipes.c md5.cpp -o Pipes
Process :	process.c
	g++ process.c -o Process

clean:
	rm -f *.o Pipe Process
