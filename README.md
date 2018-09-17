# INF214
Repo for the assignments in INF214

## Getting stuff to work:
It was a real hassle getting everything up and running. I'm using Archlinux so setting upp an IDE i could not
really be bothered with VisualStudio as it is HUGE, slow and overpowered. But I did not wish to use Vim and gcc either.

I eventually went with CLion from my favorite IDE-makers JetBrains as we do get a free student license. This comes
pre-installed with CMake, which was a hassle of its own to get compiling. But after just two hours i finally had myself
a "Hello World!" program.

Now getting C++ to work was not an easy task. Getting everything given for this assigneent to run? please don't even
get me started. I have never used this language ever, and apparently this offers a LOT of freedom for the developer
but with NO SUPPORT what so ever. Apparently this is top down compiled, so you cannot have the main method at the start.

### First run:
You can apparently freely mess arround with pointers, deconstructors and god knows what. I have NO clue what all this
code does, and googeling gives me a headace. Anyways continuing on. After much back and fourth, I finally made it:
```
/home/raknoel/CLionProjects/INF214/src/cmake-build-debug/INF214
3412

Process finished with exit code 0
``` 

### Unsafe concurrency test:
And so apparently CMake does not really like concurrency. After a bit of a hassle I was able to upgrade to C++ v.17 and
add a small line to the 'CMakeLists.txt' file.
```set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")```

And then we actually get a result from the run, but only properly sometimes:
```
/home/raknoel/CLionProjects/INF214/src/cmake-build-debug/INF214
   Elements enqueued: 2000
   Queue size: 2000
   Elements in queue: 2000
   ---------------
   Elements enqueued: 1000
   Elements dequeued: 1000
   Successful dequeue count: 1000
   Queue size: 0
   Elements in queue: 0
   
   Process finished with exit code 0
```

Then sometimes it crashes:
```
/home/raknoel/CLionProjects/INF214/src/cmake-build-debug/INF214
Elements enqueued: 2000
Queue size: 1997
Elements in queue: 1993
---------------

Process finished with exit code 139 (interrupted by signal 11: SIGSEGV)
```
Which is obvius that it could as we did not make our queue thread safe, and still used it concurrent.

## Tasks:
### Task 0:
Ii'l try my very best

### Task 1:
