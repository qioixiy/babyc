#include <stdlib.h>
#include <stdio.h>
#include "syntax.h"
#include "list.h"

Syntax *immediate_new(int value) {
    Immediate *immediate = malloc(sizeof(Immediate));
    immediate->value = value;
    
    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = IMMEDIATE;
    syntax->immediate = immediate;

    return syntax;
}

Syntax *variable_new(char *var_name) {
    Variable *variable = malloc(sizeof(Variable));
    variable->var_name = var_name;
    
    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = VARIABLE;
    syntax->variable = variable;

    return syntax;
}

Syntax *bitwise_negation_new(Syntax *expression) {
    UnaryExpression *unary_syntax = malloc(sizeof(UnaryExpression));
    unary_syntax->unary_type = BITWISE_NEGATION;
    unary_syntax->expression = expression;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = UNARY_OPERATOR;
    syntax->unary_expression = unary_syntax;

    return syntax;
}

Syntax *logical_negation_new(Syntax *expression) {
    UnaryExpression *unary_syntax = malloc(sizeof(UnaryExpression));
    unary_syntax->unary_type = LOGICAL_NEGATION;
    unary_syntax->expression = expression;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = UNARY_OPERATOR;
    syntax->unary_expression = unary_syntax;

    return syntax;
}

Syntax *addition_new(Syntax *left, Syntax *right) {
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = ADDITION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;

    return syntax;
}

Syntax *multiplication_new(Syntax *left, Syntax *right) {
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = MULTIPLICATION;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;

    return syntax;
}

Syntax *less_than_new(Syntax *left, Syntax *right) {
    BinaryExpression *binary_syntax = malloc(sizeof(BinaryExpression));
    binary_syntax->binary_type = LESS_THAN;
    binary_syntax->left = left;
    binary_syntax->right = right;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BINARY_OPERATOR;
    syntax->binary_expression = binary_syntax;

    return syntax;
}

Syntax *function_call_new(char *function_name, List *expressions) {
    FunctionCall *function_call = malloc(sizeof(FunctionCall));
    function_call->function_name = function_name;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = FUNCTION_CALL;
    syntax->function_call = function_call;

    return syntax;
}

Syntax *assignment_new(char *var_name, Syntax *expression) {
    Assignment *assignment = malloc(sizeof(Assignment));
    assignment->var_name = var_name;
    assignment->expression = expression;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = ASSIGNMENT;
    syntax->assignment = assignment;

    return syntax;
}

Syntax *return_statement_new(Syntax *expression) {
    ReturnStatement *return_statement = malloc(sizeof(ReturnStatement));
    return_statement->expression = expression;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = RETURN_STATEMENT;
    syntax->return_statement = return_statement;

    return syntax;
}

Syntax *block_new(List *statements) {
    Block *block = malloc(sizeof(Block));
    block->statements = statements;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = BLOCK;
    syntax->block = block;

    return syntax;
}

Syntax *if_new(Syntax *condition, Syntax *then) {
    IfStatement *if_statement = malloc(sizeof(IfStatement));
    if_statement->condition = condition;
    if_statement->then = then;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = IF_STATEMENT;
    syntax->if_statement = if_statement;

    return syntax;
}

Syntax *define_var_new(char *var_name, Syntax *init_value) {
    DefineVarStatement *define_var_statement = malloc(sizeof(DefineVarStatement));
    define_var_statement->var_name = var_name;
    define_var_statement->init_value = init_value;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = DEFINE_VAR;
    syntax->define_var_statement = define_var_statement;

    return syntax;
}

Syntax *while_new(Syntax *condition, Syntax *body) {
    WhileStatement *while_statement = malloc(sizeof(WhileStatement));
    while_statement->condition = condition;
    while_statement->body = body;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = WHILE_SYNTAX;
    syntax->while_statement = while_statement;

    return syntax;
}

Syntax *function_new(char *name, List *parameters, Syntax *root_block) {
    Function *function = malloc(sizeof(Function));
    function->name = name;
    function->root_block = root_block;

    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = FUNCTION;
    syntax->function = function;

    return syntax;
}

Syntax *top_level_new() {
    TopLevel *top_level = malloc(sizeof(TopLevel));
    top_level->declarations = list_new();
    
    Syntax *syntax = malloc(sizeof(Syntax));
    syntax->type = TOP_LEVEL;
    syntax->top_level = top_level;

    return syntax;
}

void syntax_free(Syntax *syntax) {
    if (syntax->type == UNARY_OPERATOR) {
        syntax_free(syntax->unary_expression->expression);
        free(syntax->unary_expression);
        
    } else if (syntax->type == BINARY_OPERATOR){
        syntax_free(syntax->binary_expression->left);
        syntax_free(syntax->binary_expression->right);
        free(syntax->binary_expression);
        
    } else if (syntax->type == IF_STATEMENT) {
        syntax_free(syntax->if_statement->condition);
        syntax_free(syntax->if_statement->then);
        
    } else if (syntax->type == BLOCK) {
        list_free(syntax->block->statements);
        
    } else if (syntax->type == FUNCTION) {
        free(syntax->block);
    }
    free(syntax);
}

char *syntax_type_name(Syntax *syntax) {
    if (syntax->type == IMMEDIATE) {
        return "IMMEDIATE";
    } else if (syntax->type == VARIABLE) {
        return "VARIABLE";
    } else if (syntax->type == UNARY_OPERATOR) {
        if (syntax->unary_expression->unary_type == BITWISE_NEGATION) {
            return "UNARY BITWISE_NEGATION";
        } else if (syntax->unary_expression->unary_type == LOGICAL_NEGATION) {
            return "UNARY BITWISE_NEGATION";
        }
    } else if (syntax->type == BINARY_OPERATOR) {
        if (syntax->binary_expression->binary_type == ADDITION) {
            return "ADDITION";
        } else if (syntax->binary_expression->binary_type == MULTIPLICATION) {
            return "MULTIPLICATION";
        } else if (syntax->binary_expression->binary_type == LESS_THAN) {
            return "LESS THAN";
        }
    } else if (syntax->type == FUNCTION_CALL) {
        return "FUNCTION CALL";
    } else if (syntax->type == IF_STATEMENT) {
        return "IF";
    } else if (syntax->type == RETURN_STATEMENT) {
        return "RETURN";
    } else if (syntax->type == DEFINE_VAR) {
        return "DEFINE VARIABLE";
    } else if (syntax->type == BLOCK) {
        return "BLOCK";
    } else if (syntax->type == FUNCTION) {
        return "FUNCTION";
    } else if (syntax->type == ASSIGNMENT) {
        return "ASSIGNMENT";
    } else if (syntax->type == WHILE_SYNTAX) {
        return "WHILE";
    } else if (syntax->type == TOP_LEVEL) {
        return "TOP LEVEL";
    }

    // Should never be reached.
    return "??? UNKNOWN SYNTAX";
}

void print_syntax_indented(Syntax *syntax, int indent) {
    for (int i=0; i<indent; i++) {
        printf(" ");
    }

    char *syntax_type_string = syntax_type_name(syntax);

    if (syntax->type == IMMEDIATE) {
        printf("%s %d\n", syntax_type_string, syntax->immediate->value);
    } else if (syntax->type == VARIABLE) {
        printf("%s '%s'\n", syntax_type_string, syntax->variable->var_name);
    } else if (syntax->type == UNARY_OPERATOR) {
        printf("%s\n", syntax_type_string);
        print_syntax_indented(syntax->unary_expression->expression, indent + 4);
        
    } else if (syntax->type == BINARY_OPERATOR){
        printf("%s LEFT\n", syntax_type_string);
        print_syntax_indented(syntax->binary_expression->left, indent + 4);

        for (int i=0; i<indent; i++) {
            printf(" ");
        }

        printf("%s RIGHT\n", syntax_type_string);
        print_syntax_indented(syntax->binary_expression->right, indent + 4);
        
    } else if (syntax->type == FUNCTION_CALL) {
        printf("%s '%s'\n", syntax_type_string, syntax->function_call->function_name);

    } else if (syntax->type == IF_STATEMENT) {
        printf("%s CONDITION\n", syntax_type_string);
        print_syntax_indented(syntax->if_statement->condition, indent + 4);

        for (int i=0; i<indent; i++) {
            printf(" ");
        }

        printf("%s THEN\n", syntax_type_string);
        print_syntax_indented(syntax->if_statement->then, indent + 4);

    } else if (syntax->type == RETURN_STATEMENT) {
        printf("%s\n", syntax_type_string);
        print_syntax_indented(syntax->return_statement->expression, indent + 4);

    } else if (syntax->type == DEFINE_VAR) {
        printf("%s '%s'\n", syntax_type_string, syntax->define_var_statement->var_name);

        for (int i=0; i<indent; i++) {
            printf(" ");
        }

        printf("'%s' INITIAL VALUE\n", syntax->define_var_statement->var_name);
        print_syntax_indented(syntax->define_var_statement->init_value, indent + 4);

    } else if (syntax->type == BLOCK) {
        printf("%s\n", syntax_type_string);

        List *statements = syntax->block->statements;
        for (int i=0; i<list_length(statements); i++) {
            print_syntax_indented(list_get(statements, i), indent + 4);
        }

    } else if (syntax->type == FUNCTION) {
        printf("%s '%s'\n", syntax_type_string, syntax->function->name);
        print_syntax_indented(syntax->function->root_block, indent + 4);
        
    } else if (syntax->type == ASSIGNMENT) {
        printf("%s '%s'\n", syntax_type_string, syntax->assignment->var_name);
        print_syntax_indented(syntax->assignment->expression, indent + 4);
        
    } else if (syntax->type == WHILE_SYNTAX) {
        printf("%s\n", syntax_type_string);
        print_syntax_indented(syntax->assignment->expression, indent + 4);
        
    } else if (syntax->type == TOP_LEVEL) {
        printf("%s\n", syntax_type_string);

        List *declarations = syntax->top_level->declarations;
        for (int i=0; i<list_length(declarations); i++) {
            print_syntax_indented(list_get(declarations, i), indent + 4);
        }

    } else {
        printf("??? UNKNOWN SYNTAX TYPE\n");
    }
}

void print_syntax(Syntax *syntax) {
    print_syntax_indented(syntax, 0);
}
