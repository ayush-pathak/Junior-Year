//Ayush Pathak and Samiksha Mailarpwar
//09_3_18
//C implementation of cat

//File for read write
#include<unistd.h>
#define bufferSize 1
int main (int argc, char* argv[]){

   char buffer[ bufferSize ];
   while(1){
     int eof =read(STDIN_FILENO, buffer, bufferSize);
     if(eof == 0){
       break;
     }
   }
   write(STDOUT_FILENO, buffer, bufferSize);
}
