
D			[0-9]
L			[a-zA-Z_]

%{
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "y.tab.h"

void comment();

void error();
%}


%%
"//"[^\n]*    { /* Discard c99 comments. */ }
"/*"          { comment(); }
[ \t\n]+      { /* Ignore whitespace */ }

"{"           { return OPEN_BRACE; }
"}"           { return CLOSE_BRACE; }
"("           { return '('; }
")"           { return ')'; }
"~"           { return '~'; }
"!"           { return '!'; }
"+"           { return '+'; }
"*"           { return '*'; }
"<"           { return '<'; }
"="           { return '='; }
";"           { return ';'; }
","           { return ','; }
[0-9]+        {
                /* TODO: check numbers are in the legal range, and don't start with 0. */
                yylval = strdup(yytext); return NUMBER;
              }
"if"          { return IF; }
"while"       { return WHILE; }
"return"      { return RETURN; }

"int"         { return TYPE; }
{L}({L}|{D})* { yylval = strdup(yytext); return IDENTIFIER; }

"#include"    { return INCLUDE; }
"<"[a-z.]+">" { return HEADER_NAME; }
%%

#define INPUT_EOF 0

void comment(void) {
    /* Consume characters up to the closing comment marker. */
    char c, prev = 0;
  
    while ((c = input()) != INPUT_EOF) {
        if (c == '/' && prev == '*')
            return;
        prev = c;
    }
    error("unterminated comment");
}
