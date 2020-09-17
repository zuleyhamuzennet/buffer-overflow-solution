all: compile1 compile2

compile1:
	rm -rf soru1
	gcc -I ./include/ -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include/ -o ./soru1 ./lib/fields.o ./src/soru1.c

compile2:
	rm -rf soru2
	gcc -I ./include/ -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include/ -o ./soru2 ./lib/fields.o ./src/soru2.c
	