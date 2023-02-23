#include "../UaParser.h"

#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

inline uint64_t clock_gettime_ns(clockid_t clock_type = CLOCK_MONOTONIC)
{
    struct timespec ts;
    clock_gettime(clock_type, &ts);
    return uint64_t(ts.tv_sec * 1000000000LL + ts.tv_nsec);
}

/// Sometimes monotonic clock may not be monotonic (due to bug in kernel?).
/// It may cause some operations to fail with "Timeout exceeded: elapsed 18446744073.709553 seconds".
/// Takes previously returned value and returns it again if time stepped back for some reason.
inline uint64_t clock_gettime_ns_adjusted(uint64_t prev_time, clockid_t clock_type = CLOCK_MONOTONIC)
{
    uint64_t current_time = clock_gettime_ns(clock_type);
    if ((prev_time <= current_time))
        return current_time;

    /// Something probably went completely wrong if time stepped back for more than 1 second.
    return prev_time;
}

/** Differs from Poco::Stopwatch only by using 'clock_gettime' instead of 'gettimeofday',
  *  returns nanoseconds instead of microseconds, and also by other minor differences.
  */
class Stopwatch
{
public:
    /** CLOCK_MONOTONIC works relatively efficient (~15 million calls/sec) and doesn't lead to syscall.
      * Pass CLOCK_MONOTONIC_COARSE, if you need better performance with acceptable cost of several milliseconds of inaccuracy.
      */
    explicit Stopwatch(clockid_t clock_type_ = CLOCK_MONOTONIC) : clock_type(clock_type_) { start(); }
    explicit Stopwatch(clockid_t clock_type_, uint64_t start_nanoseconds, bool is_running_)
        : start_ns(start_nanoseconds), clock_type(clock_type_), is_running(is_running_)
    {
    }

    void start()                       { start_ns = nanoseconds(); is_running = true; }
    void stop()                        { stop_ns = nanoseconds(); is_running = false; }
    void reset()                       { start_ns = 0; stop_ns = 0; is_running = false; }
    void restart()                     { start(); }
    uint64_t elapsed() const             { return elapsedNanoseconds(); }
    uint64_t elapsedNanoseconds() const  { return is_running ? nanoseconds() - start_ns : stop_ns - start_ns; }
    uint64_t elapsedMicroseconds() const { return elapsedNanoseconds() / 1000U; }
    uint64_t elapsedMilliseconds() const { return elapsedNanoseconds() / 1000000UL; }
    double elapsedSeconds() const      { return static_cast<double>(elapsedNanoseconds()) / 1000000000ULL; }

    uint64_t getStart() { return start_ns; }

private:
    uint64_t start_ns = 0;
    uint64_t stop_ns = 0;
    clockid_t clock_type;
    bool is_running = false;

    uint64_t nanoseconds() const { return clock_gettime_ns_adjusted(start_ns, clock_type); }
};


int main(int argc, char* argv[]) {
  if (argc != 4) {
    printf("Usage: %s <regexes.yaml> <input file> <times to repeat>\n", argv[0]);
    return -1;
  }

  std::vector<std::string> input;
  {
    std::ifstream infile(argv[2]);
    std::string line;
    while (std::getline(infile, line)) {
      input.push_back(line);
    }
  }

  uap_cpp::UserAgentParser p(argv[1]);

  int n = atoi(argv[3]);
  Stopwatch watch;
  watch.start();
  for (int i = 0; i < n; i++) {
    for (const auto& user_agent_string : input) {
	    auto result = p.parse(user_agent_string);
	    std::cout << user_agent_string << std::endl;
	    std::cout << result.toFullString()<<std::endl;
    }
  }
  watch.stop();
  std::cout << "program runs for " << watch.elapsedMilliseconds() << " ms." << std::endl;

  return 0;
}
