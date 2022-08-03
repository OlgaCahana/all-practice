/* Calc API LOG:
    - V 1.0     added header guards.
    - V 1.1     operator_struct and operator_ty typedef 
    */

#ifndef __CALC_H__
#define __CALC_H__

#include "stack.h"
#include "state_mach.h"


typedef struct calculator calc_ty;

typedef struct operator_struct operator_ty;

/* should be moved to source file 
struct calculator 
{
    stack_ty *m_num_stack;
    stack_ty *m_op_stack;
    char *m_curr_token;
}; 

struct operator_struct
{
    int m_precedence;
    double (*m_op_func)(double a, double b);
};

states
typedef enum {WAIT_NUM = 0,
              WAIT_OP = 1, 
              BAD = 2, 
              EXP_END = 3, 
              CALC_NUM_STATES = 4} state_ty;

events
typedef enum {NUMBER = 0, 
              OPERATOR = 1, 
              EQUAL = 2, 
              BAD_TOKEN = 3, 
              NUM_EVENTS = 4} event_ty;

end of move to src file */

/* valid expression should contain at least one digit and assignment operator */
double Calculate(const char *exp);



#endif /* __CALC_H__ */
