main:
	gcc server.c serch_user.c serch_word.c insert_user.c chpasswd.c history.c -o server.out -lpthread -lsqlite3
	gcc client.c sigin_create.c -o client.out

all:
	vim *.c dirc.h -p

clear:
	rm -rf *.out
