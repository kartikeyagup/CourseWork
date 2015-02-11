Assignment1.lex.sml: Assignment1.lex
	ml-lex Assignment1.lex

all: Assignment1.lex.sml Assignment1.sml
	sml Assignment1.sml

run: Assignment1.lex.sml input.txt
	sml Assignment1.sml

clean:
	rm -rf Assignment1.lex.sml
