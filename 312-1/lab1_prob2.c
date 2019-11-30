#include <stdio.h> //For input/output
#include <sys/time.h> //For gettimeofday() function
int main() {
    int int_var; //Tag 1
    struct timeval this_instant;
    
    double time_stamp;
    FILE *my_file_pointer;
    if ( (my_file_pointer = fopen("lab1_prob1_out.txt", "w")) == NULL) {
        printf("Error opening the file, so exiting\n");
        //exit(1);
        
    }
    gettimeofday(&this_instant,0); time_stamp = this_instant.tv_sec;
    //Code segment for file I/O
    fprintf(my_file_pointer, "This program was executed at time : %d secs\n", time_stamp);
    //fprintf(my_file_pointer, "The sizes of different data type for this machine and compiler are -\n");
    //fprintf(my_file_pointer, "int data type is %d bytes or %d bits long\n",sizeof(int_var), sizeof(int_var)*8 );
    //fprintf(my_file_pointer, "double data type is %d bytes or %d bits long\n",sizeof(double), sizeof(double)*8 );
    //Code segment for console I/O, this can be used instead of the file I/O printf("This program was executed at time : %d secs\n", time_stamp);
    fprintf(my_file_pointer,"The sizes of different data type for this machine and compiler are -\n");
    fprintf(my_file_pointer,"unsigned int data type is %d bytes or %d bits long\n",sizeof(unsigned int), sizeof(unsigned int)*8 );
    fprintf(my_file_pointer,"double data type is %d bytes or %d bits long\n",sizeof(double), sizeof(double)*8 );
    fprintf(my_file_pointer,"long data type is %d bytes or %d bits long\n",sizeof(long), sizeof(long)*8 );
    fprintf(my_file_pointer,"long long data type is %d bytes or %d bits long\n",sizeof(long long), sizeof(long long)*8 );
    fprintf(my_file_pointer,"char data type is %d bytes or %d bits long\n",sizeof(char), sizeof(char)*8 );
    fprintf(my_file_pointer,"float data type is %d bytes or %d bits long\n",sizeof(float), sizeof(float)*8 );
    fprintf(my_file_pointer,"struct timeval data type is %d bytes or %d bits long\n",sizeof(this_instant), sizeof(this_instant)*8 );
    fclose(my_file_pointer); //To close the output file, mandatory to actually get an output !
    return 0;
}
