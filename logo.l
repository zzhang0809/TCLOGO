%{
#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include "logo.tab.h"
%}

%%

[1-9][0-9]* yylval.val=atoi(yytext);return VALUE;
FORWARD return FORWARD;
LEFT return LEFT;
RIGHT return RIGHT;
REPEAT return REPEAT;
CIRCLE return CIRCLE;
[\[] return '[';
[\]] return ']';
\t ;
\n ;
%%
