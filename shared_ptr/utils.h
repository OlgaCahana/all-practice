#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>


/*******************************************************************************/
/* CPP */
#if __cplusplus > 201102L
    #define NOEXCEPT noexcept
#else
    #define NOEXCEPT throw()
#endif

/******************************************************************************/
/* MIN2 MAX2 ABS */
#define MIN2(x, y) ((x < y) ? x : y)
#define MAX2(x, y) ((x > y) ? x : y)
#define ABS(x) ((x) < 0 ? ((x) * -1) : (x))

/**********************Failure handle*****************************************/
#define LOG(MSG) fprintf(stderr, "msg: %s \n\tfile: %s line: %d compiled at: %s\n",	\
	                 			 #MSG,      __FILE__, __LINE__,      __TIME__); 

#define UNUSED(param) ((void)param)

/* DEADMEM is the go-to bad address: */
#define DEAD_MEM(TYPE) ((TYPE)0xBADC0FFEE0DDF00D)

/* general "return if bad macro: " */
#define RETURN_IF_BAD(IS_GOOD, RET, MSG)                             \
if(!IS_GOOD)                                                         \
{                                                                    \
	fprintf(stderr, MSG);                                            \
	fprintf(stderr, " expression: %s has failed\n", #IS_GOOD);       \
	fprintf(stderr, "file: %s line: %d compiled at: %s\n",           \
	                    __FILE__, __LINE__,      __TIME__);          \
	return RET;                                                      \
}  


#define CHECK_ALLOC_IFBAD_FREE_RETURN(x, FREE, FREE2, RETURN_VAL)	\
do 											 	\
{										 		\
	if (NULL == x)						 		\
	{											\
		fprintf(stderr, "Allocation failed\n");	\
		free(FREE);						 		\
		free(FREE2);						 	\
		return RETURN_VAL;				 		\
	}									 		\
}										 		\
while(0)


#define CHECK_ALLOC(x, FREE, FREE2, RETURN_VAL)	\
do 											 	\
{										 		\
	if (NULL == x)						 		\
	{											\
		fprintf(stderr, "Allocation failed\n");	\
		free(FREE);						 		\
		free(FREE2);						 	\
		return RETURN_VAL;				 		\
	}									 		\
}										 		\
while(0)



/* for backwards compatability only, do not use in new files */
#define CHECK_IF_BAD(x, BAD_RESULT, FREE, FREE2, RETURN_VAL)	\
do 											 	\
{										 		\
	if (x == BAD_RESULT)						 		\
	{											\
		fprintf(stderr, "Got Bad Result\n");	\
		free(FREE);						 		\
		free(FREE2);						 	\
		return RETURN_VAL;				 		\
	}									 		\
}										 		\
while(0)

/*******************************DEBUG**********************************************/
#ifndef NDEBUG
	#define DEBUG_ONLY(exp) exp;
	#define DEBUG_ONLY_ARG(exp) ,exp
#else
	#define DEBUG_ONLY(exp) 
	#define DEBUG_ONLY_ARG(exp)
#endif /* NDEBUG */

#if __cplusplus<201104
#define STATIC_ASSERT(EXP, NAME) enum {NAME = 1/EXP};
#else
#define STATIC_ASSERT(EXP, NAME) static_assert(EXP);
#endif /* cplusplus<201104 */


#endif /*__UTILS_H__*/
