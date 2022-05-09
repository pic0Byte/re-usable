#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <time.h>
#include "ring_buffer.h"
#include "ring_buffer_test.h"

#define MAX_BUFFER_SIZE 40000
#define SRAND_SEED time(NULL)


void ring_buf_test_free();
void ring_buf_test_init();
void ring_buf_test_read_write();
void ring_buf_test_is_empty();
void ring_buf_test_is_full();
void ring_buf_test_get_population ();



void ring_buf_test_all(){

   srand(SRAND_SEED);

   ring_buf_test_init();
   ring_buf_test_read_write();
   ring_buf_test_is_empty();
   ring_buf_test_is_full();
   ring_buf_test_get_population();

   printf("All  tests passed......\n\n");

}


void ring_buf_test_init(){

   int random_size = (rand() % MAX_BUFFER_SIZE);
   ring_buffer *rb = ring_buf_init(random_size);
   assert (rb);
   ring_buf_write(10, rb);
   assert (ring_buf_read(rb) == 10);
   ring_buf_free(rb);
   printf("ring_buf_test_init passed...\n\n");

}


void ring_buf_test_read_write(){

   int random_size = (rand() % MAX_BUFFER_SIZE);
   ring_buffer *rb = ring_buf_init(random_size);
   printf("ring_buf_test_read_write with buffer size of %d...\n\n", random_size);

   for (int i = 0; i < 255; i++){

      ring_buf_write(i, rb);
      assert (ring_buf_read(rb) == i);

   }

   ring_buf_free(rb);


   printf("ring_buf_test_read_write passed...\n\n");

}


void ring_buf_test_is_empty(){

   int random_size = (rand() % MAX_BUFFER_SIZE);
   ring_buffer *rb = ring_buf_init(random_size);
   printf("ring_buf_test_is_empty with buffer size of %d...\n\n", random_size);

   assert (ring_buf_is_empty(rb));

   ring_buf_free(rb);

}

void ring_buf_test_is_full(){

   int random_size = (rand() % MAX_BUFFER_SIZE);
   ring_buffer *rb = ring_buf_init(random_size);
   printf("ring_buf_test_is_full with buffer size of %d...\n\n", random_size);

   for (int i = 0; i < random_size; i++){
      assert (!(ring_buf_is_full(rb)));
      ring_buf_write (i, rb);
   }

   assert (ring_buf_is_full);

   ring_buf_free(rb);

   printf("ring_buf_test_is_full passed...\n\n");

}


void ring_buf_test_get_population(){

   int random_size = (rand() % MAX_BUFFER_SIZE);
   ring_buffer *rb = ring_buf_init(random_size);
   printf("ring_buf_test_get_population with buffer size of %d...\n\n", random_size);

   //check population is correct when empty
   assert (ring_buf_get_population(rb) == 0);

   ring_buf_write(75, rb);
   assert (ring_buf_get_population(rb) == 1);
   ring_buf_read(rb);
   assert (ring_buf_get_population(rb) == 0);
   ring_buf_read (rb);
   //check population is correct after reading from an empty buffer
   assert (ring_buf_get_population(rb) == 0);
   

   for (int i = 0; i < (random_size + 10); i++){
      ring_buf_write(i, rb);
   }   // check if the size is returned correctly when buffer is overwritten
   assert (ring_buf_get_population(rb) == random_size);

   ring_buf_read(rb);

   assert (ring_buf_get_population(rb) == (random_size - 1));

   for (int i = 0; i < (random_size - 2); i++) {
      ring_buf_read(rb);
   }
   assert (ring_buf_get_population(rb) == 1);

   ring_buf_free(rb);

   printf("ring_buf_test_get_population passed...\n\n");


}
