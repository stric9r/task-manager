#include "../src/task_mgr.h"
#include <stdio.h>

static void task_0(void)
{
    printf("task 0\n");
}

static void task_1(void)
{
    printf("task 1\n");
}

static void task_2(void)
{
    printf("task 2\n");
}

static void task_3(void)
{
    printf("task 3\n");
}

static void task_9(void)
{
    printf("task 9\n");
}

int main(void)
{

    printf("Program start\n");
    // Add some tasks with priority
    bool b_add_success = true;
    b_add_success &= task_mgr_add(task_0, 0);
    b_add_success &= task_mgr_add(task_1, 1);
    b_add_success &= task_mgr_add(task_2, 2);
    b_add_success &= task_mgr_add(task_3, 3);
    b_add_success &= task_mgr_add(task_9, 9);

    // Force a failure too many task
    // Assuming TASK_PRIORITIES is 10, valid tasks are 0-9
    #if 0
    b_add_success &= task_mgr_add(task_9, 10);
    #endif

    // Force a failure task already added
    #if 0
    b_add_success &= task_mgr_add(task_0, 3);
    #endif

    // Should run task 0 three times, then 1, 2, and 9 on next task_mgr_task call.
    // Task 3 was added and flagged multiple times but removed, it will not execute
    // Interrupts or events should trigger these flags to be set
    // Listed here for a simple example
    task_mgr_flag_task(0);
    task_mgr_flag_task(1);
    task_mgr_flag_task(0);
    task_mgr_flag_task(2);
    task_mgr_flag_task(3);
    task_mgr_flag_task(3);
    task_mgr_flag_task(0);
    task_mgr_remove(3);
    task_mgr_flag_task(9);

    // Only run if what we wanted to add happened
    while(b_add_success)
    {
        // App has its own while loop, no need to block
        task_mgr_task(false);

        // enter_low_power_mode(...) device specific
    }


    // If you get here, then a task failed to get added - fail out of program
    printf("Add task(s) failed\n");


    return b_add_success ? 0 : -1;
}
