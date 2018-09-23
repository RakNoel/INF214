# INF214
Repo for the assignments in INF214

## Getting stuff to work:
It was a real hassle getting everything up and running. I'm using Arch-linux so setting upp an IDE i could not
really be bothered with VisualStudio as it is HUGE, slow and overpowered. But I did not wish to use Vim and gcc either.

I eventually went with CLion from my favorite IDE-makers JetBrains as we do get a free student license. This comes
pre-installed with CMake, which was a hassle of its own to get compiling. But after just two hours i finally had myself
a "Hello World!" program.

Now getting C++ to work was not an easy task. Getting everything given for this assigneent to run? please don't even
get me started. I have never used this language ever, and apparently this offers a LOT of freedom for the developer
but with NO SUPPORT what so ever. Apparently this is top down compiled, so you cannot have the main method at the start.

### First run:
You can apparently freely mess arround with pointers, deconstructions and god knows what. I have NO clue what all this
code does, and google-ing gives me a headace. Anyways continuing on. After much back and fourth, I finally made it:
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
Which is obvious that it could as we did not make our queue thread safe, and still used it concurrent.

## Tasks:
### Task 0:
I did try my very best, and I'm able to imagine it, but I cannot convince myself without the needed evidence.

### Task 1:
See "Oblig_1_ole006.tex"

### Task 2:
I did encounter a lot of problems with this, but in the end it turned out to really be solvable

### Task 3:
To limit the code and changes needed I chose to keep the variables the same, and keep them atomic? with the
A<> notation. Since a semaphore is not directly implemented in C++, I chose to use the mutex-lock. Which could
probably just be replaced by using the "enter/exit _critical" since that's what it looks like A-Lang does.
