# Graphs


Project has following folder tree

.  
├── CMakeLists.txt  
├── CMakeLists.txt.in  
├── README.md  
├── app  
│   └── main.cpp  
├── build  
├── code  
│   ├── Edge.cpp  
│   ├── Edge.h  
│   ├── Node.cpp  
│   ├── Node.h  
│   ├── Graphs.cpp  
│   └── Graphs.h  
└── tests  
    └── test_Graphs.cpp  

CMakeLists.txt      : Ignore this file  
CMakeLists.txt.in   : Ignore this file  
README.md           : Readme file  
app\                : Application folder  
main.cpp            : Application main file for your personal tests. you can use this executable to debug your own classes.  
build\              : Build folder to build the project. your executables are gonna be here eventually.  
code\               : all your code should be in this folder.   
Node.cpp            : Node class source file  
Node.h              : Node class heather file  
Edge.cpp            : Edge class source file  
Edge.h              : Edge class heather file  
Graphs.cpp          : Graphs class source file  
Graphs.h            : Graphs class heather file  
tests\              : Tests folder  
test_Graphs.cpp     : Tests implemented for you / your personal tests  



For your final submission you submitt Graphs.cpp and Graphs.h files. Any other changes in other folders will be ignored in grading process but feel free to change them if you want to test/debug something.

## Where to Start
Open a terminal window in Jupytherhub(recommended) or your personal linux/mac machine (no windows platforms). First pull the this repository by
```console
jovyan@jupyter-yourcuid:~$ git clone https://github.com/Colorado-CompSci-Ugrad/Graphs.git
```
### If you want to use vscode environment
Then open the VScode app through JupyterHub and open Graphs folder from vscode.

Now your environment is set up, change Graphs.cpp and Graphs.h files and eventually press CTRL+SHIFT+B to compile your code.

Open a terminal window in vscode and go into ''build'' folder and run tests by
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
debugger is also set up for you, go to debug tab on the left column and select **Run Tests** in drop-down menu and press the green play button to run the debugger. if you have any implementation in **app/main.cpp** you can also debug that code by first choosing **Run App** in drop-down menu and pressing green play button.

### If you want to use linux terminal for comilation
Make sure you have the dependecies installed (ckeck dependencies in this document)
go into your project folder, then build folder
```console
jovyan@jupyter-yourcuid:~$ cd Graphs
jovyan@jupyter-yourcuid:~$ cd build
```
run cmake to create make file for your project
```console
jovyan@jupyter-yourcuid:~$ cmake ..
```
run make to compile your code
```console
jovyan@jupyter-yourcuid:~$ make
```
once done, you can run tests by 
```console
jovyan@jupyter-yourcuid:~$ ./run_tests
```
app executable is also in this folder, you can run it by
```console
jovyan@jupyter-yourcuid:~$ ./run_app
```
you can debug in terminal using gdb

## Dependencies
you need **gcc** and **cmake** installed to be able to compile this code.

if you are using vscode environment in JupyterHub, you just need to make sure you have C/C++ extension installed.

## About This homework
Check Graphs.h file comments for detailed information for each function.

## Go in order

I recommend that you implement the functions in the same order that
they appear in the `points.json` file. This is the same order reported
by `python grade.py graph_test`.

## Pseudocode

This is the pseudocode to get you going. You'll need to augment it
(e.g. by setting ancestors, incrementing the clock, classifying edges,
and so on).

```
bfs(start):
  clear graph
  mark start gray
  Q = empty queue
  add start to Q
  while Q has stuff in it:
    v = popped element from Q
    mark v black
    visit v
    for each unmarked neighbor w
        mark w gray
        add w to Q
```

```
# clear graph before initial call
dfs(node): 
  mark node gray
  visit node
  E = edges related to node
  for all edges e in E:
    a = end of e that isn't node
    if a is white:
      dfs(a)
  mark node black
```

## Two versions of bfs

There are two signatures for bfs. I recommend that you implement the
two-arg version fully, and then have the one-arg version simply call
the two-arg version with a target that doesn't exist in the graph.

Remember: laziness is one of the three virtues of a great programmer.

## Use a queue, maybe

The header file includes vectors to store nodes and edges during a
search. You can use these if you like, or ignore them and use
something else instead.

In my implementation I did an interative BFS using a queue (so,
`#include <queue>` atop implementation file), and a recursive DFS
using the `getAdjacentEdges` set.

## The auto keyword

The `auto` keyword can make life easier when iterating through a
collection. It leverages the compiler to 'figure out' what type would be
assigned for you (this only works for assignment, you cannot use `auto` for
example in function parameters). Also note that it is NOT like Python's dynamic
types, the type must still be known at compile time.

You can use `auto` to cleanly iterate over C++ collections:
```cpp
for (auto n : nodes) {
  // N right here will be a single node, one at a time.
}
```

A more correct way to handle iteration (which forces const and that the value is
iterated by reference resulting in zero-copy):
```cpp
for (const auto& n : nodes) {
  // N right here will be a single node, one at a time.
}
```

## Use `make_dot`

Check out the `tick` and `make_dot` functions that is provided for you
in the implementation file. If you call `tick` after each interesting
event (start, end, and every time you increment the clock) you can use
this to watch the progress of your dfs or bfs.

## Make helper functions

You'll likely want to create and use helper functions. The details are
up to you. For example, I made a `otherEnd` function that returned the
start/end of an edge that wasn't the node I'm looking at currently.

Helpers aren't strictly necessary but they will make your life easier
and reduce the volume of code where bugs can lurk.