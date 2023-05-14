all: CW2

CW2: main.o read_write.o func.o frame.o
	gcc main.o read_write.o func.o frame.o -o CW2 -lm 
main.o: main.c CWlib.h read_write.h
	gcc -c main.c
read_write.o: read_write.c func.h CWlib.h
	gcc -c read_write.c
func.o: func.c func.h CWlib.h
	gcc -c func.c 
frame.o: frame.c func.h CWlib.h
	gcc -c frame.c
clean:
	rm -rf *.o
