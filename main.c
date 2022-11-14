#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
int main()
{
    struct timeval mytime;
	struct timezone mytimezone;



    // 현재 시간을 얻어온다.
	mytime.tv_sec = 0;
	// mytime.tv_usec = 0;
	settimeofday(&mytime, NULL);
	gettimeofday(&mytime, &mytimezone);
    printf("%ld:%ld\n", mytime.tv_sec/3600/24%365/30, mytime.tv_usec);
	printf("%d:%d\n", mytimezone.tz_dsttime, mytimezone.tz_minuteswest);
    return 0;
}