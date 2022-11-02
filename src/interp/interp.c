#include "interp.h"
#include "../tables.h"

void web49_interp_module(web49_module_t mod) {
    uint64_t start = 0;
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_EXPORT) {
            for (size_t j = 0; j < section.export_section.num_entries; j++) {
                web49_section_export_entry_t entry = section.export_section.entries[j];
                if (!strcmp(entry.field_str, "_start")) {
                    start = entry.index;
                }
            }
        }
    }
    uint64_t num_funcs = 0;
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_IMPORT) {
            for (size_t j = 0; j < section.import_section.num_entries; j++) {
                web49_section_import_entry_t entry = section.import_section.entries[j];
                if (entry.kind == WEB49_EXTERNAL_KIND_FUNCTION) {
                    num_funcs += 1;
                }
            }
        }
    }
    for (size_t i = 0; i < mod.num_sections; i++) {
        web49_section_t section = mod.sections[i];
        if (section.header.id == WEB49_SECTION_ID_CODE) {
            for (size_t j = 0; j < section.code_section.num_entries; j++) {
                web49_section_code_entry_t entry = section.code_section.entries[j];
                for (size_t k = 0; k < entry.num_instrs; k++) {
                    fprintf(stderr, "%s\n", web49_opcode_to_name(entry.instrs[k].opcode));
                }
            }
        }
    }
}
