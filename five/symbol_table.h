// symbol_table.h

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef enum { VARIABLE, FUNCTION } SymbolType;
typedef enum { GLOBAL, LOCAL } SymbolScope;

typedef struct Symbol {
    char *name;
    SymbolType type;
    SymbolScope scope;
    int memory_location;
    int line_number;
    struct Symbol *next; // For handling collisions using chaining
} Symbol;

typedef struct SymbolTable {
    Symbol *table[TABLE_SIZE];
} SymbolTable;

// Function prototypes
SymbolTable* create_table();
unsigned int hash(const char *str);
Symbol* create_symbol(const char *name, SymbolType type, SymbolScope scope, int memory_location, int line_number);
void add_symbol(SymbolTable *table, const char *name, SymbolType type, SymbolScope scope, int memory_location, int line_number);
Symbol* search_symbol(SymbolTable *table, const char *name);
void remove_symbol(SymbolTable *table, const char *name);
void print_symbol_table(SymbolTable *table);  // Update function prototype
void free_table(SymbolTable *table);

#endif

