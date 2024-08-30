// symbol_table.c
#include <stdio.h>
#include "symbol_table.h"

SymbolTable* create_table() {
    SymbolTable *table = (SymbolTable *)malloc(sizeof(SymbolTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->table[i] = NULL;
    }
    return table;
}

unsigned int hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}

Symbol* create_symbol(const char *name, SymbolType type, SymbolScope scope, int memory_location, int line_number) {
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->scope = scope;
    symbol->memory_location = memory_location;
    symbol->line_number = line_number;
    symbol->next = NULL;
    return symbol;
}

void add_symbol(SymbolTable *table, const char *name, SymbolType type, SymbolScope scope, int memory_location, int line_number) {
    unsigned int index = hash(name);
    Symbol *new_symbol = create_symbol(name, type, scope, memory_location, line_number);
    
    if (table->table[index] == NULL) {
        table->table[index] = new_symbol;
    } else {
        Symbol *current = table->table[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_symbol;
    }
}

Symbol* search_symbol(SymbolTable *table, const char *name) {
    unsigned int index = hash(name);
    Symbol *current = table->table[index];
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void remove_symbol(SymbolTable *table, const char *name) {
    unsigned int index = hash(name);
    Symbol *current = table->table[index];
    Symbol *prev = NULL;
    
    while (current != NULL && strcmp(current->name, name) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        return; // Symbol not found
    }
    
    if (prev == NULL) {
        table->table[index] = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current->name);
    free(current);
}

void free_table(SymbolTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *current = table->table[i];
        while (current != NULL) {
            Symbol *temp = current;
            current = current->next;
            free(temp->name);
            free(temp);
        }
    }
    free(table);
}

void print_symbol_table(SymbolTable *table) {
    printf("Symbol Table:\n");
    printf("------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s | %-15s | %-10s |\n", "Name", "Type", "Scope", "Memory Location", "Line Number");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *symbol = table->table[i];
        while (symbol) {
            printf("| %-10s | %-10s | %-10s | %-15d | %-10d |\n",
                   symbol->name,
                   symbol->type == VARIABLE ? "Variable" : "Function",
                   symbol->scope == GLOBAL ? "Global" : "Local",
                   symbol->memory_location,
                   symbol->line_number);
            symbol = symbol->next;
        }
    }
    printf("------------------------------------------------------------\n");
}

