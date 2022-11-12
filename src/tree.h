#if !defined(WEB49_HEADER_IR_IR)
#define WEB49_HEADER_IR_IR

#include "ast.h"

web49_instr_t web49_tree_opt_read(web49_module_t *mod, web49_instr_t **head);
web49_instr_t web49_tree_opt_read_block(web49_module_t *mod, web49_instr_t **head);
void web49_tree_opt_code(web49_module_t *mod, web49_section_code_entry_t *entry);
void web49_tree_opt_module(web49_module_t *mod);

#endif