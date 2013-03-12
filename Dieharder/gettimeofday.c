#include <dieharder/libdieharder.h>
#include <time.h>
#include <windows.h> 

const __int64 DELTA_EPOCH_IN_MICROSECS= 11644473600000000;

/* IN UNIX the use of the timezone struct is obsolete;
 I don't know why you use it. See http://linux.about.com/od/commands/l/blcmdl2_gettime.htm
 But if you want to use this structure to know about GMT(UTC) diffrence from your local time
 it will be next: tz_minuteswest is the real diffrence in minutes from GMT(UTC) and a tz_dsttime is a flag
 indicates whether daylight is now in use
*/

int gettimeofday(struct timeval *tv/*in*/, struct timezone *tz/*in*/)
{
  FILETIME ft;
  __int64 tmpres = 0;
  TIME_ZONE_INFORMATION tz_winapi;
  int rez=0;

   ZeroMemory(&ft,sizeof(ft));
   ZeroMemory(&tz_winapi,sizeof(tz_winapi));

    GetSystemTimeAsFileTime(&ft);

    tmpres = ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    /*converting file time to unix epoch*/
    tmpres /= 10;  /*convert into microseconds*/
    tmpres -= DELTA_EPOCH_IN_MICROSECS; 
    tv->tv_sec = (__int32)(tmpres*0.000001);
    tv->tv_usec =(tmpres%1000000);

  return 0;
}

double fmax(double a, double b)
{
   return a > b ? a:b;
}