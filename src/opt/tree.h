#if !defined(WEB49_HEADER_OPT_TREE)
#define WEB49_HEADER_OPT_TREE

#include "../ast.h"

web49_instr_t web49_opt_tree_read(web49_module_t *mod, web49_instr_t **head);
web49_instr_t web49_opt_tree_read_block(web49_module_t *mod, web49_instr_t **head);
void web49_opt_tree_code(web49_module_t *mod, web49_section_code_entry_t *entry);
void web49_opt_tree_module(web49_module_t *mod);

#endif