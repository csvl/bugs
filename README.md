# Buggy programs 

These bugs are part of a collection of differents bugs meant to be analyzed for academic research.

## Binary Search

> This bug is an out-of-bounds access in a binary search. In this bug, the array ``arr`` is received as a parameter. Because the variable ``size`` has been initialized at ``size`` instead of ``size-1``, this code will go out of bounds under certain circumstances.
This bug is hard to track because in terms of behavior, most of the time this out-of-bound access will have no visible consequence. In some rare case, if the researched value ``elem`` is present at the memory address located just after the array, then the algoritm will return this value. Because this event is higly unlikely, it might be very hard to detect it by just observing the output of the algorithm.
 
## Local Binary Search

> This example coming from the CProver manual http://www.cprover.org/cprover-manual/cbmc/tutorial/ is also an out-of-bound access in a binary search, but this time the array ``a`` is local and not received as a parameter. The difference with the previous example resides in the fact that in this case it is possible to determine the size of the local array ``a``, when it wasn't possible in the previous case.

## Static out-of-bounds

> This simple example is based on the example from http://cppcheck.sourceforge.net/. It consists of a simple out-of-bounds access that will happen every time. Because the ``oob`` function is called with the parameter ``x`` that contains the value 10, the code will try to access the buffer ``buf`` at the index 10, while ``buf`` can only be accessed by using an index between 0 and 9.
Because this bug is "hardcoded" and happens every time and is easy to detect.


## Random out-of-bounds

> This bug is a variation of the previous one and also based on the example from http://cppcheck.sourceforge.net/.
While the previous one was "static" in the sense that it was hardcoded and thus happenned every time, this version happens randomly.
Instead of being called with the value 10 every time, the ``oob`` function in this case is called with a random parameter ``oob(rand()%15);``. While this change appears trivial, is actually makes the bug harder to detect by several tools due to the "randomness".

## Division by zero

> This bug consists of a simple ``divide`` function that takes two parameters ``a`` and ``b`` and tries to return ``a / b``.
While this code generally works, it doesn't check the value of ``b`` to protect against divisions by zero.

## Buffer overflow

> In this example, the variable ``x`` is used to access a secret line of code located at line 38. In theory, because the variable ``x`` is initialized to the value 42 and not modified after there should be no way to execute line 38. However, the buffer ``buf`` can be overflowed to overwrite the value of ``x``. In the same fashion as the random out-of-bounds, the overflow happens on a random basis depending on the result of line 34. When ``r`` is equal to 13, the ``strncpy`` call at line 36 will overflow the  variable ``x`` with the value ``"d"`` and thus trigger the line 38.

## Pointer-to-pointer

> This algorithm leverages the complexity of memory abstraction by using a pointer to pointer to store a dictionnary. Coupled with that, a ``NULL`` value is randomly inserted in one of the array's entry. Then, a random entry is choosed in the array to be displayed. In some rare case this program might try to ``printf`` the ``NULL`` value.
This examples covers the complexity of the representation of a pointer to pointer in memory and the occurence of rare events that are difficult to detect.


## Read-only memory

> In this simple example, the program is trying to write into some read-only memory, creating a segmentation fault when executed. This example is hard to detect without executing the code because the fact that a certain zone of memory is read-only depends on the architecture.  

## Integer overflow

> This bug consists of a simple ``add`` function that adds two values. This simple addition might cause an integer overflow. This example is also hard to detect because the max value of an integer depends on the architecture.
