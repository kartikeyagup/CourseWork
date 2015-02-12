all: interpreter hardy.asm
	./interpreter.exe hardy.asm

interpreter: interpreter.c
	gcc -o interpreter interpreter.c

clean:
	rm -rf *.exe
