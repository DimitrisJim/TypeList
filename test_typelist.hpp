#include "Typelist.hpp"

/**
 * Create a couple of typelists.
 * Creation will be tested further with other ops.
 */
void test_creation(){
    using Typelist::Create;
    using Typelist::Sentinel;

    using t1 = Create<int>::result;
    using t2 = Create<int, bool, double>::result;

    // Abuse it a bit. Creates:
    // t1 = Typelist<int, Sentinel>
    // t2 = Typelist<t1, Sentinel>
    // t3 = Typelist<t2, Sentinel>
    using t3 = Create<Create<Create<Create<Create<Create<int>>>>>>::result;
    using t4 = Create<Sentinel, Sentinel, Sentinel, Sentinel, Sentinel, int>;
}

void test_length(){
    using Typelist::Create;
    using Typelist::Length;
    using Typelist::Sentinel;

    using t1 = Create<int, bool, double>::result;
    using t2 = Create<Create<Create<Create<Create<Create<int>>>>>>::result;

    static_assert(Length<t1>::value == 3, "Length Mismatch");
    static_assert(Length<t2>::value == 1, "Length Mismatch");

    using t3 = Create<Typelist::Sentinel, Typelist::Sentinel>::result;
    static_assert(Length<t3>::value == 0);

    using t4 = Create<
        Sentinel, Sentinel, double, Sentinel, Sentinel, Sentinel, int, Sentinel
        >::result;
    static_assert(Length<t4>::value == 2);
}