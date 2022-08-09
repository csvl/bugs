# Buggy programs 

These bugs are part of a collection of differents bugs meant to be analyzed for academic research.
For each program, the directory contains
> The source code of the program (example.c)
> 
> The repaired source code (example_patch.c)
> 
> The requirements needed by SMC (*.toml)
>
> A Makefile

## Binary Search
### Description 
This bug is an out-of-bounds access in a binary search. In this bug, the array ``arr`` is received as a parameter. Because the variable ``size`` has been initialized at ``size`` instead of ``size-1``, this code will go out of bounds under certain circumstances.
This bug is hard to track because in terms of behavior, most of the time this out-of-bounds access will have no visible consequence. In some rare case, if the researched value ``elem`` is present at the memory address located just after the array, then the algoritm will return this value. Because this event is higly unlikely, it might be very hard to detect it by just observing the output of the algorithm.
 
### Repair
The tool fixes the faulty statement ``int r = size`` located at line 10 by applying the pattern ``m-1`` from line 17 thus replacing ``size`` by ``size-1`` (See search_patch16.c). Initializing ``r`` at the value ``size-1``, will fix the out-ouf-bounds access.
The size of the population needed to repair this program was 112 with a random strategy and 50 with the Q-function.

## Local Binary Search
### Description 
This example coming from the CProver manual http://www.cprover.org/cprover-manual/cbmc/tutorial/ is also an out-of-bound access in a binary search, but this time the array ``a`` is local and not received as a parameter. The difference with the previous example resides in the fact that in this case it is possible to determine the size of the local array ``a``, when it wasn't possible in the previous case.
### Repair
The tool applies a patch that modifies lines 14, 16 and 18 by adding a bounds-check. These lines are the lines where the variables might get out-ouf-bounds and are thus monitored by the BLTL property. The bounds-check is added as a if-statement, where the condition is created based on the BLTL property. (See binsearch_patch1.c)
The size of the population needed to repair this program was 13 with a random strategy and 10 with the Q-function.

## Static out-of-bounds
### Description
This simple example is based on the example from http://cppcheck.sourceforge.net/. It consists of a simple out-of-bounds access that will happen every time. Because the ``oob`` function is called with the parameter ``x`` that contains the value 10, the code will try to access the buffer ``buf`` at the index 10, while ``buf`` can only be accessed by using an index between 0 and 9.
Because this bug is "hardcoded" and happens every time and is easy to detect.
### Repair
The tool fixes the statement at line 6 by replacing the size of the buffer ``buf`` by ``1000`` (See oob_patch5.c). By increasing the size of the buffer, the "hardcoded" access to the index 10 will never be out-of-bounds, thus fixing the bug.
The size of the population needed to repair this program was 4 with a random strategy and 2 with the Q-function.
## Random out-of-bounds
### Description
This bug is a variation of the previous one and also based on the example from http://cppcheck.sourceforge.net/.
While the previous one was "static" in the sense that it was hardcoded and thus happenned every time, this version happens randomly.
Instead of being called with the value 10 every time, the ``oob`` function in this case is called with a random parameter ``oob(rand()%15);``. While this change appears trivial, is actually makes the bug harder to detect by several tools due to the "randomness".
### Repair
The tool fixes the statement at line 6 by replacing the size of the buffer ``buf`` by ``1000``. (See oob_dynamic_patch5.c)
By increasing the size of the buffer, the access to a random index located between 0 and 14 will never be out-of-bounds, thus fixing the bug.
The size of the population needed to repair this program was 4 with a random strategy and 2 with the Q-function.
## Division by zero
### Description 
This bug consists of a simple ``divide`` function that takes two parameters ``a`` and ``b`` and tries to return ``a / b``.
While this code generally works, it doesn't check the value of ``b`` to protect against divisions by zero.
### Repair
For this patch, the tool will try to avoid a division by 0 by replacing the statement ``int divisor = b;`` from line 3 by the statement ``int divisor = dividend;`` (See divide_patch2.c). 
In this case, ``dividend`` is picked from the vocabulary of the original program. While this patch fixes the bug in the sense that it will satisfie the BLTL property ``line > 3 => divisor!=0`` used to prevent a division by 0, it does so by applying a fix that changes the function's semantic. This shows that when using this tool, either the BLTL properties used must be carefully picked to also preserve the function's semantic or the patch should be reviewed to ensure that the semantic of the function is preserved.
The size of the population needed to repair this program was 1 with a random strategy and 3 with the Q-function.
## Buffer overflow
### Description 
In this example, the variable ``x`` is used to access a secret line of code located at line 38. In theory, because the variable ``x`` is initialized to the value 42 and not modified after there should be no way to execute line 38. However, the buffer ``buf`` can be overflowed to overwrite the value of ``x``. In the same fashion as the random out-of-bounds, the overflow happens on a random basis depending on the result of line 34. When ``r`` is equal to 13, the ``strncpy`` call at line 36 will overflow the  variable ``x`` with the value ``"d"`` and thus trigger the line 38.
### Repair
To repair this buffer overflow, the tool will generate a patch to prevent the ``strncpy`` call from line 36 from overflowing the ``x`` variable. To do so, it will replace the ``r`` argument passed to the ``strncpy`` call with ``argc`` (See buffer_overflow_patch15.c). ``argc`` is picked from the vocabulary of the original program. With this fix the program will reach the desired behavior of not reaching line 38 because we don't specify any arguments in our tests (this behavior can be tested and enforced by adding a BLTL property to monitor the value of ``argc``).
The size of the population needed to repair this program was 25 with a random strategy and 3 with the Q-function.
## Pointer-to-pointer
### Description 
This algorithm leverages the complexity of memory abstraction by using a pointer to pointer to store a dictionnary. Coupled with that, a ``NULL`` value is randomly inserted in one of the array's entry. Then, a random entry is choosed in the array to be displayed. In some rare case this program might try to ``printf`` the ``NULL`` value.
This examples covers the complexity of the representation of a pointer to pointer in memory and the occurence of rare events that are difficult to detect.
### Repair
To fix this bug, the tool will modifie the statement ``int insertNull = rand() % 10;`` located at line 80 by changing it to ``int insertNull = rand() % 1;`` (See double_pointer_patch1.c). The number ``1`` is picked from the vocabulary of the original program. Because this statement is responsible for selecting wether or not a ``NULL`` value is inserted into the dictionnary, and because ``rand() % 1;`` is always going to be equal to 0, a ``NULL`` value will never be inserted into the dictionnary, thus fixing the bug.
The size of the population needed to repair this program was 2 with a random strategy and 1 with the Q-function.

## Read-only memory
### Description 
In this simple example, the program is trying to write into some read-only memory (variable ``*s``), creating a segmentation fault when executed. This example is hard to detect without executing the code because the fact that a certain zone of memory is read-only depends on the architecture.  
### Repair
Our approach wasn't able to repair this program. The failure is due to there being no reasonable way for the patch generation algorithm to create a suitable repair.
## Integer overflow
### Description 
This bug consists of a simple ``add`` function that adds two values. This simple addition might cause an integer overflow. This example is also hard to detect because the max value of an integer depends on the architecture.
### Repair
To prevent the integer overflow from occuring, the tool will protect the statement responsible for the overflow at line 6 ``result = a+b;`` with a if-statement checking for a potential overflow at line 5 (See add_patch1.c). With this fix, the code from line 6 will only be executed when it is "safe" to do so.
This if-statement ``if((!(a > 0 && b > INT_MAX - a)))`` used to protect the addition is created based on the BLTL property.
The size of the population needed to repair this program was 10 with a random strategy and 3 with the Q-function.