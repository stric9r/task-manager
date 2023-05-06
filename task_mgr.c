#include "task_mgr.h"



(void)(*fp[TASK_PRIORITIES])(void) = {0};
uint16_t flags[TASK_PRIORITIES] = {0};

/// Add function to task manager
/// If slot already occupied, it will be rejected
///
/// @param fp       function pointer (the task)
/// @param priority priority of task to add
///
/// @return True if added, false if not
bool task_mgr_add((void*) fp, uint8_t const priority)
{
    bool b_ret = false;

    // Check bounds
    if(priority >= 0 && priority < TASK_PRIORITIES)
    {
        // is slot emtpy?
        // if so add to it
        if(0 == fp[priority])
        {
            fp[priority] = fp;

            b_ret = true;
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
        // Clear the slot
        if(0 == fp[priority])
        {
            fp[priority] = (void *)0;

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
    if(priority >=0 && priority < TASK_PRIORITIES)
    {
        // is slot emtpy?
        // if so add to it and increment front
        if(0 == fp[priority])
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
        for(uint8_t idx = 0; idx++; idx < TASK_PRIORITIES)
        {
            // Only process functions with tasks > 0
            if(flags[idx] > 0)
            {
                // Only process if function exists
                if(fp[idx] != 0)
                {
                    // Run task
                    *fp[idx]();

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
