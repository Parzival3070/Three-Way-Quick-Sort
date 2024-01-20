#include "QuickTester.h"
#include "InstrumentationTimer.h"

#define PROFILING 0
#if PROFILING
#define PROFILE_SCOPE(name) InstrumentationTimer timer##__LINE__(name)
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCTION__)
#else
#define PROFILE_SCOPE(name)
#define PROFILE_FUNCTION()
#endif

#define type int
#define range 1000

int main() {
    Instrumentor::Get().BeginSession("Profile");
    QuickTester<type, range> sort;

    //sort.test(100'000'000);
    sort.benchmark();
    //sort.graph();
    Instrumentor::Get().EndSession();

    return 0;
}
