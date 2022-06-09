/**********************************************************************/
/*                                                                    */
/* Program Name: scheduler - UNIX operating system scheduler.         */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS326, Operating Systems                             */
/* Date Written: April 3, 2022                                        */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/* I pledge this assignment is my own first time work.                */
/* I pledge I did not copy or try to copy any work from the Internet. */
/* I pledge the only person I asked for help from was my teacher.     */
/* I pledge I did not attempt to help any student on this assignment. */
/* I understand if I violate this pledge I will receive a 0 grade.    */
/*                                                                    */
/*                                                                    */
/*                      Signed: _____________________________________ */
/*                                           (signature)              */
/*                                                                    */
/*                                                                    */
/**********************************************************************/

/**********************************************************************/
/*                                                                    */
/*      This program simulates a UNIX operating system scheduler.     */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>

/**********************************************************************/
/*                          Symbolic Constants                        */
/**********************************************************************/
#define BEFORE             "BEFORE" /* Print BEFORE in the header.    */
#define AFTER              "AFTER"  /* Print AFTER in the header.     */
#define RUNNING_STATE      'N'      /* Process running state.         */
#define BLOCKED_STATE      'B'      /* Process blocked state.         */
#define READY_STATE        'R'      /* Process ready state.           */
#define SORT_STATE         'S'      /* Process sort state.            */
#define STARTING_PROCESSES 5        /* Number of starting processes.  */
#define MINIMUM_ID         1        /* Smallest process id number.    */
#define MAXIMUM_ID         100      /* Largest process id number.     */
#define MAXIMUM_PROCESSES  10       /* Max amount of table processes. */
#define MAXIMUM_CPU_TIME   18       /* Allotted CPU time per process. */
#define MAXIMUM_BLOCK_TIME 6        /* Allotted quantum per process.  */
#define CREATE_PROCESS     5        /* Chance to create new process.  */
#define UNBLOCK_PROCESS    20       /* Chance to unblock process.     */
#define HEADER_ALLOC_ERR   1        /* Header allocation error.       */
#define TRAILER_ALLOC_ERR  2        /* Trailer allocation error.      */
#define PROCESS_ALLOC_ERR  3        /* Process allocation error.      */
#define TABLE_HEADER       MINIMUM_ID - 1
                                    /* Table header id number.        */
#define TABLE_TRAILER      MAXIMUM_ID + 1
                                    /* Table trailer id number.       */

/**********************************************************************/
/*                          Program Structures                        */
/**********************************************************************/
/* Linked list of processes.                                          */
struct process
{
   int block_time,   /* Amount of quantum until the process blocks.   */
       cpu_used,     /* Total amount of time the CPU was used.        */
       max_time,     /* Total amount of time until the process ends.  */
       pid,          /* Process id number.                            */
       priority,     /* CPU priority level of the process.            */
       quantum_used, /* Current amount of quantum used.               */
       wait_ticks;   /* Amount of time a ready process has waited.    */
   char state;       /* Current status of the process.                */
   struct process *p_next_process;                 
                     /* Pointer to the next process in the list.      */
};
typedef struct process PROCESS;

/**********************************************************************/
/*                         Function Prototypes                        */
/**********************************************************************/
void change_priority(int next_pid, int processes,
                     int *p_running, int *p_context);
   /* Recalculate and change the priority of the process.             */
void create_process(int *p_next_pid, int *p_processes);
   /* Add new process to the process table.                           */
PROCESS *create_process_table();
   /* Create a process table.                                         */
void delete_process_table();
   /* Delete the process table from memory.                           */
void delete_running_process(int next_pid, int *p_processes,
                            int *p_running, int *p_context);
   /* Delete a running process from memory.                           */
void initialize_process(PROCESS *p_process, int *p_next_pid);
   /* Initialize process data.                                        */
void initialize_process_table(int *p_next_pid, int *p_processes);
   /* Add five starting processes to the process table.               */
void print_process_table(int next_pid, int processes, char when[]);
   /* Print the process table.                                        */
void set_running_process(int next_pid, int processes,
                         int *p_running, int *p_context);
   /* Set the next highest priority ready process to running.         */
void sort_process();
   /* Sort the process that has a sort state.                         */
void unblock_processes();
   /* Chance to unblock blocked processes.                            */
void update_ready_processes(int next_pid, int processes, int *p_context);
   /* Update the wait ticks on all ready processes.                   */
void update_running_process();
   /* Update the quantum values of the running process.               */

/**********************************************************************/
/*                          Global Variables                          */
/**********************************************************************/
PROCESS *p_process_table; /* Global pointer to the process table.     */

/**********************************************************************/
/*                            Main Function                           */
/**********************************************************************/
int main()
{
   int context = 0,           /* Shows when a context switch occurs.  */
       next_pid = MINIMUM_ID, /* Process id for newly added process.  */
       processes = 0,         /* Number of processes in the table.    */
       running = 0;           /* Shows when a process is running.     */

   /* Create and initialize a new process table.                      */
   p_process_table = create_process_table();
   initialize_process_table(&next_pid, &processes);

   /* Interrupt the CPU until the highest process id is created.      */
   while (next_pid <= MAXIMUM_ID)
   {
      /* Delete a process that reaches it's maximum time on the CPU.  */
      delete_running_process(next_pid, &processes, &running, &context);

      /* Change the priorty of the process that stopped running.      */
      change_priority(next_pid, processes, &running, &context);

      /* Sort the process that has a sort state.                      */
      sort_process();

      /* Set the next highest priority ready process to running.      */
      set_running_process(next_pid, processes, &running, &context);
      
      /* Increment the wait ticks of any ready processes by 1.        */
      update_ready_processes(next_pid, processes, &context);

      /* Increment the quantum values of the running process by 1.    */ 
      update_running_process();

      /* Chance to unblock any blocked processes.                     */
      unblock_processes();

      /* Chance to create a new process in the process table.         */
      create_process(&next_pid, &processes);
   }

   /* Delete process table from allocated memory and terminate.       */
   delete_process_table();
   return 0;
}

/**********************************************************************/
/*         Recalculate and change the priority of the process.        */
/**********************************************************************/
void change_priority(int next_pid, int processes,
                     int *p_running, int *p_context)
{
   PROCESS *p_process;

   p_process = p_process_table->p_next_process;
   while (p_process->quantum_used != p_process->block_time &&
          p_process->pid != TABLE_TRAILER)
   {
      p_process = p_process->p_next_process;
   }

   if (p_process->pid != TABLE_TRAILER)
   {
      if (*p_context == 0)
      {
         print_process_table(next_pid, processes, BEFORE);
         *p_context = 1;
      }

      if (p_process->block_time == MAXIMUM_BLOCK_TIME)
      {
         if ((abs(p_process->priority) + p_process->quantum_used) % 2)
         {
            p_process->priority = ((abs(p_process->priority) +
               p_process->quantum_used) * 0.5f) + 1.0f;
         }
         else
         {
            p_process->priority = (abs(p_process->priority) +
               p_process->quantum_used) * 0.5f;
         }
      }
      else
      {
         if ((abs(p_process->priority) + p_process->quantum_used) % 2)
         {
            p_process->priority = ((abs(p_process->priority) +
               p_process->quantum_used) * 0.5f) + 1.0f;
            p_process->priority = -p_process->priority;
         }
         else
         {
            p_process->priority = (abs(p_process->priority) +
               p_process->quantum_used) * 0.5f;
            p_process->priority = -p_process->priority;
         }
      }
      p_process->state = SORT_STATE;
      p_process->quantum_used = 0;
      *p_running = 0;
   }
   return;
}

/**********************************************************************/
/*         Create and add a new process to the process table.         */
/**********************************************************************/
void create_process(int *p_next_pid, int *p_processes)
{
   PROCESS *p_process,
           *p_new_process; /* Pointer to the new process.             */

   if (*p_processes < MAXIMUM_PROCESSES && rand() % CREATE_PROCESS == 0)
   {
      p_process = p_process_table;
      if ((p_new_process = (PROCESS *) malloc(sizeof(PROCESS))) == NULL)
      {
         printf("\nError #%d in create_new_process.", PROCESS_ALLOC_ERR);
         printf("\nCannot allocate memory for the process.");
         printf("\nThe program is aborting.");
         exit(PROCESS_ALLOC_ERR);
      }
      initialize_process(p_new_process, p_next_pid);

      while (abs(p_new_process->priority) >=
             p_process->p_next_process->priority &&
             p_process->p_next_process->pid != TABLE_TRAILER)
      {
         p_process = p_process->p_next_process;
      }
      p_new_process->p_next_process = p_process->p_next_process;
      p_process->p_next_process = p_new_process;
      (*p_processes)++;
   }
   return;
}

/**********************************************************************/
/*                     Create a new process table.                    */
/**********************************************************************/
PROCESS *create_process_table()
{
   PROCESS *p_new_table; /* Pointer to the new process table.         */

   if ((p_new_table = (PROCESS *) malloc(sizeof(PROCESS))) == NULL)
   {
      printf("\nError #%d in create_process_table.", HEADER_ALLOC_ERR);
      printf("\nCannot allocate memory for the process header.");
      printf("\nThe program is aborting.");
      exit(HEADER_ALLOC_ERR);
   }
   p_new_table->pid = TABLE_HEADER;

   if ((p_new_table->p_next_process = (PROCESS *)
                                       malloc(sizeof(PROCESS))) == NULL)
   {
      printf("\nError #%d in create_process_table.", TRAILER_ALLOC_ERR);
      printf("\nCannot allocate memory for the process trailer.");
      printf("\nThe program is aborting.");
      exit(TRAILER_ALLOC_ERR);
   }
   p_new_table->p_next_process->pid = TABLE_TRAILER;
   p_new_table->p_next_process->p_next_process = NULL;

   return p_new_table;
}

/**********************************************************************/
/*               Delete a process from allocated memory.              */
/**********************************************************************/
void delete_running_process(int next_pid, int *p_processes,
                            int *p_running, int *p_context)
{
   PROCESS *p_process,
           *p_previous; /* Pointer to the previous process.           */

   p_previous = p_process_table;
   p_process = p_process_table->p_next_process;
   while (p_process->cpu_used != p_process->max_time &&
          p_process->pid != TABLE_TRAILER)
   {
      p_previous = p_process;
      p_process = p_process->p_next_process;
   }

   if (p_process->pid != TABLE_TRAILER)
   {
      if (*p_context == 0)
      {
         print_process_table(next_pid, *p_processes, BEFORE);
         *p_context = 1;
      }

      p_previous->p_next_process = p_process->p_next_process;
      free(p_process);
      (*p_processes)--;
      *p_running = 0;
   }
   return;
}

/**********************************************************************/
/*           Delete the process table from allocated memory.          */
/**********************************************************************/
void delete_process_table()
{
   PROCESS *p_process; /* Pointer to a process.                       */

   p_process = p_process_table;
   while (p_process_table->pid != TABLE_TRAILER)
   {
      p_process = p_process_table;
      p_process_table = p_process_table->p_next_process;
      free(p_process);
   }
   free(p_process_table);

   return;
}

/**********************************************************************/
/*                      Initialize process data.                      */
/**********************************************************************/
void initialize_process(PROCESS *p_process, int *p_next_pid)
{
   if (rand() % 3)
   {
      p_process->block_time = rand() % (MAXIMUM_BLOCK_TIME - 1) + 1;
   }
   else
   {
      p_process->block_time = MAXIMUM_BLOCK_TIME;
   }
   p_process->cpu_used = 0;
   p_process->pid = (*p_next_pid)++;
   p_process->priority = 0;
   p_process->max_time = rand() % MAXIMUM_CPU_TIME + 1;
   p_process->quantum_used = 0;
   p_process->wait_ticks = 0;
   p_process->state = READY_STATE;

   return;
}

/**********************************************************************/
/*          Add five starting processes to the process table.         */
/**********************************************************************/
void initialize_process_table(int *p_next_pid, int *p_processes)
{
   PROCESS *p_process,
           *p_new_process; /* Pointer to the new process.             */
   int     count;          /* Count the number of loops.              */

   p_process = p_process_table;
   for (count = 0; count < STARTING_PROCESSES; count++)
   {
      if ((p_new_process = (PROCESS *) malloc(sizeof(PROCESS))) == NULL)
      {
         printf("\nError #%d in create_new_process.", PROCESS_ALLOC_ERR);
         printf("\nCannot allocate memory for the process.");
         printf("\nThe program is aborting.");
         exit(PROCESS_ALLOC_ERR);
      }
      initialize_process(p_new_process, p_next_pid);

      while (p_process->p_next_process->pid != TABLE_TRAILER)
      {
         p_process = p_process->p_next_process;
      }
      p_new_process->p_next_process = p_process->p_next_process;
      p_process->p_next_process = p_new_process;
      (*p_processes)++;
   }
   return;
}

/**********************************************************************/
/*                      Print the process table.                      */
/**********************************************************************/
void print_process_table(int next_pid, int processes, char when[])
{
   PROCESS *p_process;
   
   printf("\n\n %s SCHEDULING CPU:  Next PID = %2d", when, next_pid);
   printf(",  Number of Processes = %2d", processes);
   printf("\n PID   CPU Used   MAX Time   STATE   PRI ");
   printf("  QUANTUM USED   BLK TIME   WAIT TKS");

   p_process = p_process_table->p_next_process;
   while (p_process->pid != TABLE_TRAILER)
   {
      printf("\n %3d",         p_process->pid);
      printf("      %2d",      p_process->cpu_used);
      printf("         %2d",   p_process->max_time);
      printf("        %c",     p_process->state);
      printf("      %2d",      p_process->priority);
      printf("        %2d",    p_process->quantum_used);
      printf("           %2d", p_process->block_time);
      printf("         %3d",   p_process->wait_ticks);
      p_process = p_process->p_next_process;
   }
   return;
}

/**********************************************************************/
/*      Set the next highest priority ready process to running.       */
/**********************************************************************/
void set_running_process(int next_pid, int processes,
                         int *p_running, int *p_context)
{
   PROCESS *p_process;

   if (*p_running == 0)
   {
      p_process = p_process_table->p_next_process;
      while (p_process->state != READY_STATE &&
             p_process->pid != TABLE_TRAILER)
      {
         p_process = p_process->p_next_process;
      }

      if (p_process->pid != TABLE_TRAILER)
      {
         if (*p_context == 0)
         {
            print_process_table(next_pid, processes, BEFORE);
            *p_context = 1;
         }

         p_process->state = RUNNING_STATE;
         *p_running = 1;
      }
   }
   return;
}

/**********************************************************************/
/*                Sort the process based on priority.                 */
/**********************************************************************/
void sort_process()
{
   PROCESS *p_process,
           *p_previous, /* Pointer to the previous process.           */
           *p_target;   /* Pointer to the target process.             */

   p_previous = p_process_table;
   p_process = p_process_table->p_next_process;
   while (p_process->state != SORT_STATE &&
          p_process->pid != TABLE_TRAILER)
   {
      p_previous = p_process;
      p_process = p_process->p_next_process;
   }

   if (p_process->pid != TABLE_TRAILER)
   {
      p_target = p_process;
      p_previous->p_next_process = p_process->p_next_process;
      p_previous = p_process_table;
      p_process = p_process_table->p_next_process;
      if (p_target->priority >= 0)
      {
         p_target->state = READY_STATE;
         while (abs(p_target->priority) >= p_process->priority &&
                p_process->pid != TABLE_TRAILER)
         {
            p_previous = p_process;
            p_process = p_process->p_next_process;
         }
      }
      else
      {
         p_target->state = BLOCKED_STATE;
         while (abs(p_target->priority) >= abs(p_process->priority) &&
                p_process->priority < 0 &&
                p_process->pid != TABLE_TRAILER)
         {
            p_previous = p_process;
            p_process = p_process->p_next_process;
         }
      }
      p_target->p_next_process = p_process;
      p_previous->p_next_process = p_target;
   }
   return;
}

/**********************************************************************/
/*                Chance to unblock blocked processes.                */
/**********************************************************************/
void unblock_processes()
{
   PROCESS *p_process;

   p_process = p_process_table->p_next_process;
   while (p_process->pid != TABLE_TRAILER)
   {
      if (p_process->state == BLOCKED_STATE &&
          rand() % UNBLOCK_PROCESS == 0)
      {
         p_process->state = READY_STATE;
      }
      p_process = p_process->p_next_process;
   }
   return;
}

/**********************************************************************/
/*           Update the wait ticks on all ready processes.            */
/**********************************************************************/
void update_ready_processes(int next_pid, int processes, int *p_context)
{
   PROCESS *p_process;

   if (*p_context == 1)
   {
      print_process_table(next_pid, processes, AFTER);
      *p_context = 0;
   }

   p_process = p_process_table->p_next_process;
   while (p_process->pid != TABLE_TRAILER)
   {
      if (p_process->state == READY_STATE)
      {
         p_process->wait_ticks++;
      }
      p_process = p_process->p_next_process;
   }
   return;
}

/**********************************************************************/
/*         Update the quantum values of the running process.          */
/**********************************************************************/
void update_running_process()
{
   PROCESS *p_process;

   p_process = p_process_table;
   while (p_process->state != RUNNING_STATE &&
          p_process->pid != TABLE_TRAILER)
   {
      p_process = p_process->p_next_process;
   }

   if (p_process->pid != TABLE_TRAILER)
   {
      p_process->cpu_used++;
      p_process->quantum_used++;
   }
   return;
}
