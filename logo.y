%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node.h"

void yyerror(){
  perror("Erreur");
  exit(1);
}

int yywrap(){
  return 1;
}

%}

%token FORWARD LEFT RIGHT REPEAT CIRCLE VALUE

%union{
  ELEMINST * NODE_TYPE;
  int val;
}

%type <val> VALUE
%type <NODE_TYPE> INST PROG

%%

PROG : INST {
        $$ = $1;
	pinst = $$;
          }| INST PROG {
            $$ = ajoutInstruction($2,$1); 
	    pinst = $$; 
	}
	
INST : FORWARD VALUE {
         $$ = creationInstruction(INST_FORWARD,$2,NULL,NULL);
        } |
       LEFT VALUE {
         $$ = creationInstruction(INST_LEFT,$2,NULL,NULL);
       }|
       RIGHT VALUE{
         $$ = creationInstruction(INST_RIGHT,$2,NULL,NULL);
       }|
       CIRCLE VALUE{
         $$ = creationInstruction(INST_CIRCLE,$2,NULL,NULL);
       }|
       REPEAT VALUE '[' PROG ']' {
         $$ = creationInstruction(INST_REPEAT,$2,$4,NULL);
       }

%%

int main(int argc, char *argv[]){
  if (argc <= 2){
    if (argc == 1)
    argv[1] = "black";
    yyparse();
    cor_x = 100;    // initialize the data for svg
    cor_y = 100;
    direction = 0;
    affiche(pinst);
    svg_begin();
    svg(pinst, argv[1]);
    svg_end();
    fclose(flogo);
    supprimer(pinst);
    return 0;
  }else{
    printf("ERREUR! Trop de paramètre\n");
  }
}
