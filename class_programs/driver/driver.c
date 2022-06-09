/**********************************************************************/
/*                                                                    */
/* Program Name: driver - Simulates a UNIX Operating System Driver    */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS326, Operating Systems                             */
/* Date Written: May 1, 2022                                          */
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
/* This program acts as a UNIX Operating System driver by             */
/* communicating with both the DISK drive and the FILE SYSTEM to      */
/* process FILES SYSTEM requests and complete DISK operations.        */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**********************************************************************/
/*                         Symbolic Constants                         */
/**********************************************************************/
#define TRUE                1     /* Boolean true                     */
#define BLOCKS_PER_DISK     360   /* Number of blocks on the DISK     */
#define BYTES_PER_BLOCK     1024  /* Number of bytes per block        */
#define BYTES_PER_SECTOR    512   /* Number of bytes per sector       */
#define CYLINDERS_PER_DISK  40    /* Number of cylinders on the DISK  */
#define TRACKS_PER_CYLINDER 2     /* Number of tracks per cylinder    */
#define SECTORS_PER_TRACK   9     /* Number of sectors per track      */
#define SPOOL_DRIVE_MOTOR   3     /* Max seconds for motor startup    */
#define SENSE_CYLINDER      1     /* Sense DISK heads cylinder        */
#define SEEK_CYLINDER       2     /* Send DISK heads to cylinder      */
#define DMA_SETUP           3     /* Prepare DMA registers            */
#define START_DRIVE_MOTOR   4     /* Turn on DISK drive motors        */
#define DRIVE_MOTOR_STATUS  5     /* Check drive motor status         */
#define READ_DISK           6     /* Read data from the DISK          */
#define WRITE_DISK          7     /* Write data to the DISK           */
#define STOP_DRIVE_MOTOR    8     /* Turn off DISK drive motor        */
#define RECALIBRATE_HEADS   9     /* Reset DISK heads to cylinder 0   */
#define LIST_LENGTH         20    /* Array length of requests list    */
#define MAX_REQUEST_NUMBER  32767 /* Highest request number           */
#define DISK_DRIVE_ERROR    -1    /* Read or write error code         */
#define BAD_OPERATION_CODE  -1    /* Bad operation code error number  */
#define BAD_REQUEST_NUMBER  -2    /* Bad request number error number  */
#define BAD_BLOCK_NUMBER    -4    /* Bad block number error number    */
#define BAD_BLOCK_SIZE      -8    /* Bad block size error number      */
#define BAD_DATA_ADDRESS    -16   /* Bad data address error number    */

/**********************************************************************/
/*                         Program Structures                         */
/**********************************************************************/
struct message
{                int operation_code;  /* Disk operation code          */
                 int request_number;  /* Unique request number        */
                 int block_number;    /* Block number to read/write   */
                 int block_size;      /* Block size in bytes          */
   unsigned long int *p_data_address; /* Unique address number        */
};
struct message fs_message[LIST_LENGTH];

struct pending_request
{                int operation_code;  /* Disk operation code          */
                 int request_number;  /* Unique request number        */
                 int block_number;    /* Block number to read/write   */
                 int block_size;      /* Block size in bytes          */
   unsigned long int *p_data_address; /* Unique address number        */
};
struct pending_request request[LIST_LENGTH];

/**********************************************************************/
/*                         Function Prototypes                        */
/**********************************************************************/
void bubble_down_requests();
   /* Bubble sort down the pending requests list                      */
void bubble_up_requests(int cylinder_number);
   /* Bubble sort up the pending requests list                        */
int check_request();
   /* Validate the current request                                    */
void convert_block(int block_number, int *p_cylinder_number,
                             int *p_track_number, int *p_sector_number);
   /* Convert a block number into cylinder, track, and sector numbers */
int disk_drive(int, int, int, int, long unsigned int*);
   /* Send an operation request to the DISK                           */
void fill_message();
   /* Fill the FILE SYSTEM message array with the finished request    */
void get_pending_requests(int *p_pending_requests);
   /* Get the pending requests list from the FILE SYSTEM              */
void move_to_cylinder(int cylinder_number,
                   int temp_cylinder_number, int *p_drive_motor_status);
   /* Move DISK heads to a cylinder                                   */
void read_from_disk();
   /* Read data from the DISK drive                                   */
void send_message(struct message*);
   /* Send the message structure to the FILE SYSTEM                   */
void start_disk_drive();
   /* Startup the DISK drive                                          */
void swap_structure_data(int index, int index2);
   /* Swap structure data values                                      */
void write_to_disk();
   /* Write data to the DISK drive                                    */

/**********************************************************************/
/*                            Main Function                           */
/**********************************************************************/
int main()
{
   int cylinder_number,      /* Cylinder number on the DISK           */
       drive_motor_status,   /* Current status of the drive motor     */
       idle_counter,         /* Number of idle messages sent          */
       pending_requests,     /* Current number of pending requests    */
       sector_number,        /* Sector number on a DISK track         */
       temp_cylinder_number, /* Temporary cylinder number             */
       track_number;         /* Track number on a DISK cylinder       */

   /* Initialize driver                                               */
   pending_requests   = 0;
   idle_counter       = 0;
   drive_motor_status = 1;
   send_message(fs_message);

   /* Loop processing of pending requests                             */
   while (TRUE)
   {
      /* Get the pending requests list and sort the requests          */
      get_pending_requests(&pending_requests);
      bubble_down_requests();
      bubble_up_requests(cylinder_number);

      /* Process a pending request or empty request                   */
      if (request->operation_code != 0)
      {
         idle_counter = 0;
         if (check_request() == 0)
         {
            /* Start the DISK drive motor and sort the request list   */
            convert_block(request->block_number, &cylinder_number,
                                         &track_number, &sector_number);
            if (drive_motor_status)
            {
               start_disk_drive();
               temp_cylinder_number =
                                 disk_drive(SENSE_CYLINDER, 0, 0, 0, 0);
               bubble_down_requests();
               bubble_up_requests(temp_cylinder_number);
               convert_block(request->block_number, &cylinder_number,
                                         &track_number, &sector_number);
            }

            /* Move DISK heads to a cylinder                          */
            move_to_cylinder(cylinder_number, temp_cylinder_number,
                                                   &drive_motor_status);

            /* Setup DMA and perform a read or write on the DISK      */
            if (disk_drive(DMA_SETUP, sector_number, track_number,
                          request->block_size, request->p_data_address))
            {
               printf("\nError occurred in main().");
               printf("\nDMA setup failed");
               printf(" with error code: %d!", DISK_DRIVE_ERROR);
               exit(DISK_DRIVE_ERROR);
            }
            if (request->operation_code == 1)
               read_from_disk();
            else
               write_to_disk();
            request->operation_code = 0;
         }
         pending_requests -= 1;
      }
      else
         idle_counter += 1;

      /* Stop the DISK drive motor if 2 idle messages are received    */
      if (idle_counter == 2 && drive_motor_status == 0)
      {
         disk_drive(STOP_DRIVE_MOTOR, 0, 0, 0, 0);
         drive_motor_status = 1;
      }

      /* Send the finished request back to the FILE SYSTEM            */
      fill_message(&pending_requests);
      send_message(fs_message);
   }
   return 0;
}

/**********************************************************************/
/*        Get the pending requests list from the FILE SYSTEM          */
/**********************************************************************/
void get_pending_requests(int *p_pending_requests)
{
   int index; /* FILE SYSTEM message array index                      */

   index = 0;
   while (fs_message[index].operation_code != 0 &&
          index < LIST_LENGTH)
   {
      *p_pending_requests += 1;
      request[*p_pending_requests].operation_code =
                                       fs_message[index].operation_code;
      request[*p_pending_requests].request_number =
                                       fs_message[index].request_number;
      request[*p_pending_requests].block_number   =
                                         fs_message[index].block_number;
      request[*p_pending_requests].block_size     =
                                           fs_message[index].block_size;
      request[*p_pending_requests].p_data_address =
                                       fs_message[index].p_data_address;
      index += 1;      
   }
   return;
}

/**********************************************************************/
/*             Bubble sort down the pending requests list             */
/**********************************************************************/
void bubble_down_requests()
{
   int outer_index; /* Outer while loop array index                   */
   int inner_index; /* Inner while loop array index                   */

   outer_index = 0;
   while ((request[outer_index].operation_code != 0 &&
          outer_index < LIST_LENGTH) ||
          outer_index == 0)
   {
      inner_index = 0;
      while (request[inner_index + 1].operation_code != 0 &&
             inner_index < LIST_LENGTH)
      {
         if (request[inner_index].block_number >
             request[inner_index + 1].block_number ||
             request[inner_index].operation_code == 0)
            swap_structure_data(inner_index, inner_index + 1);
         inner_index += 1;
      }
      outer_index += 1;
   }
   return;
}

/**********************************************************************/
/*              Bubble sort up the pending requests list              */
/**********************************************************************/
void bubble_up_requests(int cylinder_number)
{
   int upper_index,  /* Upper index of the pending requests list      */
       lower_index,  /* Lower index of the pending requests list      */
       target_index; /* Target index of the data to be swapped        */

   upper_index = 0;
   lower_index = 0;
   while (request[lower_index].operation_code != 0 &&
          lower_index < LIST_LENGTH)
   {
      if (request[lower_index].block_number >
                                    cylinder_number * SECTORS_PER_TRACK)
      {
         target_index = lower_index;
         while (target_index > upper_index)
         {
            swap_structure_data(target_index, target_index - 1);
            target_index -= 1;
         }
         upper_index += 1;
      }
      lower_index += 1;
   }
   return;
}

/**********************************************************************/
/*  Convert a block number into cylinder, track, and sector numbers   */
/**********************************************************************/
void convert_block(int block_number, int *p_cylinder_number,
                              int *p_track_number, int *p_sector_number)
{
   *p_cylinder_number = (block_number - 1) / SECTORS_PER_TRACK;

   if ((block_number - 1) % SECTORS_PER_TRACK < SECTORS_PER_TRACK *0.5f)
      *p_track_number = 0;
   else
      *p_track_number = 1;

   *p_sector_number =
           (block_number - 1) % SECTORS_PER_TRACK * TRACKS_PER_CYLINDER;
   if (*p_sector_number >= SECTORS_PER_TRACK)
      *p_sector_number -= SECTORS_PER_TRACK;

   return;
}

/**********************************************************************/
/*                       Startup the DISK drive                       */
/**********************************************************************/
void start_disk_drive()
{
   if (disk_drive(START_DRIVE_MOTOR, 0, 0, 0, 0))
      while (disk_drive(DRIVE_MOTOR_STATUS, 0, 0, 0, 0));

   return;
}

/**********************************************************************/
/*                    Validate the current request                    */
/**********************************************************************/
int check_request()
{
   int    error_sum;   /* Sum of all occuring error numbers           */
   double square_root; /* Square root of the block size in bytes      */

   error_sum = 0;
   if (request->operation_code < 0 ||
       request->operation_code > 2)
   {
      request->operation_code = BAD_OPERATION_CODE;
      error_sum += BAD_OPERATION_CODE;
   }
   if (request->request_number < 1 ||
       request->request_number > MAX_REQUEST_NUMBER)
   {
      request->operation_code = BAD_REQUEST_NUMBER;
      error_sum += BAD_REQUEST_NUMBER;
   }
   if (request->block_number < 1 ||
       request->block_number > BLOCKS_PER_DISK)
   {
      request->operation_code = BAD_BLOCK_NUMBER;
      error_sum += BAD_BLOCK_NUMBER;
   }
   if (request->block_size != BYTES_PER_BLOCK)
   {
      square_root = sqrt(request->block_size);
      while (square_root > 2.0)
         square_root = sqrt(square_root);
      if ((int)square_root != 2 ||
          request->block_size < 0 ||
          request->block_size >
             TRACKS_PER_CYLINDER * SECTORS_PER_TRACK * BYTES_PER_SECTOR)
      {
         request->operation_code = BAD_BLOCK_SIZE;
         error_sum += BAD_BLOCK_SIZE;
      }
   }
   if (request->p_data_address < 0)
   {
      request->operation_code = BAD_DATA_ADDRESS;
      error_sum += BAD_DATA_ADDRESS;
   }
   if (error_sum)
      request->operation_code = error_sum;

   return error_sum;
}

/**********************************************************************/
/*                    Move DISK heads to a cylinder                   */
/**********************************************************************/
void move_to_cylinder(int cylinder_number, int temp_cylinder_number,
                                              int *p_drive_motor_status)
{
   if (*p_drive_motor_status)
   {
      if (temp_cylinder_number != cylinder_number)
         while (disk_drive(SEEK_CYLINDER, cylinder_number, 0, 0, 0) !=
                                                        cylinder_number)
         {
            while (disk_drive(RECALIBRATE_HEADS, 0, 0, 0, 0));
            if (cylinder_number == 0)
               break;
         }
      *p_drive_motor_status = 0;
   }
   else
   {
      if (disk_drive(SENSE_CYLINDER, 0, 0, 0, 0) != cylinder_number)
         while (disk_drive(SEEK_CYLINDER, cylinder_number, 0, 0, 0) !=
                                                        cylinder_number)
         {
            while (disk_drive(RECALIBRATE_HEADS, 0, 0, 0, 0));
            if (cylinder_number == 0)
               break;
         }
   }
   return;
}

/**********************************************************************/
/*                    Read data from the DISK drive                   */
/**********************************************************************/
void read_from_disk()
{
   int status_code; /* The returned status of the DISK drive function */

   while ((status_code = disk_drive(READ_DISK, 0, 0, 0, 0)))
   {
      if (status_code)
      {
         if (status_code == DISK_DRIVE_ERROR)
         {
            printf("\nError occurred in read_from_disk().");
            printf("\nDisk read failed");
            printf(" with error code: %d!", DISK_DRIVE_ERROR);
            exit(DISK_DRIVE_ERROR);
         }
      }
      else
         break;
   }
   return;
}

/**********************************************************************/
/*                   Write data to the DISK drive                     */
/**********************************************************************/
void write_to_disk()
{
   int status_code; /* The returned status of the DISK drive function */

   while ((status_code = disk_drive(WRITE_DISK, 0, 0, 0, 0)))
   {
      if (status_code)
      {
         if (status_code == DISK_DRIVE_ERROR)
         {
            printf("\nError occurred in write_to_disk().");
            printf("\nDisk write failed");
            printf(" with error code: %d!", DISK_DRIVE_ERROR);
            exit(DISK_DRIVE_ERROR);
         }      
      }
      else
         break;
   }
   return;
}

/**********************************************************************/
/*                     Swap structure data values                     */
/**********************************************************************/
void swap_structure_data(int index1, int index2)
{
                 int temp_block_number,
                                      /* Temporary block number       */
                     temp_block_size, /* Temporary block size bytes   */
                     temp_operation_code,
                                      /* Temporary operation code     */
                     temp_request_number;
                                      /* Temporary request number     */
   unsigned long int *p_temp_data_address;
                                      /* Temporary address pointer    */

   temp_operation_code = request[index1].operation_code;
   temp_request_number = request[index1].request_number;
   temp_block_number   = request[index1].block_number;
   temp_block_size     = request[index1].block_size;
   p_temp_data_address = request[index1].p_data_address;

   request[index1].operation_code = request[index2].operation_code;
   request[index1].request_number = request[index2].request_number;
   request[index1].block_number   = request[index2].block_number;
   request[index1].block_size     = request[index2].block_size;
   request[index1].p_data_address = request[index2].p_data_address;

   request[index2].operation_code = temp_operation_code;
   request[index2].request_number = temp_request_number;
   request[index2].block_number   = temp_block_number;
   request[index2].block_size     = temp_block_size;
   request[index2].p_data_address = p_temp_data_address;

   return;
}

/**********************************************************************/
/*    Fill the FILE SYSTEM message array with the finished request    */
/**********************************************************************/
void fill_message()
{
   fs_message->operation_code = request->operation_code;
   fs_message->request_number = request->request_number;
   fs_message->block_number   = request->block_number;
   fs_message->block_size     = request->block_size;
   fs_message->p_data_address = request->p_data_address;

   request->operation_code = 0;
   request->request_number = 0;
   request->block_number   = 0;
   request->block_size     = 0;
   request->p_data_address = NULL;

   return;
}
