/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode* declaration(void);
static TreeNode* declaration_1 (void);
static TreeNode* type_specifier(void);
static TreeNode* param_list(void);
static TreeNode* param_list1(void);
static TreeNode* param_list2(void);
static TreeNode* param(void);
static TreeNode* compound_stmt(void);
static TreeNode* statement(void);
static TreeNode* expression_stmt(void);
static TreeNode* selection_stmte(void);
static TreeNode* iteration_stmt(void);
static TreeNode* return_stmt(void);
static TreeNode* expression(void);
static TreeNode* var(void);
static TreeNode* simple_expression(TreeNode* par);
static TreeNode* relop(TreeNode* par);
static TreeNode* additive_expression(TreeNode* par);
static TreeNode* addop(void);
static TreeNode* term(TreeNode* par);
static TreeNode* mulop(void);
static TreeNode* factor(TreeNode* par);
static TreeNode* factor_1(TreeNode* par);
static TreeNode* arg_list(void);

static void syntaxError(char* message)
{
    fprintf(listing, "\n>>> ");
    fprintf(listing, "Syntax error at line %d: %s", lineno, message);
    Error = TRUE;
}

static void match(TokenType expected)
{
    if (token == expected) token = getToken();
    else {
        syntaxError("unexpected token -> ");
        printToken(token, tokenString);
        fprintf(listing, "      ");
    }
}

TreeNode* declaration()
{
    type_specifier;
    match(ID);
    declaration_1;
}

TreeNode* declaration_1()
{
    switch (token)
    {
    case SEMI:
        match(';');
    case LMBRACKET:
        match('[');
        match(NUM);
        match(']');
        match(';');
    case LPAREN:
        match('(');
        param_list;
        match(')');
        compound_stmt;
    }
}

TreeNode* type_specifier()
{
    switch (token)
    {
    case INT:
        match(INT);
    case VOID:
        match(VOID);
    }
}


/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly
 * constructed syntax tree
 */
TreeNode* parse(void)
{
    TreeNode* t;
    token = getToken();
    t = stmt_sequence();
    if (token != ENDFILE)
        syntaxError("Code ends before file\n");
    return t;
}
