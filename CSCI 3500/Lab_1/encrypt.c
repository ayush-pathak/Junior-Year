//Ayush Pathak
#include<string.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

#include<stdio.h>
#include<rpc/des_crypt.h>

#include<errno.h>
#include<stdlib.h>
int main( int argc, char* argv[] ){
   //error checking parameters
   if(argc != 5){
     errno = 8;
     perror("Usage: <key> <input> <output> <mode>\n");
     exit(-1);
   }   
   
   if(strlen(argv[1]) != 8){
     errno = 22;
     perror("Error! Key must be of length 8\n");
     exit(-1);
   }
   
   int infd = open(argv[2], O_RDONLY);
   if(infd == -1 ){
      perror("Error!");
      exit(-1);
   }
   int outfd = open(argv[3], O_CREAT|O_WRONLY, S_IRUSR|S_IWUSR);
   if(outfd == -1){
      errno = 5;
      perror("Error! Could not create output file!\n");
      exit(-1);
   }
   //set up the buffer; using 8 as size as to minimize number of extra spaces added
   int i;
   int buffSize = 8;
   char buffer[buffSize];
   //inital read needed for while loop
   int readIn = read(infd, buffer, buffSize);
   if(readIn == -1){
     errno = 5;
     perror("Error! Could not read the input file!\n");
     exit(-1);
   }
      
   des_setparity(argv[1]);
   //endptr needed for strtol signature
   char* endptr;
   int mode = strtol(argv[4], &endptr, 10); 
   //while loop to keep reading until EOF
   while(readIn != 0){
      if(mode == 0){
         ecb_crypt(argv[1], buffer, buffSize, DES_ENCRYPT);
      }
      else if(mode == 1){
         ecb_crypt(argv[1], buffer, buffSize, DES_DECRYPT);
      }
      else{
         errno = 22;
         perror("Error! Mode must be a 0 or 1\n");
         exit(-1);
      }
      int writeCheck = write(outfd, buffer, buffSize);
      if(writeCheck == -1){
        errno = EIO;
        perror("Error! Could not write to output file!\n");
        exit(-1);
      }
      for(i=0; i<buffSize; i++){
         buffer[i] = ' ';
      }
      readIn = read(infd, buffer, buffSize);
      if(readIn == -1){
        errno = EIO;
        perror("Error! Could not read input file!\n");
        exit(-1);
      }
   }
   //close all open files
   int closeIn = close(infd);
   if (closeIn == -1){
      errno = EIO;
      perror("Error! Couldn't close input file.\n");
      exit(-1);
   }
   int closeOut = close(outfd);
   if(closeOut == -1){
      errno = EIO;
      perror("Error! Couldn't close output file.\n");
      exit(-1);
   }
} 
