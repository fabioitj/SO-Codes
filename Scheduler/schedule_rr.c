#include <stddef.h>
#include "schedule_rr.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

struct node *taskList = NULL;

void add(char *name, int priority, int burst) {
    Task *newTask = malloc(sizeof(Task));
    newTask->name = name;
    newTask->priority = priority;
    newTask->burst = burst;
    insert(&taskList, newTask);
}

void schedule() {
    const int timeSlice = 10;  // Tamanho do quantum para o Round Robin
    struct node *temp = taskList;
    int allTasksCompleted = 0;

    while (!allTasksCompleted) {
        temp = taskList;
        allTasksCompleted = 1;  // Assumimos que todas as tarefas foram concluídas

        while (temp != NULL) {
            if (temp->task->burst > 0) {
                allTasksCompleted = 0;  // Pelo menos uma tarefa não foi concluída

                if (temp->task->burst > timeSlice) {
                    run(temp->task, temp->task->burst);
                    temp->task->burst -= timeSlice;
                } else {
                    run(temp->task, temp->task->burst);
                    temp->task->burst = 0;
                }
            }

            temp = temp->next;
        }
    }
}



// void insert(struct node **head, Task *task) {
//     struct node *newNode = malloc(sizeof(struct node));
//     newNode->task = task;
//     newNode->next = NULL;

//     if (*head == NULL) {
//         *head = newNode;
//     } else {
//         struct node *temp = *head;
//         while (temp->next != NULL) {
//             temp = temp->next;
//         }
//         temp->next = newNode;
//     }
// }

// void delete(struct node **head, Task *task) {
//     if (*head == NULL) {
//         return;
//     }

//     struct node *temp = *head;
//     if (temp->task == task) {
//         *head = temp->next;
//         free(temp);
//         return;
//     }

//     struct node *prev = NULL;
//     while (temp != NULL && temp->task != task) {
//         prev = temp;
//         temp = temp->next;
//     }

//     if (temp == NULL) {
//         return;
//     }

//     prev->next = temp->next;
//     free(temp);
// }
