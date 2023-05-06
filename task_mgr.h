#ifndef TASK_MGR_H
#define TASK_MGR_H

#include "stdbool.h"
#include "stdint.h"

/// Array size for how many tasks to keep
/// Update to your needs.  It can go up to UINT8_MAX
/// But if you need UINT8_MAX, this probably isn't
/// the module for you
#define TASK_PRIORITIES 10


bool task_mgr_add(void * fp, uint8_t const priority);
void task_mgr_remove(uint8_t const priority);
bool task_mgr_flag_task(uint8_t const priority);
void task_mgr_task(bool b_is_blocking);


#endif //TASK_MGR_H