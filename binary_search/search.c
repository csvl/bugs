#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>

int search(int arr[], int size, int elem)
{
    int l = 0;
    int r = size; //should be size-1
    int m = 0;
    
    while (r >= l) {
        m = (l+r) / 2;

        if (arr[m] == elem) {
            return m;
        } else if (arr[m] > elem) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    return -1;
}

/* "Classical Unit test 01"
 * With a unit test this will always looks like a success, because the program
 * will always find 2. Because 2 is a the beginning of the table, the algorithm
 * will not go out of bounds. So in this example, nothing is going to go wrong. 
 */
void classical_test_01() {
    int tab[8] = {1,2,3,4,5,6,7,8};

    int i = search(tab, sizeof(tab)/sizeof(tab[0]), 2);
    assert(i == 1);
}

/* "Classical Unit test 02"
 * With a unit test this will always looks like a success, because the program
 * will always return -1 because 100 is not in the table. However, due to the 
 * bug and the fact that the value we're looking for is bigger than the biggest
 * value in the table, the algorithm will go out of bounds (up to size, 8 in
 * this case). Because the value we're looking for is *most probably* not in
 * the memoery directly following the tab, the unit test will not return -1. 
 * The bug will then go unnoticed from the unit test.
 */
void classical_test_02() {
    int tab[8] = {1,2,3,4,5,6,7,8};

    int i = search(tab, sizeof(tab)/sizeof(tab[0]), 100);
    assert(i == -1);
}

/* "Faulty Unit test"
 * This test is provided to show the incorrectness of the algorithm.
 * In this program, we assume that two arrays follow each other in memory
 * (this depends on the compiler) such as tab[8] is tab2[0].
 * In that very specific case, if tab2[0] contains the value we are looking
 * for (11 in this example), the algorithm will return 8 instead of -1.
 * It is however very unlikely that a unit test covers such a specific case.
 */
void faulty_test() {
    /* Two arrays, following each other in memory */
    int tab[8] = {1,2,3,4,5,6,7,8};  
    int tab2[8] = {11,12,13,14,15,16,17,18};
    /* Printing the address of the beginning of each array */
    printf("%p\n", &tab[0]);
    printf("%p\n", &tab2[0]);

    /* Search for 11 which is located in tab2[0] (and thus tab[8]) */
    int i = search(tab, sizeof(tab)/sizeof(tab[0]), 11); // i = 8 instead of -1
    /* Here i = 8 instead of -1 */
    printf("%d\n", i);
    printf("%d\n", tab[8]);

    assert(i == -1);
}

/* "Random test"
 * This test is design to generate a mixed output.
 * In this test we will look for values between 1 and 10. Values 1-8 should
 * not result in the algorithm going out of bounds while values 9 and 10 should
 * push it to look in tab[8]. With this example ~80% of the traces should be
 * GOOD and ~20% of the traces should be BAD.
 */ 
void random_test() {
    int tab[8] = {1,2,3,4,5,6,7,8};

    /* Initialize rand */
    srand(time(NULL));
   
    /* We're looking for a value between 1 and 10 */
    int v = (rand() % 10)+1;

    /* searching for the value in the tab */
    int i = search(tab, sizeof(tab)/sizeof(tab[0]), v);

    /* printing the value found by the algorithm */
    printf("%d\n", i);
}

int main() {
    //classical_test_01();
    //classical_test_02();
    //faulty_test();
    random_test();
    printf("All tests succeeded !\n");
    return 0;
}
