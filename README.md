# LDD
Linux Device Driver


Introduction
Loadable Kernel Module using C

- kernel module are considered as object files which contains code which Extends the feature of running kernel.
- kernel module are generally used to Support new hardware , to support new file system to add new system call.
- Advantages of kernel module is that It gets loaded memory of kernel whenever required and it gets removed from memory when its used gets completed.
- To load and Unload kernel modules their is no need to reboot our kernel.
- The Concept of kernel module is used in almost every Linux Distro. Including MAC OS.
- To write the kernel module we have to use Basic C programming concept and some commands.

- Types of kernel Module-  1. Device Driver
                                               2. File system Driver
                                               3. Network Driver
                                               4. TTY (teli Type Terminals)

Advantages of kernel Module-

1. Easy to Insert and Remove from memory.
2. We can Insert it without rebooting the kernel.
3 We can easily Remove it from memory when its used gets completed.

Disadvantages of kernel Module-

1. Due to loading and unloading of kernel module their is fragmentation in kernel memory.

