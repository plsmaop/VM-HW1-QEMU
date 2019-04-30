#ifndef INSTRUMENTATION_RESULTS_H
#define INSTRUMENTATION_RESULTS_H

#include <stdint-gcc.h>
#include <inttypes.h>
#include <stdio.h>

#include "instrumentation/args.h"
#include "instrumentation/uthash.h"

struct InstruEntry {
    uint64_t addr;
    uint64_t cnt;
    UT_hash_handle hh;
};

extern struct InstruEntry *dests;
extern struct InstruEntry *srcs;
extern uint64_t n_taken;
extern uint64_t n_not_taken;

static inline bool addr_sort(struct InstruEntry *a, struct InstruEntry *b) {
    return a->addr > b->addr;
}

static inline void sort_by_addr(struct InstruEntry **entries) {
    HASH_SORT(*entries, addr_sort);
}

static inline void print_entries(struct InstruEntry **entries) {
    sort_by_addr(entries);
    for (struct InstruEntry *entry = *entries; entry != NULL; entry = (struct InstruEntry *)(entry->hh.next)) {
        printf("%" PRIx64 ", %" PRIu64 "\n", entry->addr, entry->cnt);
    }
    printf("\n");
}

static inline void print_instrumentation_results(void) {
    printf("Targets of branch 0x%" PRIx64 "\n", targets_of_branch);
    print_entries(&dests);

    printf("Entries of BasicBlock 0x%" PRIx64 "\n", entries_of_basic_block);
    print_entries(&srcs);

    printf("Conditional branch 0x%" PRIx64 "\n", conditional_branch_info);
    printf("taken:%" PRIu64 ", not-taken:%" PRIu64 "\n", n_taken, n_not_taken);

    fflush(stdout);
}

#endif
