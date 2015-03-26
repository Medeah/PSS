

threads: threads.c
	gcc -Wall -g -std=c11 -pthread threads.c -o threads

run: threads
	./threads

philosopher: philosopher.c
	gcc -Wall -g -std=c11 -pthread philosopher.c -o philosopher

clean:
	rm threads philosopher
