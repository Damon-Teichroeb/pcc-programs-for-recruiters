#define STD_INPUT  0     /* File descriptor for standard output.           */
#define STD_OUTPUT 1     /* File descriptor for standard input.            */
pipeline(char* process1, char* process2, char* process3)
{                        /* Create a pipline that points to user commands. */
   int fd[4];            /* Create the file descriptors.                   */
   pipe(&fd[0]);         /* Create the first pipe.                         */
   pipe(&fd[2]);         /* Create the second pipe.                        */
   if (fork() != 0)      /* Create a child process and check the process   */
   {                     /*      id of both the parent and the child.      */
      /*                Only execute in the parent process.                */
      /*===================================================================*/
      close(fd[0]);      /* Process 1 does not need to read from pipe 1.   */
      close(fd[2]);      /* Process 1 does not need to read from pipe 2.   */
      close(fd[3]);      /* Process 1 does not need to write to pipe 2.    */
      close(STD_OUTPUT); /* Prepare for new standard output.               */
      dup(fd[1]);        /* Set the standard output to write to pipe 1.    */
      close(fd[1]);      /* Close the write file descriptor on pipe 1.     */
      execl(process1, process1, 0);
                         /* Overwrite all the code and make  it into the   */
   }                     /*             user's first command.              */
   else if (fork() != 0) /* Create a child process and check the process   */                   
   {                     /*      id of both the parent and the child.      */
      /*              Only execute in the first child process.             */
      /*===================================================================*/
      close(fd[1]);      /* Process 2 does not need to write to pipe 1.    */
      close(fd[2]);      /* Process 2 does not need to read from pipe 2.   */
      close(STD_INPUT);  /* Prepare for new standard input.                */
      dup(fd[0]);        /* Set the standard input to read from pipe 1.    */
      close(fd[0]);      /* Close the read file descriptor on pipe 1.      */
      close(STD_OUTPUT); /* Prepare for new standard output.               */
      dup(fd[3]);        /* Set the standard output to write to pipe 2.    */
      close(fd[3]);      /* Close the write file descriptor on pipe 2.     */
      execl(process2, process2, 0);
                         /* Overwrite all the code and make it into the    */
   }                     /*             user's second command.             */
   else                  /* Run the final process.                         */
   {  /*              Only execute in the second child process.            */
      /*===================================================================*/
      close(fd[0]);      /* Process 3 does not need to read from pipe 1.   */
      close(fd[1]);      /* Process 3 does not need to write to pipe 1.    */
      close(fd[3]);      /* Process 3 does not need to write to pipe 2.    */
      close(STD_INPUT);  /* Prepare for new standard input.                */
      dup(fd[2]);        /* Set the standard input to read from pipe 2.    */
      close(fd[2]);      /* Close the read file descriptor on pipe 2.      */
      execl(process3, process3, 0);
                         /* Overwrite all the code and make it into the    */
                         /*             user's third command.              */
   }
}
/*          This is my own first time work I did not receive help          */
/*                 from anywhere else except my teacher.  -Damon Teichroeb */