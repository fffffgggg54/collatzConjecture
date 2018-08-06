/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

/* Function Prototypes */
void collatzCalc(mpz_t inputNum, mpz_t outputNum);

/* Function Definitions */
void collatzCalc(mpz_t inputNum, mpz_t outputNum){
  mpz_t tempPlaceholder;
  mpz_init(tempPlaceholder);
  if(mpz_mod_ui(tempPlaceholder, inputNum, (unsigned int)2) == 0){
    mpz_cdiv_q_ui(outputNum, inputNum, (unsigned int)2);
  }
  else if(mpz_mod_ui(tempPlaceholder, inputNum, (unsigned int)2) == 1){
    mpz_mul_ui(outputNum, inputNum, (unsigned int)3);
    mpz_add_ui(outputNum, outputNum, (unsigned int)1);
  }
  mpz_clear(tempPlaceholder);
}

int main(){

  mpz_t lLimit, uLimit, iteration, num, startNum, output, count, maxCount, numAtMaxCount;
  mpz_inits(lLimit, uLimit, iteration, num, startNum, output, count, maxCount, numAtMaxCount, NULL);

  printf("Input lower limit:\n"); // Prompt the Lower Limit
  gmp_scanf("%Zi", lLimit);
  printf("Input upper limit:\n"); // Prompt the Upper Limit
  gmp_scanf("%Zi", uLimit);
  mpz_set(iteration, lLimit);

  FILE * currFile;
  currFile = fopen ("collatzMaxCountList.txt","w"); /* Open collatzSummaryList.txt for writing */
  setvbuf(currFile, NULL, _IONBF, 1);
  for(; mpz_cmp(iteration, uLimit) <= 0; mpz_add_ui(iteration, iteration, 1)){
    
    mpz_set(num, iteration);
    mpz_set(startNum, num);
    
    {
  	  char *s = mpz_get_str(NULL, 10, iteration);
      printf("%s\n", s);
      free(s);
	  s = NULL;
    }

    time_t startTime = clock(); // Start recording time
    mpz_set_ui(count, (unsigned int)0);
    while(mpz_cmp_ui(num, 1) >= 1){
      mpz_add_ui(count, count, 1);
      collatzCalc(num, output);
      mpz_set(num, output);
    }
    time_t endTime = clock(); // Stop recording time
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
   /* fprintf(currFile, "**************************************************************************\n");
    fprintf(currFile, "Info:\n");
    {
  	  char *s = mpz_get_str(NULL, 10, startNum);
      fprintf(currFile, "Starting Number: %s\n", s);
      free(s);
	  s = NULL;
    }
    {
  	  char *s = mpz_get_str(NULL, 10, count);
      fprintf(currFile, "Count: %s\n", s);
      free(s);
	  s = NULL;
    }
    fprintf(currFile, "Seconds Taken: %f\n", timeSpent);*/
    if(mpz_cmp(count, maxCount) > 0){
      mpz_set(maxCount, count);
      mpz_set(numAtMaxCount, iteration);
      {
  	    char *s = mpz_get_str(NULL, 10, startNum);
        fprintf(currFile, "Starting Number: %s\t|\t", s);
        free(s);
	    s = NULL;
      }
      {
  	    char *s = mpz_get_str(NULL, 10, count);
        fprintf(currFile, "Count: %s\n", s);
        free(s);
	    s = NULL;
      }
    }
  }
  printf("Greatest Count: %s at %s\n", mpz_get_str(NULL, 10, maxCount), mpz_get_str(NULL, 10, numAtMaxCount));
  char s;
  printf("Input '0' and press return to exit\n");
  while(s != '0'){ s = getchar(); }
  return 0;
}
