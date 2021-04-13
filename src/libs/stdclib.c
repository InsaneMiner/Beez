#include <stdint.h>

#define RAND_MAX 32767
unsigned long next = 1;

extern uint32_t _timestamp_edx();
extern uint32_t _timestamp_eax();


int rand(){
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % RAND_MAX+1; 
}

void srand(unsigned int seed){
    next = seed;
}


void randseed(){
    srand(_timestamp_eax());
}



uint32_t digit_count(int num)
{
  uint32_t count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}