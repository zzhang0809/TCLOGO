all: logo

logo: lex.yy.c node.c logo.tab.c
	gcc -g lex.yy.c node.c logo.tab.c -o logo -lm

lex.yy.c: logo.l
	flex logo.l

logo.tab.c: logo.y
	bison -d logo.y

clean:
	rm lex.yy.c logo.tab.h logo.tab.c logo logo.svg; touch logo.svg
