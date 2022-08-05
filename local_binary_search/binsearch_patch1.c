// Code from http://www.cprover.org/cprover-manual/cbmc/tutorial/
//
int binsearch(int x)
{
  int a[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,12,16};
  signed low = 0, high = 17;
  signed middle=0;

  while(low < high)
  {
    middle = low + ((high - low) >> 1);
    
    if(a[middle] < x)if((middle == 0 | (0 <= middle & middle < ((sizeof(a)/sizeof(*a)))))) { 
      high = middle;} 
    else if(a[middle] > x)if((middle == 0 | (0 <= middle & middle < ((sizeof(a)/sizeof(*a)))))) { 
      low = middle + 1;} 
    else if((middle == 0 | (0 <= middle & middle < ((sizeof(a)/sizeof(*a)))))) { // a[middle]==x
      return middle;} 
  }

  return -1;
}

int main() {
	int x;
//	x = binsearch(18);
	x = binsearch(0);
//	x = binsearch(5);
}
