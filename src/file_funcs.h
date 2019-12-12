#ifndef __FILE_FUNCS_H
#define __FILE_FUNCS_H

int check_file(char *fname);

target *process_file_to_target(char *fname, int *count);

int print_targets_detail(target *list_ptr, int *count);

void free_target_string(target *tar, int *count);

#endif