# Embedded Linux and Kernel Programming

## Hands-on

* Pseudo Driver - Step by Step
  * Register char driver
  * Register file operations
  * Device Create, Class Create
  * Read, Write operations using global buffer
  * Read, Write operations using kfifo
  * ioctl operations, returning length/remaining space, reset operation
  * ioctl operations - filling lentth/remaining space ins tructure
  * synchronization in char driver - using wait queue

* User space code
  * simple read, write
  * multiple read, multiple write
  * Userspace code for IOCTL operations
  * Using two threads for reading, writing
* kthread examples
  * simple two threads
  * Race condition scenarios
  * Mutual exclusion using semaphore, mutex, spinlock
  * Synchronization using semaphores, wait queues
 
* Device Tree based platform driver code -- dummy UART

## Activity
* Making a System call to echo back the given string
* Making a System Call to pass the Arguments
* Making a System call to traverse process list and print PID and PPID of a process  and making a System call to retrieve the attributes of calling process
* Implementing IOCTL to echo back the string, implement two operations such that the string passed by one operation is retrieved by the other operation
* Applying mutual exclusion between first two threads by implementing three kernel threads. First two threads will write N nodes into a kernel list. The third thread waits for the first two threads and traverses the list while mutual exclusion is applied between the first two threads. Exit method cleanup the list nodes
