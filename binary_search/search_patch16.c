#include <stdio.h>
#include <alloca.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
int gt;
int search(int arr[], int size, int elem)
{
    int l = 0;
    int r = size-1;
    int m;
    while (r>= l) {
        m = (r + l) / 2;
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
    int tab[9] = {1,2,3,4,5,6,7,8,9};
	//int* tab = (int*) alloca(8*sizeof(int));
	//for(int i= 1; i < 9; i++){
	//	tab[i-1] = i;
	//}

    /* Initialize rand */
    srand(time(NULL));
   
    /* We're looking for a value between 1 and 10 */
    //int v = (rand() % 10)+1;
	gt = (rand() % 18);
	int v = (rand() % 10)+10;
	if (gt<9) v = tab[gt];
	else gt = -1;
	//v = 11;

    /* searching for the value in the tab */
    int i = search(tab, sizeof(tab)/sizeof(tab[0]), v);
	//int i = search(tab, 8, v);

    /* printing the value found by the algorithm */
    printf("%d\t%d\n", i,v);
}

/**
**/
void test_(){
	char* FNAME = "/media/kdam/Data/UCL/code/Project2/Project2/samples/search/search_test.in";
	int n;
	int v;
	int arr[8];
	//int * arr;
	FILE *fptr;
	fptr = fopen(FNAME,"r");
	fscanf(fptr,"%d", &n );
	printf("n=%d\n", n);
	//arr = (int*)malloc(sizeof(int)*n);
	for(int i = 0; i < n; i++){
		fscanf(fptr,"%d", &arr[i] );
		printf("%d ", arr[i]);
	}
	fscanf(fptr,"%d", &v );
	int j,e;
	if (v >= 0){
		e = arr[v];
		gt = v;
	}else{
		if(v==-1){
		srand(time(NULL));
		e =(rand() % 10)+100;
		gt = -1;
		}else{
		srand(time(NULL));
		e =-(rand() % 10+100);
		gt = -1;
		}
	}
	printf("\n%d\t%d\n",v,e);
	
	fclose(fptr);

	fptr = fopen(FNAME,"w");
	fprintf(fptr,"%d\n", n );
	for(int i = 0; i < n; i++){
		fprintf(fptr,"%d ", arr[i]);
	}
	if (v < n-1 && v >=0){
		v+=1;
	}else{
		if (v>=n-1)	v=-1;
		else if (v == -1) v+=-1;
				else v= 0;
	}
	printf("v=%d\n",v);
	fprintf(fptr,"\n%d",v);
	fclose(fptr);
	printf("\nsize %ld\n", sizeof(arr)/sizeof(arr[0]));
	//e = 10;
	//n=8;
	j = search(arr, n, e);
	printf("e=%d\tid=%d\n\n",e,j);
}

void report_fail(int v,int o){
	printf("Failed at %d",v);
	char* FNAME = "/media/kdam/Data/UCL/code/Project2/Project2/samples/search/search_test.out";
	FILE *fptr;
	fptr = fopen(FNAME,"a");
	fprintf(fptr,"%d %d\n", v,o);
	fclose(fptr);
}

void report_pass(int v,int o){
	char* FNAME = "/media/kdam/Data/UCL/code/Project2/Project2/samples/search/search_test.out";
	FILE *fptr;
	fptr = fopen(FNAME,"a");
	fprintf(fptr,"%d %d\n", v,o);
	fclose(fptr);
}

void test_input(){
	int MAXINT = 10000;
	int input[10] = {1,2,3,4,5,6,7,8,(rand() % (MAXINT - 8)) + 9,-(rand() % (MAXINT - 3)) - 4};
	int n_test= 10;

	char* FNAME = "/media/kdam/Data/UCL/code/Project2/Project2/samples/search/search_test.out";
	FILE *fptr;
	fptr = fopen(FNAME,"w");
	fprintf(fptr,"%d\n", n_test);
	fclose(fptr);

	printf("Test input\n");
	srand(time(NULL));
	
	//int input[16] = {-3,-1,0,4,5,6,7,8,-2,1,2,3,19,100, (rand() % (MAXINT - 8)) + 9,-(rand() % (MAXINT - 3)) - 4};
 	//int tab[10] = {-3,-1,0,4,5,6,7,8,9,10}; 
	
	int tab[8] = {1,2,3,4,5,6,7,8};
	int size = 8;
    int i = 0;
    while(i < 8) { // Test good values
		printf("input= %d ",input[i]);
      int y = search(tab, size, input[i]);
		printf("output= %d\t%d ",y,y==i);
      if (y != i) { report_fail(input[i],-1); }
		else{
		report_pass(input[i],1);
		}
		printf("\n");
		
      i++;
    }
    while (i < n_test) { // Test random values outside the good values
	printf("input= %d ",input[i]);
      int y = search(tab, size, input[i]);
	printf("output= %d\t%d ",y,y==-1);
      if (y != -1) { report_fail(input[i],-1); }
		else{
		report_pass(input[i],1);
		}
	printf("\n");
      i++;
    }
	
}

int main( int argc, char *argv[] ) {
    //classical_test_01();
    //classical_test_02();
    //faulty_test();
    //random_test();
	if( argc == 1 )
	test_();
	else
	test_input();
    printf("All tests succeeded !\n");
    return 0;
}
