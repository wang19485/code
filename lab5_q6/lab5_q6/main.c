//File named "lab5_prob6.c"
#include <stdio.h>
int very_fast_function(int i){
    //int result;
    if ( (i*64 +1) > 1024) {return i++;}
    else {return 0;}
    /*asm("movl $64, %%ebx;\n\t"
                         "movl $1024, %%ecx;"
                         "movl $1, %%edx;"
                         "movl %1, %%esi;"
                         "imul %%ebx %%esi;"
                         "addl %%edx, %%esi;"
                         "movl %%esi,%%eax;"
                         "subl %%ecx,%%eax;"
          
                         "jle L2;"
                         "movl %%edx, %%eax;"
                         "addl %%eax,%0;"
                         //"halt;"
          
                         "L2: movl $0,%0;"
                         : "=D"(result): "D"(i)
                         );
    return result;*/
}

int main(int argc, char *argv[])
{
    int i;
    i=40;
    printf("The function value of  i is %d\n", very_fast_function(i) );
    return 0;
}
