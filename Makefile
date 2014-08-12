CC=gcc

queue: queue.o main.c
	$(CC) -o $@ $^ -g -lpthread

queue.o: queue.c
	$(CC) -c  $^ -g

main.o: main.c
	$(CC) -c  $^ -g

clean:
	find . -name "*.o" |xargs rm -rf
	rm -rf queue 
	rm -rf core*
