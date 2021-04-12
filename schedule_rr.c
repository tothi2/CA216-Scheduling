#include <stdlib.h>
#include <stdbool.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"

node_t *tasks = NULL;
int unique_id = 0;

// add a task to the list
void add(char *name, int priority, int burst)
{
    Task *new_task = malloc(sizeof(Task));
    new_task->burst = burst;
    new_task->name = name;
    new_task->priority = priority;
    new_task->tid = unique_id++;
    insert(&tasks, new_task);
}

// sort the tasks in the right order
node_t *sort(node_t *head)
{
    node_t *newlist = NULL;
    for (node_t *tmp = tasks; tmp; tmp = tmp->next)
    {
        insert(&newlist, tmp->task);
    }
    return newlist;
}

void clear(node_t **head)
{
    bool still = false;
    do
    {
        node_t *to_rm = NULL;
        for (node_t *tmp = *head; tmp; tmp = tmp->next)
        {
            if (tmp->task->burst == 0)
            {
                to_rm = tmp;
                break;
            }
        }
        if (to_rm != NULL)
        {
            delete (head, to_rm->task);
        }
        still = to_rm != NULL;
    } while (still);
}

// invoke the scheduler
void schedule()
{
    while (tasks != NULL)
    {
        for (node_t *tmp = tasks; tmp; tmp = tmp->next)
        {
            int burst = tmp->task->burst > 10 ? 10 : tmp->task->burst;
            run(tmp->task, burst);
            tmp->task->burst -= burst;
        }
        clear(&tasks);
    }
    free_list(tasks);
}
