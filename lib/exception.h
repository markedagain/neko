/* All content (C) 2013-2014 DigiPen (USA) Corporation, all rights reserved. */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <setjmp.h>
#include <stdlib.h>

enum exceptions {
  EXCEPTION_ONE = 1,
  EXCEPTION_TWO,
  EXCEPTION_THREE
};

#define THROW(exception) do { \
          if (_exp_) \
            longjmp(*_exp_, exception); \
          printf("uncaught exception %d\n", exception); \
          exit(exception); \
        } while (0)

#define TRY(block, catch_block) { \
          jmp_buf *exception_outer = _exp_; \
          jmp_buf exception_inner; \
          _exp_ = &exception_inner; \
          int exception = setjmp(*_exp_); \
          if (!exception) { \
            do block while(0); \
            _exp_ = exception_outer; \
          } \
          else { \
            _exp_ = exception_outer; \
            switch (exception) { \
              catch_block \
              default: \
                THROW(exception); \
            } \
          } \
        }

#define CATCH(exception, block) \
          case exception: \
            do block while (0); \
            break;

#define _throws_ jmp_buf* _exp_

#define INIT_EXCEPTIONS _throws_ = NULL; /* remember to call this at the start of the program */

/*

int divide(_throws_, int a, int b) {
  if (b == 0)
    THROW(EXCEPTION_ONE);
  return a / b;
}

int test(_throws_, int a, int b) {
  try({
    divide(_exp_, 1, 0);
  },
  catch(EXCEPTION_ONE, {
    printf("Caught EXCEPTION_ONE!");
  }))
}

*/

#endif
