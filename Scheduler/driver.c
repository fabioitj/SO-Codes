#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "task.h"
#include "list.h"
#include "schedule_rr_p.h"

#define SIZE 100

char* strsep(char** stringp, const char* delim)
{
  char* start = *stringp;
  char* p;

  p = (start != NULL) ? strpbrk(start, delim) : NULL;

  if (p == NULL)
  {
    *stringp = NULL;
  }
  else
  {
    *p = '\0';
    *stringp = p + 1;
  }

  return start;
}


int main(int argc, char *argv[])
{
    clock_t start_time, end_time;
    double total_time;

    start_time = clock();

    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;

    in = fopen(argv[1],"r");
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));

        // add the task to the scheduler's list of tasks
        add(name,priority,burst);

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    schedule();


    end_time = clock();

    total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("\nO tempo de execução foi: %f segundos\n", total_time);

    return 0;
}
