#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_STRINGS 10
#define DICTIONNARY_SIZE 50
#define MAX_STRING_SIZE 15 

char dictionnary[DICTIONNARY_SIZE][MAX_STRING_SIZE] =
{ 
	"allowance",
	"frozen",
	"slump",
	"trail",
	"restrict",
	"residence",
	"language",
	"anniversary",
	"museum",
	"acid",
	"worm",
	"latest",
	"costume",
	"praise",
	"dog",
	"function",
	"recording",
	"houseplant",
	"arch",
	"mobile",
	"accompany",
	"committee",
	"sweep",
	"evening",
	"undertake",
	"redeem",
	"industry",
	"parking",
	"tax",
	"cooperation",
	"item",
	"filter",
	"process",
	"medieval",
	"constitution",
	"example",
	"eliminate",
	"spite",
	"X-ray",
	"reward",
	"inspiration",
	"concern",
	"secretion",
	"reflection",
	"consensus",
	"marathon",
	"flag",
	"impulse",
	"manual",
	"buggy"
};

int main(int argc, char **argv) {
	/* The array we're going to use (at least it's clear that's it's a pointer on pointer :)) */
	char **myArray;
	char *choosenString;

	myArray = malloc(NUMBER_OF_STRINGS * sizeof(char*));
	srand(time(NULL));

	/* Let's fill the arry with NUMBER_OF_STRINGS words from the dictionnary */
	for (int i = 0; i < NUMBER_OF_STRINGS; i++) {
		int strNbr = rand() % 50;
		myArray[i] = malloc((strlen(dictionnary[strNbr])+1) * sizeof(char));
		strncpy(myArray[i], dictionnary[strNbr], strlen(dictionnary[strNbr])+1);
	}
	
	/* Are we going to insert a null value somewhere? */
	int insertNull = rand() % 1;
	
	/* If so let's insert it at a random position */
	if (insertNull == 1) {
		myArray[rand() % NUMBER_OF_STRINGS] = NULL;
	}

	/* Now let's pick one of the value to print it */
	choosenString = myArray[rand() % NUMBER_OF_STRINGS];

	/* Print that value */
	printf("%s\n", choosenString);

	/* Let's print our array */
//	printf("Content of the array:\n");
//	for (int i = 0; i < NUMBER_OF_STRINGS; i++) {
//		printf("%d. %s\t%p\t%p\n", i, myArray[i], myArray[i], &myArray[i]);
//	}
}

