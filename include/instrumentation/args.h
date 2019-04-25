#ifndef INTRUMENTATION_ARGS_H
#define INTRUMENTATION_ARGS_H

#include <stdint-gcc.h>
#include <stdlib.h>
#include <stdio.h>

extern uint64_t targets_of_branch;
extern uint64_t entries_of_basic_block;
extern uint64_t conditional_branch_info;

static inline uint64_t parse_env_var(const char * name) {
    char *var = getenv(name);
	if (var == NULL) {
		printf("no exported variable: %s\n", name);
	}
	assert(var);
    return strtoull(var, NULL, 16);
}

static inline void fetch_instrumentation_args(void) {
    targets_of_branch = parse_env_var("TargetsOfBranch");
    entries_of_basic_block = parse_env_var("EntriesOfBasicBlock");
    conditional_branch_info = parse_env_var("ConditionalBranchInfo");
}

#endif
