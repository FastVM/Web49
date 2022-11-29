#include "tee.h"

#include "../tables.h"

void web49_opt_tee_code(web49_module_t *mod, web49_section_code_entry_t *entry) {
    uint64_t len = 0;
    uint64_t alloc = entry->num_instrs + 16;
    web49_instr_t *next = web49_malloc(sizeof(web49_instr_t) * alloc);
    for (uint64_t i = 0; i < entry->num_instrs; i++) {
        web49_instr_t instr = entry->instrs[i];
        if (len + 2 >= alloc) {
            alloc = (len + 2) * 2;
            next = web49_realloc(next, sizeof(web49_instr_t) * alloc);
        }
        if (instr.opcode == WEB49_OPCODE_TEE_LOCAL) {
            next[len++] = (web49_instr_t){
                .opcode = WEB49_OPCODE_SET_LOCAL,
                .immediate = instr.immediate,
            };
            next[len++] = (web49_instr_t){
                .opcode = WEB49_OPCODE_GET_LOCAL,
                .immediate = instr.immediate,
            };
            web49_free_instr(instr);
        } else {
            next[len++] = instr;
        }
    }
    web49_free(entry->instrs);
    entry->num_instrs = len;
    entry->instrs = next;
}

void web49_opt_tee_module(web49_module_t *mod) {
    for (uint64_t s = 0; s < mod->num_sections; s++) {
        web49_section_t cur = mod->sections[s];
        if (cur.header.id == WEB49_SECTION_ID_CODE) {
            for (uint64_t i = 0; i < cur.code_section.num_entries; i++) {
                web49_opt_tee_code(mod, &cur.code_section.entries[i]);
            }
        }
    }
}
