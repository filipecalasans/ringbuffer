# Ring Buffer

Ring Buffer Implementation in C - Memory and Performance Efficient targeting applications with resource constrained requirements.

This project targets to delivery a memory efficient implementation of
Ring BUffer in C. Performance aspect was privileged over the safety, for we do not make safety checks before manipulating the buffer.  For example, we do not verify if the buffer is already full before inserting a new element, nor we verify the buffer is empty before getting a new element. Users should be advised to do so on upper layers.
