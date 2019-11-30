#include "BuddyAllocator.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;

BuddyAllocator::BuddyAllocator (int _basic_block_size, int _total_memory_length){
    if (log2(_basic_block_size) != ceil(log2(_basic_block_size))) {
        cerr << "ERROR:: Size of basic block is non-power of 2" << endl;
        exit (-2);
    }
    if (log2(_total_memory_length) != ceil(log2(_total_memory_length))) {
        cerr << "ERROR:: Size of total memory is non-power of 2" << endl;
        exit (-3);
    }
    if (_basic_block_size < 0 || _total_memory_length < 0) {
        cerr << "ERROR: Negative bbs or tms" << endl;
        exit(-4);
    }
    basic_block_size = _basic_block_size;
    total_memory_size = _total_memory_length;
    for (int i = log2(_basic_block_size); i <= log2(_total_memory_length); i++) {
        LinkedList newNode;
        newNode.head = NULL;
        FreeList.push_back(newNode);
    }
    char *start = (char*)malloc(_total_memory_length);
    FreeList[log2(_total_memory_length)-log2(_basic_block_size)].head = (BlockHeader*)start;
    FreeList[log2(_total_memory_length)-log2(_basic_block_size)].head->block_size = _total_memory_length;
    FreeList[log2(_total_memory_length)-log2(_basic_block_size)].head->next = NULL;
    FreeList[log2(_total_memory_length)-log2(_basic_block_size)].head->free = 1;
    total = FreeList[log2(_total_memory_length)-log2(_basic_block_size)].head;
}

BuddyAllocator::~BuddyAllocator (){
    delete FreeList[FreeList.size()-1].head;
}

char* BuddyAllocator::alloc(int _length) {
  /* This preliminary implementation simply hands the call over the 
     the C standard library! 
     Of course this needs to be replaced by your implementation.
  */
    char *new_re = NULL;
    _length += sizeof(BlockHeader);
    if (_length > total_memory_size) {
        cerr << "One of the _length is larger than total memory. Out of memory, unable to allocate" << endl;
        exit(-7);
    }
    int size = 0;
    if (_length <= basic_block_size) {
        size = basic_block_size;
    }else {
        size = pow(2,ceil(log2(_length)));
    }
        int i = log2(size)-log2(basic_block_size);
        if (FreeList[i].head == NULL) {
            while (FreeList[i].head == NULL) {
                i++;
                if (i == FreeList.size()-1 && FreeList[FreeList.size()-1].head == NULL) {
                    cerr << "Out of memory, unable to allocate" << endl;
                    exit(-6);
                }
                if (i > FreeList.size()-1) {
                    cerr << "One of the _length is larger than the biggest block which can be allocated. Out of memory, unable to allocate" << endl;
                    exit(-7);
                }
            }
            while (FreeList[i].head->block_size != size) {
                BlockHeader *old_add = FreeList[i].head;
                BlockHeader *new_add = split(FreeList[i].head);
                new_add->free = 1;
                old_add->free = 1;
                old_add->block_size = (FreeList[i].head->block_size)/2;
                new_add->block_size = old_add->block_size;
                FreeList[i].remove(FreeList[i].head);
                i--;
                FreeList[i].insert(new_add);
                FreeList[i].insert(old_add);
            }
        }
        if (FreeList[i].head->block_size == size) {
            FreeList[i].head->free = 0;
            new_re = (char*)FreeList[i].head + sizeof(BlockHeader);
            FreeList[i].remove(FreeList[i].head);
        }
    return new_re;
}

int BuddyAllocator::free(char* _a) {
  /* Same here! */
    _a -= sizeof(BlockHeader);
  BlockHeader *front_block = (BlockHeader*)_a;
    front_block->free = 1;
    while (log2(front_block->block_size)-log2(basic_block_size) < FreeList.size()) {
        BlockHeader *buddy = getbuddy(front_block);
        if (FreeList[log2(front_block->block_size)-log2(basic_block_size)].head == NULL || buddy->free==0) {
            FreeList[log2(front_block->block_size)-log2(basic_block_size)].insert(front_block);
            return 0;
        }
        FreeList[log2(buddy->block_size)-log2(basic_block_size)].remove(buddy);
        front_block = merge(front_block, buddy);
        front_block->free = 1;
        buddy->free = 1;
    }
    FreeList[log2(front_block->block_size)-log2(basic_block_size)].insert(front_block);
  //delete _a;
  return 0;
}

void BuddyAllocator::printlist (){
  cout << "Printing the Freelist in the format \"[index] (block size) : # of blocks\"" << endl;
  for (int i=0; i<FreeList.size(); i++){
      //
    cout << "[" << i <<"] (" << ((1<<i) * basic_block_size) << ") : ";  // block size at index should always be 2^i * bbs
    int count = 0;
    BlockHeader* b = FreeList [i].head;
    // go through the list from head to tail and count
    while (b){
      count ++;
      // block size at index should always be 2^i * bbs
      // checking to make sure that the block is not out of place
      if (b->block_size != (1<<i) * basic_block_size){
          cout << "  " << b->block_size << endl;
        cerr << "ERROR:: Block is in a wrong list" << endl;
        exit (-1);
      }
      b = b->next;
    }
    cout << count << endl;  
  }
}

