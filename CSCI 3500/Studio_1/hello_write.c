//Ayush Pathak and Samiksha Mailarpwar
//08_29_19
//Printing to the terminal
#include<unistd.h>

int main( int argc, char* argv[] ){
    char buffer[] = "Hello, world!\n;
    write(STDOUT_FILENO, buffer, 14);
    return 0;
}
