This is an example from `valgrind` [documentation](https://valgrind.org/docs/manual/QuickStart.html).

To run this with `valgrind`, type:

```bash
valgrind --leak-check=yes ./valgrind_example
```

You'll get a report like:

```
==718642== Memcheck, a memory error detector
==718642== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==718642== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==718642== Command: ./valgrind_example
==718642== 
==718642== Invalid write of size 4
==718642==    at 0x10916B: f() (valgrind_example.cpp:7)
==718642==    by 0x109180: main (valgrind_example.cpp:12)
==718642==  Address 0x4a82068 is 0 bytes after a block of size 40 alloc'd
==718642==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==718642==    by 0x10915E: f() (valgrind_example.cpp:6)
==718642==    by 0x109180: main (valgrind_example.cpp:12)
==718642== 
==718642== 
==718642== HEAP SUMMARY:
==718642==     in use at exit: 40 bytes in 1 blocks
==718642==   total heap usage: 1 allocs, 0 frees, 40 bytes allocated
==718642== 
==718642== 40 bytes in 1 blocks are definitely lost in loss record 1 of 1
==718642==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==718642==    by 0x10915E: f() (valgrind_example.cpp:6)
==718642==    by 0x109180: main (valgrind_example.cpp:12)
==718642== 
==718642== LEAK SUMMARY:
==718642==    definitely lost: 40 bytes in 1 blocks
==718642==    indirectly lost: 0 bytes in 0 blocks
==718642==      possibly lost: 0 bytes in 0 blocks
==718642==    still reachable: 0 bytes in 0 blocks
==718642==         suppressed: 0 bytes in 0 blocks
==718642== 
==718642== For lists of detected and suppressed errors, rerun with: -s
==718642== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```