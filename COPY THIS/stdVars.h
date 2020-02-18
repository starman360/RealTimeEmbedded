#ifndef STDVARS_H
#define STDVARS_H

#define MAX_TIME 100000
#define GETALIFE 1

#define POST_ROUTINE_RESTART 	"Would you like to try again? (Y|n): "
#define POST_ROUTINE_COMPLETE 	"POST routine finished successfully.\t\r\n"
#define POST_ROUTINE_FAILED		"POST routine failed.\t\r\n"
#define ENTER_KEY 0x0D
#define BACKSPACE_KEY 0x7F
#define CHANGE_LOWER_LIMIT_Q "Change lower limit (y|n): "
#define ENTER_LOWER_LIMIT "\r\nEnter lower limit: "
#define OUT_OF_RANGE_LIMIT "\r\nLower limit out of range. Select between 50-9950"
#define INVALID_NUMBER_ENTERED "\r\nNot a valid lower limit"
#define INVALID_ENTRY "\r\nNot a valid entry\r\n"
#define WAIT_ENTER "Press enter to begin timing test\r\n"
#define BEGIN_TIMING_TEST "Running timing test\r\n"
#define RUN_TEST_AGAIN "\r\nRun the test again (y|n): "

typedef int bool;
#define true 1
#define false 0

extern int lower_limit;
extern int upper_limit;
extern int ISRFLAG;
extern int done;
extern int iter;
extern int post_complete;

#endif
