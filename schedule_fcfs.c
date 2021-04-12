#include <stdlib.h>
#include <stdbool.h>
#include "schedulers.h"
#include "task.h"
#include "list.h"
#include "cpu.h"


nodetotal *tasks = NULL;
int unique_id = 0;

// add a task to the list
void add(char *name, int priority, int burst) {
    Task *new_task = malloc(sizeof(Task));
    new_task->burst = burst;
    new_task->name = name;
    new_task->priority = priority;
    new_task->tid = unique_id++;
    insert(&tasks, new_task);
}

// sort the tasks in the right order
nodetotal *sort(nodetotal *head) {
    nodetotal *newlist = NULL;
    for (nodetotal *tmp = tasks; tmp; tmp = tmp->next) {
        insert(&newlist, tmp->task);
    }
    return newlist;
}

// invoke the scheduler
void schedule() {
    nodetotal *reversed = sort(tasks);
    for (nodetotal *tmp = reversed; tmp; tmp = tmp->next) {
        run(tmp->task, tmp->task->burst);
    }
    free_list(reversed);
    free_list(tasks);
}
