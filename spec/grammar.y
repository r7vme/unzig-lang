Root <- skip TopLevelDeclarations eof

# *** Top level ***
TopLevelDeclarations <- TopLevelDecl TopLevelDeclarations*
TopLevelDecl <- FnDef
             / VarDecl

FnDef <- KEYWORD_fn IDENTIFIER LPAREN RPAREN TypeExpr Block

VarDecl <- KEYWORD_var IDENTIFIER COLON TypeExpr (AssignOp Expr)? SEMICOLON

# *** Block Level ***
Block <- LBRACE Statement* RBRACE
Statement <- VarDecl
          / AssignSt
          / ReturnSt
AssignSt <- IDENTIFIER AssignOp Expr SEMICOLON
ReturnSt <- KEYWORD_return Expr? SEMICOLON

# *** Expression Level ***
Expr <- PrimaryExpr BinOpRhsExpr
BinOpRhsExpr <- (BinOp PrimaryExpr)*
PrimaryExpr <- GroupedExpr
            / FnCallExpr
            / VarExpr
            / NumberExpr
GroupedExpr <- LPAREN Expr RPAREN
FnCallExpr <- IDENTIFIER LPAREN RPAREN
VarExpr <- IDENTIFIER
NumberExpr <- FLOAT
           / INTEGER
TypeExpr <- IDENTIFIER

# Operators
AssignOp <- EQUAL
BinOp <- PLUS / MINUS / ASTERISK / SLASH

# *** Tokens ***
eof <- !.
dec <- [0-9]

dec_int <- dec*

skip <- [ \n]*

FLOAT <- dec_int "." dec_int skip
INTEGER <- dec_int skip
IDENTIFIER
    <- !keyword [A-Za-z_] [A-Za-z0-9_]* skip


ASTERISK             <- '*'      ![*%=]    skip
COLON                <- ':'                skip
EQUAL                <- '='      ![>=]     skip
LBRACE               <- '{'                skip
LPAREN               <- '('                skip
MINUS                <- '-'      ![%=>]    skip
PLUS                 <- '+'      ![%+=]    skip
RBRACE               <- '}'                skip
RPAREN               <- ')'                skip
SEMICOLON            <- ';'                skip
SLASH                <- '/'      ![=]      skip

end_of_word <- ![a-zA-Z0-9_] skip
KEYWORD_fn          <- 'fn'          end_of_word
KEYWORD_pub         <- 'pub'         end_of_word
KEYWORD_return      <- 'return'      end_of_word
KEYWORD_var         <- 'var'         end_of_word

keyword <- KEYWORD_fn / KEYWORD_pub / KEYWORD_return / KEYWORD_var
