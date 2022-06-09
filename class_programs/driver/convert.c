/**********************************************************************/
/*                                                                    */
/* Program Name: convert - Convert Disk Blocks                        */
/* Author:       Damon L. Teichroeb                                   */
/* Installation: Pensacola Christian College, Pensacola, Florida      */
/* Course:       CS326, Operating Systems                             */
/* Date Written: April 12, 2022                                       */
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
/*   This program converts disk block numbers into cylinder, track,   */
/*         and sector numbers, and then prints those numbers.         */
/*                                                                    */
/**********************************************************************/

#include <stdio.h>

/**********************************************************************/
/*                         Symbolic Constants                         */
/**********************************************************************/
#define BLOCK_SIZE  1024 /* Number of bytes per block                 */
#define SECTOR_SIZE 512  /* Number of bytes per sector                */
#define CYLINDERS   40   /* Number of cylinders per disk              */
#define TRACKS      2    /* Number of tracks per cylinder             */
#define SECTORS     9    /* Number of sectors per track               */

/**********************************************************************/
/*                         Function Prototypes                        */
/**********************************************************************/
void convert_block(int block, int *p_cyl, int *p_track, int *p_sector);
   /* Convert a block number into cylinder, track, and sector numbers */

/**********************************************************************/
/*                            Main Function                           */
/**********************************************************************/
int main()
{
   int block,    /* Stores the disk block number                      */
       cylinder, /* Stores the disk cylinder number                   */
       track,    /* Stores the disk track number                      */
       sector;   /* Stores the disk sector number                     */

   /* Print the disk header                                           */
   printf("\n Block    Cylinder    Track    Sector");
   printf("\n-------  ----------  -------  --------");

   /* Convert blocks and print the block, cylinder, track, and sector */
   for (block = 1; block <= 360; block++)
   {
      convert_block(block, &cylinder, &track, &sector);
      printf("\n  %3d        %2d  ", block, cylinder);
      printf("       %d         %d", track, sector);
   }
   return 0;
}

/**********************************************************************/
/*  Convert a block number into cylinder, track, and sector numbers   */
/**********************************************************************/
void convert_block(int block, int *p_cyl, int *p_track, int *p_sector)
{
   int sector; /* Stores the calculated sector number                 */

   *p_cyl = (block - 1) / SECTORS;
   
   if ((block - 1) % SECTORS < SECTORS * 0.5f)
      *p_track = 0;
   else
      *p_track = 1;

   sector = (block - 1) % SECTORS * TRACKS;
   if (sector < SECTORS)
      *p_sector = sector;
   else
      *p_sector = sector - SECTORS;

   return;
}