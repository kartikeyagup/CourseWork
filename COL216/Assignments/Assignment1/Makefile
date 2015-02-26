all: interpreter ass1.asm
	./interpreter.exe ass1.asm

another: interpreter ass1_again.asm
	./interpreter ass1_again.asm $(n)

interpreter: interpreter.c
	gcc -o interpreter interpreter.c

clean:
	rm -rf interpreter
