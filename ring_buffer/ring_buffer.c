#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

#define SIZE (rb->size)
#define LAST_ELEMENT (rb->size - 1)


struct ring_buffer{
  int head;
  int tail;
  int size;
  ring_buf_element *array;
};


int ring_buf_free (ring_buffer *rb) {

   if (rb != NULL){

      if (rb->array != NULL){
         free (rb->array);
      }

      free (rb);

      return 0;

   }

   return 1;

}


ring_buffer* ring_buf_init (int size) {

   ring_buffer* rb = malloc(sizeof(struct ring_buffer));

   if (rb == NULL){
      return NULL;
   }

   rb->head = 0;
   rb->tail = 0;
   rb->size = size + 1;  // +1 to accomodate for head pointer

   rb->array = malloc(rb->size * sizeof(ring_buf_element));

   if (rb->array == NULL){
      free (rb);
      return NULL;
   }

//   initialize to zeroes - not needed??
//   for (int i = 0; i < rb->size; i++){
//      rb->array[i] = 0;
//   }


   return rb;

}


int ring_buf_resize (int new_size, ring_buffer *rb) {

   if (rb != NULL){

      ring_buf_element *tmp;
      tmp = realloc(rb->array, (new_size + 1) * sizeof(ring_buf_element));

      if (tmp != NULL){

         rb->array = tmp;
         rb->size = (new_size + 1);
         return 0;
      }
   }

   return 1;


}


ring_buf_element ring_buf_read (ring_buffer *rb) {

   ring_buf_element read;

   if (rb->tail == rb->head){
      return 0;
   }

   read = rb->array[rb->tail];
   rb->tail = (rb->tail + 1) % SIZE;

   return read;

}


int ring_buf_write (ring_buf_element input, ring_buffer *rb){

   int dataOverwitten = 0;
   rb->array[rb->head] = input;
   rb->head = (rb->head + 1) % SIZE;

   if (rb->head == rb->tail){

      rb->tail = (rb->tail + 1) % SIZE;
      dataOverwitten =  1;

   }

   return dataOverwitten;
}


int ring_buf_is_empty (ring_buffer *rb){
   if (rb->tail == rb->head){
      return 1;
   } else return 0;
   
}


int ring_buf_is_full(ring_buffer *rb){

   if (rb->head > rb->tail){
      if (rb->head == LAST_ELEMENT && rb->tail == 0){
         return 1;
      }
   } else if ((rb->tail - 1) == rb->head){
      return 1;
   }

   return 0;

}


int ring_buf_get_population (ring_buffer *rb) {

   int population = 0;

   /*if (ringBufIsFull(rb)){
      population = SIZE;
      return population;
   }*/

   int count = 0;
   int position = rb->tail;

   while (position != rb->head){
      count++;
      position = ((position + 1) % SIZE);
      population = (count);
      //printf("Population %d\n", population;
   }

   return population;

}
