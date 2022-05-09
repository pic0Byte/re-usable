/*
 * ring_buffer.h
 *
 *  Created on: 27 Apr. 2022
 *      Author: Mitch
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_


//typedef the type that the buffer will hold here:
typedef int ring_buf_element;

typedef struct ring_buffer ring_buffer;


/*  Frees memory allocated to ringBuffer
 *
 *  Takes ringBuffer to be freed as an argument
 *
 *  Returns a 0 if memory was freed sucessfully, returns 1 if not sucessful
 *  eg if NULL pointer passed in
 *
 */
int ring_buf_free (ring_buffer *rb);


/*  Initialize ringBuffer
 *
 *  Takes the size of the buffer as an argument
 *
 *  Returns a ringBuf type pointer, returns NULL if memory alloction fails
 */
ring_buffer* ring_buf_init (int size);


/*  Resizes the ringBuffer
 *
 *  Takes new size & ringBuffer pointer as arguments
 *
 *  Returns a 0 on sucess, 1 on failure
 */
int ring_buf_resize (int new_size, ring_buffer *rb);


/*  Return the next unread (oldest) element from the buffer
 *  Takes ringBuf to read from as the argument
 *
 *  Returns the read element. Returns NULL if the buffer is empty
 *  To prevent false data being interpreted from the returned NULL value,
 *  you should always check the buffer is not empty before reading with ring_buf_is_empty()
 */
ring_buf_element ring_buf_read (ring_buffer *rb);


/*  Write an element to the buffer. Overwrites the oldest unread entry if the buffer
 *  is full.
 *  Takes the char to be written, & the ringBuf to write it to as arguments
 *
 *  Returns a 1 if data was overwritten, returns 0 if it wasn't
 *
 */
int ring_buf_write (ring_buf_element input, ring_buffer *rb);

/*  Checks to see if the buffer is empty
*   Slightly more performant than ring_buf_get_population();
*
*   Returns 1 if empty, 0 if it's not
*/
int ring_buf_is_empty (ring_buffer *rb);


/*  Checks whether buffer is full
 *
 *  Returns 1 if full, 0 if not full
 */
int ring_buf_is_full (ring_buffer *rb);


/*  Returns the number of unread items in the buffer.
 *
 *  Takes the ringBuffer pointer as an argument.
 */
int ring_buf_get_population (ring_buffer *rb);

#endif /* INC_RING_BUFFER_H_ */
