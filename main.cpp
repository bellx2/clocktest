#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sys/time.h>
#include <ctime>

#include "clx/format.h"
#include "clx/time.h"
#include "cmdline.h"



using std::cout; using std::endl;

int main(int argc, char* argv[]) {

  cmdline::parser p;

  p.add<int>("time", 't', "time sec", false, 0);

  p.parse_check(argc, argv);

  if (p.exist("help")){
		cout << p.error_full() << p.usage();
		exit(0);
	}	

  if (p.get<int>("time") == 0){
  
    // Get ms (ns)

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);

    cout << "*** gettimeofday() ***" << endl;
    cout << "seconds since epoch: " << time_now.tv_sec << endl;
    cout << "milliseconds since epoch: "  << msecs_time << endl;
    cout << "tv_usec (Microseconds): " << time_now.tv_usec << endl;
    cout << "tv_usec (ms): " << time_now.tv_usec / 1000 << endl;

    // Get ms (ns)

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    cout << endl << "*** clock_gettime() ***" << endl;
    cout << "seconds since epoch: " << ts.tv_sec << endl;
    cout << "tv_usec (Nanoseconds): " << ts.tv_nsec << endl;
    cout << "tv_usec (ms): " << ts.tv_nsec / 1000 / 1000 << endl;

    cout << endl << "*** to clx::date_time ***" << endl;
    // sec to clx::date_time
    cout << clx::date_time( ts.tv_sec ).to_string<char>() << clx::format(".%03d") % (ts.tv_nsec / 1000 / 1000) << endl;
    // defualt clx::datetime constructor
    cout << clx::date_time().to_string<char>() << endl;

  } else {
 
    cout << "seconds since epoch: " << p.get<int>("time") << endl;
    cout << clx::date_time( p.get<int>("time") ).to_string<char>() << endl;
 
  }

  return 0;
}
