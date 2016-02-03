#include <sys/time.h>
struct   timeval  start,stop,diff;

gettimeofday(&start,0);
gettimeofday(&stop,0);
timeval_subtract(&diff,&start,&stop);
log("C RSA总计用时:%ld 微秒",diff.tv_usec);
int   timeval_subtract(struct   timeval*   result,   struct   timeval*   x, struct   timeval*   y)
  {
        int   nsec;

        if   (   x->tv_sec>y->tv_sec   )
                  return   -1;

        if   (   (x->tv_sec==y->tv_sec)   &&   (x->tv_usec>y->tv_usec)   )
                  return   -1;

        result->tv_sec   =   (   y->tv_sec-x->tv_sec   );
        result->tv_usec   =   (   y->tv_usec-x->tv_usec   );

        if   (result->tv_usec<0)
        {
                  result->tv_sec--;
                  result->tv_usec+=1000000;
        }

        return   0;
  }
