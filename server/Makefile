all: run

run: server.c
	gcc -pthread -o server server.c -L/usr/local/mysql/lib -lmysqlclient
clean: 
	rm -f server
