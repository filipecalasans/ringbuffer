# Ring Buffer

Ring Buffer Implementation in C.

This project targets to delivery a memory efficient implementation of
Ring BUffer in C. Performance aspect was privileged over the safety, for we do not make safety checks before manipulating the buffer.  For example, we do not verify if the buffer is already full before inserting a new element, nor we verify the buffer is empty before getting a new element. Users should be advised to do so on upper layers.

# Using RingBuffer in C

You ony need to add the sources at **src/** in your project. This implementation is well suited for embedded systems.

# Using Ring Buffer in Cpp

We provide a Ring BUffer Cpp wrapper. This implementation provides some checks before inserting and
getting elements, preventing users of having inconsistent behavior.

# Build Tests

The Makefile in the directory **tests/** builds the plain-c ring-buffer Unit Tests. 

Dependecies:

   * [libcheck](https://libcheck.github.io/check/)

