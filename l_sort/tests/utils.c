#include "utils.h"

static const char status[2][10] = {"FAILED", "SUCCEEDED"};
                                         /* RED        GREEN       RESET */
static const char status_color[3][10] = {"\x1B[31m", "\x1B[32m", "\x1B[0m"};

void PrintTestHeader()
{
	printf(GOLD"%-30s %-36s %-10s" RST "\n", "FUNCTION", "TEST CASE", "RESULT");
}

void PrintTestResult(const char *func_name, const int state,  char *test_case)
{
	test_case = strlen(test_case) ? test_case : "default";
	printf("%-30s %-35s %s%10s%s\n", 
			func_name, 
			test_case, 
			status_color[state], status[state], status_color[2]
	);
}

int PrintIntTestResult(	const char *func_name, 
						const int expected,
						const int aquired,  	  
						char *test_case)
{
	int result = (expected == aquired);
	
	PrintTestResult(func_name, result, test_case);
			
	if(0 == result)
	{
		printf(	"%-30s %s%s%d%s %s%s%d%s\n", 
				"", "Expected: ", GREEN, expected, RST", ",
			    "Aquired: ",  RED,   aquired,  RST);
	}
	return !result;
}

int PrintDblTestResult(	const char *func_name, 
						const double expected,
						const double aquired,  	  
						char *test_case)
{
	double tolerance = expected/10000000;
	int result = fabs(expected - aquired) < tolerance;
	PrintTestResult(func_name, result, test_case);
			
	if(0 == result)
	{
		printf("%-30s %s%s%f%s %s%s%f%s\n", 
			   "", "Expected: ", GREEN, expected, RST", ",
			   "Aquired: ",  RED,   aquired,  RST);
	}
	return !result;
}

int PrintStrTestResult(	const char *func_name, 
						const char *expected,
						const char *aquired,  	  
						char *test_case)
{
	int result = !strcmp(expected, aquired);
	
	PrintTestResult(func_name, result, test_case);
			
	if(0 == result)
	{
		printf("%-30s %s%s%s%s %s%s%s%s\n", 
			   "", "Expected: ", GREEN, expected, RST", ",
			   "Aquired: ",  RED,   aquired,  RST);
	}
	return !result;
}
	














