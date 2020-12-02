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
#define IS_E_OF_T(n,e) ((e != 0)&&(((unsigned int)n) % ((unsigned int)e) == 0))

// get the coresponding not value of p
#define GET_NOT(n,p) ((n)/(p))

// determins witch number is bigger
#define GET_BIGGER_NUMBER(p,q) (((p) > (q)) ? (p) : (q))

// a modulo for negativ devidents that work with the euclid algoeithem
#define negMOD(n,m) ((n)-(((n)/(m))-1)*(m))
 
// used for operation selection in the code though argument parsing
typedef enum {
  op_not = 3,
  op_scm = 2,
  op_gcd = 1,
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
 * get_gcd
 *
 * @info: calculates the greatest common devider of p and q
 *
 * @param[in]: p: Natural number and Element of the deivider set
 * @param[in]: q: Natural number and Element of the deivider set
 *
 * @return: the greates common devider
 */
unsigned int get_gcd(unsigned int p, unsigned int q){
  unsigned int max = GET_BIGGER_NUMBER(p,q); 
  unsigned int rslt = 0; 

  // for every number between 1 and p or q, witchever is bigger then the other
  for (int i = 1; i <= max; i++)
    // if the modulo opperation beweent p or q and i results in 0,
    // i is a divider of both p and q.
    if ((p % i == 0) && (q % i == 0)) rslt = i;
  return rslt;
}

/**
 * get_scm
 *
 * @info: calculates the smalest common multible of p and q
 *
 * @param[in]: p: Natural number and Element of the deivider set
 * @param[in]: q: Natural number and Element of the deivider set
 *
 * @return: the smalest common multible
 */
unsigned int get_scm(unsigned int p, unsigned int q){
  unsigned int i = GET_BIGGER_NUMBER(p,q); 
  unsigned int rslt = 0;

  // for every number between p or q, witchever is bigger then the other,
  // and the Maximum numeric value of unsigned int.
  // Or, when the scm was determend.
  while ((i < UINT_MAX) && (rslt == 0)){
    // if the modulo opperation beweent i and p or q results in 0,
    // i is a multible of both p and q.
    if ((i % p == 0) && (i % q == 0)) rslt = i;
    i++;
  } 
  return rslt;
}

/**
 * is_number_g0
 *
 * @info: checks if the parameter string is a number and if the number is
 *        greater then 0
 *
 * @param[in]: str: should be a value from argv containing a number 
 *
 * @return: the number, if everything went well
 *          0, when something went wrong
 */
unsigned int is_number_g0(const char* str){
  unsigned int n = 0;
  unsigned char dummy = '\0';
  if ((sscanf(str,"%d%c",&n,&dummy) == 1) && (atoi(str) > 0)) return n;
  else return 0;
}

/**
 * op_pars
 *
 * @info: used to determen what opperation was selected by argument
 *
 * @param[in]: str: should be a value from argv containing the abbreviation of
 *                  the opperation.
 *
 * @return op_code of the corosponding opperation or the error value of
 *         op_codes
 */
op_codes op_pars(const char* str){
  char rslt[4] = {'\0','\0','\0','\0'};
  if (sscanf(str,"%c%c%c%c", rslt, (rslt + 1), (rslt + 2), (rslt + 3)) == 3){
    // greatest common devider
    if ( rslt[0] == 'g' && rslt[1] == 'c' && rslt[2] == 'd' ) return op_gcd;
    // smalest common multible
    if ( rslt[0] == 's' && rslt[1] == 'c' && rslt[2] == 'm' ) return op_scm;
    // not... yeah... who would have though?! ( ._.)
    if ( rslt[0] == 'n' && rslt[1] == 'o' && rslt[2] == 't' ) return op_not;
  }
  return op_fuck;
}

/**
 * euclidGCD
 *
 * @info: an other way to determin the greatest common devider between two 
 *        numbers
 *
 * @param[in]: p: Natural number and Element of the deivider set
 * @param[in]: q: Natural number and Element of the deivider set
 *
 * @return: the greates common devider
 */
int euclidGCD(int q, int p){
  int r = 0;
  if (q > 0) r = q % p;
  if (q < 0) r = negMOD(q,p);
  if (r == 0) return p;
  else euclidGCD(p,r);
}

/*****************************************************************************/

int main (const int argc, const char* argv[]){
  unsigned int n = 0;
  unsigned int p = 0;
  unsigned int q = 0;
  unsigned char op = 0;

  switch (argc){
    case(2): // Print the divider set
      n = is_number_g0(argv[1]);
      if (n != 0)
        print_divider_set(n);
      else {
        fprintf(stderr,"n is 0 or not a number\n");  
        return 1;
      }
    break;
    
    case(4): // Print not p
      n  = is_number_g0(argv[1]);
      p  = is_number_g0(argv[3]);
      if (n == 0){
        fprintf(stderr,"n is 0 or not a number\n");  
        return 1;
      }
      if (IS_E_OF_T(n,p) && (op_pars(argv[2]) == op_not)){
        printf("%d\n", GET_NOT(n,p));
      } else fprintf(stderr,"unkown op or p not e of T\n");
    break;

    case(5): // Print scm/gcd of p and q
      n  = is_number_g0(argv[1]);
      op = op_pars(argv[2]);
      p  = is_number_g0(argv[3]);
      q  = is_number_g0(argv[4]);
      if (n == 0){
        fprintf(stderr,"n is 0 or not a number\n");  
        return 1;
      }
      if ((IS_E_OF_T(n,p)) && (IS_E_OF_T(n,q))){
        switch(op){
          // Print the greatest common devider
          case(op_gcd): printf("%d\n",euclidGCD(p,q));
          //case(op_gcd): printf("%d\n",get_gcd(p,q));
          break;
          // Print the smalest common multible
          case(op_scm):printf("%d\n",get_scm(p,q));
          break;
          
          default: 
            fprintf(stderr,"bad op\n");  
            return 1;
        }
      } else {
        fprintf(stderr,"p or q not e of T or not a number\n");  
        return 1; 
      }
    break;

    default:
      fprintf(stderr,"to many or no args\n");  
      return 1;
  }
  return 0;
}