#include "task_mgr.h"


void (* fp_tasks[TASK_PRIORITIES])(void) = {0};
uint16_t flags[TASK_PRIORITIES] = {0};

/// Add function to task manager
/// If slot already occupied, it will be rejected
///
/// @param fp_task  function pointer (the task)
/// @param priority priority of task to add
///
/// @return True if added, false if not
bool task_mgr_add(void * fp_task, uint8_t const priority)
{
    bool b_ret = false;

    if(fp_task != 0)
    {
        // Check bounds
        if(priority >= 0 && priority < TASK_PRIORITIES)
        {
            // is slot emtpy?
            // if so add to it
            if(0 == fp_tasks[priority])
            {
                fp_tasks[priority] = fp_task;
                b_ret = true;
            }
        }
    }

    return b_ret;
}

/// Remove function from task manager
///
/// @param priority priority of function
void task_mgr_remove(uint8_t const priority)
{
    // Check bounds
    if(priority >= 0 && priority < TASK_PRIORITIES)
    {
        // Clear the slot and flags
        if(0 != fp_tasks[priority])
        {
            fp_tasks[priority] = (void *)0;
            flags[TASK_PRIORITIES] = 0;
        }
    }
}

/// Flag a task to execute
///
/// @param priority the task to flag
///
/// @return True if task was flagged, false if not
bool task_mgr_flag_task(uint8_t const priority)
{
    bool b_ret = false;

    // Check bounds
    if(priority >= 0 && priority < TASK_PRIORITIES)
    {
        // is slot emtpy?
        // if not add flag
        if(0 != fp_tasks[priority])
        {
            ++flags[priority];
            b_ret = true;
        }
    }

    return b_ret;
}


/// Execute each task by priority
///
/// @param b_is_blocking True if task manager runs for ever
///                      False if app has its own service loop
void task_mgr_task(bool b_is_blocking)
{
    do
    {
        // Loop through array
        for(uint8_t idx = 0; idx < TASK_PRIORITIES; idx++)
        {
            // Only process functions with flags > 0
            if(flags[idx] > 0)
            {
                // Only process if function exists
                if(fp_tasks[idx] != 0)
                {
                    // Run task
                    (*fp_tasks[idx])();

                    // Decrement flag
                    --flags[idx];

                    // Exit the loop, let it restart
                    // Always want to run by priority
                    break;
                }
            }
        }
    } while(b_is_blocking);
}
