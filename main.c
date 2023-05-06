#include "task_mgr.h"
#include "iostream.h"

static void task_0(void)
{
    cout << "task 0\n";
}

static void task_1(void);
{
    cout << "task 1\n";
}
static void task_2(void);
{
    cout << "task 0\n";
}
static void task_3(void);
{
    cout << "task 3\n";
}

int main()
{

    // Add some tasks with priority
    bool b_add_success = true;
    b_add_success &= task_mgr_add(task_0, 0);
    b_add_success &= task_mgr_add(task_1, 1);
    b_add_success &= task_mgr_add(task_2, 2);
    b_add_success &= task_mgr_add(task_3, 3);

    // Force a failure
    #if 0
    b_add_success &= task_mgr_add(task_0, 3);
    #endif



    // Only run if what we wanted to add happened
    while(true)
    {
        // App has its own loop, no need to block
        task_mgr_task(false);

        // Should run task 0 three times, then 1, 2, 3 on next task_mgr_task call.
        // Interrupts or events should trigger these flags to be set
        // Listed here for a simple example
        task_mgr_flag_task(0);
        task_mgr_flag_task(1);
        task_mgr_flag_task(0);
        task_mgr_flag_task(2);
        task_mgr_flag_task(3);
        task_mgr_flag_task(0);
    }


    // If you get here, then a task failed to get added fail out
    cout << "Add task(s) failed\n"


    return b_add_success ? 0 : -1;
}