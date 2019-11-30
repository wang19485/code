#include "Ackerman.h"
#include "BuddyAllocator.h"
#include <stdlib.h>
#include <ostream>
#include <unistd.h>
using namespace std;

void easytest(BuddyAllocator* ba){
  // be creative here
  // know what to expect after every allocation/deallocation cycle

  // here are a few examples
  ba->printlist();
  // allocating a byte
  char * mem = ba->alloc (1);
  // now print again, how should the list look now
  ba->printlist ();
  ba->free (mem); // give back the memory you just allocated
  ba->printlist(); // shouldn't the list now look like as in the beginning

}

int main(int argc, char ** argv) {
  // create default bbs and tms
  int basic_block_size = 128, memory_length = 512 * 1024; // 512kb is default.
    // call getopt to check the command line arguments
    // Error checking like non-pow of 2 is loacated at BuddyAllocator constructor. The getopt() doesn't handle this kind of errors.
    int c;
    while ((c = getopt(argc, argv, "b:s:")) != -1) {
        switch (c) {
            case 'b':
                basic_block_size = atoi(optarg);
                break;
            case 's':
                memory_length = atoi(optarg);
                break;
            default:
                cout <<"ERROR: Unacceptable command line argument, see report to get the correct format" << endl;
                exit(-5);
                break;
        }
    }
  // create memory manager
  BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);

  // the following won't print anything until you start using FreeList and replace the "new" with your own implementation
  easytest (allocator);

  
  // stress-test the memory manager, do this only after you are done with small test cases
  Ackerman* am = new Ackerman ();
  am->test(allocator); // this is the full-fledged test. 
  
  // destroy memory manager
  delete allocator;
    
}
