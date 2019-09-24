#include "Typelist.hpp"

/**
 * Create a couple of typelists.
 * Creation will be tested further with other ops.
 */
void test_creation(){
    using Typelist::Create;

    using t1 = Create<int>::result;
    using t2 = Create<int, bool, double>::result;

    // Abuse it a bit. Creates:
    // t1 = Typelist<int, Sentinel>
    // t2 = Typelist<t1, Sentinel>
    // t3 = Typelist<t2, Sentinel>
    using t3 = Create<Create<Create<Create<Create<Create<int>>>>>>;
}