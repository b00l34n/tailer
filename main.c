/**
 * NAME: tailer
 * AUTH: A.P.C.S. - monday
 * DATE: 2020.11.23
 * DESC:
 *   It's a little program to implement divider algebra.
 *   Posible to nest multible opperations through shell and sub-shells.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Check if e is an element of the divider set of n
#define IS_E_OF_T(n,e) (((unsigned int)n) % ((unsigned int)e) == 0)

// get the coresponding not value of p
#define GET_NOT(n,p) ((n)/(p))

// used for operation selection in the code though argument parsing
typedef enum {
  op_not = 3,
  op_kgv = 2,
  op_ggt = 1,
  op_fuck = 0
} op_codes;

/*****************************************************************************/

/**
 * print_usage
 *
 * WIP
 */
void print_usage(FILE* stream){
  /* WIP */
}

/**
 * print_divider_set
 * 
 * @info: print the elements of divider set of n
 *
 * @param[in] n: Natural number used as the maximum value of the divider set
 *
 * @stdout: list of numbers seperaited with wightspaces
 */
void print_divider_set(unsigned int n){
    for (int i = 1; i <= n; i++) 
      if (n % i == 0) printf("%d ", i);
    printf("\n");
}

/**
 * get_ggt
 *
 */
unsigned int get_ggt(unsigned int p, unsigned int q){
  unsigned int max = (p > q) ? p : q;
  unsigned int rslt = 0;

  for (int i = 1; i <= max; i++)
    if ((p % i == 0) && (q % i == 0)) rslt = i;
  return rslt;
}

/**
 * get_kgv
 *
 */
unsigned int get_kgv(unsigned int p, unsigned int q){
  unsigned int i = (p > q) ? p : q; 
  unsigned int rslt = 0;

  while ((i < UINT_MAX) && (rslt == 0)){
    if ((i % p == 0) && (i % q == 0)) rslt = i;
    i++;
  } 
  return rslt;
}

/**
 * is_number_g0
 *
 */
unsigned int is_number_g0(const char* str){
  unsigned int n = 0;
  unsigned char dummy = '\0';
  if ((sscanf(str,"%d%c",&n,&dummy) == 1) && (n > 0)) return n;
  else return 0;
}

/**
 * op_pars
 *
 */
op_codes op_pars(const char* str){
  char rslt[4] = {'\0','\0','\0','\0'};
  if (sscanf(str,"%c%c%c%c",rslt ,rslt + 1,rslt + 2,rslt + 3) == 3){
    if ( rslt[0] == 'g' && rslt[1] == 'g' && rslt[2] == 't' ) return op_ggt;
    if ( rslt[0] == 'k' && rslt[1] == 'g' && rslt[2] == 'v' ) return op_kgv;
    if ( rslt[0] == 'n' && rslt[1] == 'o' && rslt[2] == 't' ) return op_not;
  }
  return op_fuck;
}

/*****************************************************************************/

int main (const int argc, const char* argv[]){
  unsigned int n = 0;
  unsigned int p = 0;
  unsigned int q = 0;
  unsigned char op = 0;

  switch (argc){
    case(2):
      n = is_number_g0(argv[1]);
      if (n != 0)
        print_divider_set(n);
      else {
        fprintf(stderr,"n is 0\n");  
        return 1;
      } // Print T_n
    break;
    
    case(4): // Print Not p
      n  = is_number_g0(argv[1]);
      p  = is_number_g0(argv[3]);
      if (n == 0){
        fprintf(stderr,"n is 0\n");  
        return 1;
      }
      if (IS_E_OF_T(n,p) && (op_pars(argv[2]) == op_not)){
        printf("%d\n", GET_NOT(n,p));
      } else fprintf(stderr,"unkown op or p not e of T\n");
    break;

    case(5): // Print kgv/ggt of p and q
      n  = is_number_g0(argv[1]);
      op = op_pars(argv[2]);
      p  = is_number_g0(argv[3]);
      q  = is_number_g0(argv[4]);
      if (n == 0){
        fprintf(stderr,"n is 0\n");  
        return 1;
      }
      if ((IS_E_OF_T(n,p)) && (IS_E_OF_T(n,q))){
        switch(op){
          case(op_ggt): printf("%d\n",get_ggt(p,q));
          break;
          
          case(op_kgv):printf("%d\n",get_kgv(p,q));
          break;
          
          default: 
            fprintf(stderr,"bad op\n");  
            return 1;
        }
      } else {
        fprintf(stderr,"p or q not e of T\n");  
        return 1; 
      }
    break;

    default:
      fprintf(stderr,"to many or no args\n");  
      return 1;
  }
  return 0;
}