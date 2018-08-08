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
  mpz_t num, startNum, output, count;
  mpz_inits(num, startNum, output, count, NULL);
  printf("Input number:\n");
  gmp_scanf("%Zi", num);
  printf("**************************************************************************\n");
  time_t startTime = clock();
  mpz_set(startNum, num);
  printf("%s\n", mpz_get_str(NULL, 10, num));
  while(mpz_cmp_ui(num, 1) >= 1){
    mpz_add_ui(count, count, 1);
    collatzCalc(num, output);
    {
  	  char *s = mpz_get_str(NULL, 10, output);
      printf("%s\n", s);
      free(s);
	  s = NULL;
    }
    mpz_set(num, output);
  }
  time_t endTime = clock();
  double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
  printf("**************************************************************************\n");
  printf("Info:\n");
  printf("Starting Number: %s\n", mpz_get_str(NULL, 10, startNum));
  printf("Count: %s\n", mpz_get_str(NULL, 10, count));
  printf("Seconds Taken: %f\n", timeSpent);
  char s = NULL;
  printf("Input '0' and press return to exit\n");
  while(s != '0'){ s = getchar(); }
  return 0;
}
