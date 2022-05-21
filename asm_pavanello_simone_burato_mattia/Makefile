AS = as --32 
LD = ld -m  elf_i386
FLAGS = -gstabs
GCC_AS = gcc -m32 -c $(FLAGS) -o
GCC_LD = gcc -m32 -o
WARNINGS = -Wall
all:
	$(GCC_AS) parking.o parking.c 
	$(GCC_AS) main.o main.s 
	$(GCC_AS) stampa.o stampa.s 
	$(GCC_LD) parking parking.o main.o stampa.o 
clean:
	rm -f parking.o main.o stampa.o parking core
win:
	$(GCC_AS) parking.o parking.c 
	$(GCC_AS) main.o main.s 
	$(GCC_AS) stampa.o stampa.s 
	$(GCC_LD) parking.exe parking.o main.o stampa.o


	
