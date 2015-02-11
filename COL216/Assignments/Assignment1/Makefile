all: interpreter ass1.asm
	./interpreter.exe ass1.asm

interpreter: interpreter.c
	gcc -o interpreter interpreter.c

clean:
	rm -rf *.exe