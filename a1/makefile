 # makefile
 # Jerad Alexander Arnold
 # 1008362
 # jerad@uoguelph.ca
 # 2019-09-29

CC = gcc
FLAGS = -ansi -Wall -pedantic

all: create_array.o create_list.o ds_memory.o ds_array.o ds_list.o
	$(CC) $(FLAGS) -o create_array create_array.o ds_memory.o ds_array.o
	$(CC) $(FLAGS) -o create_list create_list.o ds_memory.o ds_list.o

create_array.o: create_array.c ds_memory.h ds_array.h
	$(CC) $(FLAGS) -c create_array.c -o create_array.o

create_list.o: create_list.c ds_memory.h ds_list.h
	$(CC) $(FLAGS) -c create_list.c -o create_list.o

ds_memory.o: ds_memory.c ds_memory.h
	$(CC) $(FLAGS) -c ds_memory.c -o ds_memory.o

ds_array.o: ds_array.c ds_array.h ds_memory.h
	$(CC) $(FLAGS) -c ds_array.c -o ds_array.o

ds_list.o: ds_list.c ds_list.h
	$(CC) $(FLAGS) -c ds_list.c -o ds_list.o

runl: all
	./create_list
	
runa: all
	./create_array

clean:
	rm *.bin
	rm ./create_array
	rm ./create_list
	rm *.o

cppcheck: 
	cppcheck -enable=all -language=c -std=c99 -inconclusive -suppress=missingInclude src/*.c
