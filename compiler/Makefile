
default:
	yacc -d parser.y
	flex scanner.l
	gcc lex.yy.c -o a.out

clean:
	rm -f y.tab.*
	rm -f *.out
	rm -f lex.yy.c