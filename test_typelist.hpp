#include <type_traits>
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
    using t3 = Create<Create<Create<Create<Create<Create<int>>>>>>::result;
    using t4 = Create<Sentinel, Sentinel, Sentinel, Sentinel, Sentinel, int>;

    // No arguments not allowed (should it?)
    // using t5 = Create<>::result;
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
    static_assert(Length<t3>::value == 0, "Length Mismatch");

    using t4 = Create<
        Sentinel, Sentinel, double, Sentinel, Sentinel, Sentinel, int, Sentinel
        >::result;
    static_assert(Length<t4>::value == 2, "Length Mismatch");
}

void test_typeof(){
    using Typelist::Create;
    using Typelist::TypeAt;
    using Typelist::Sentinel;
    using std::is_same;

    // Basic test:
    using t1 = Create<int, double, char>::result;
    using res1 = TypeAt<t1, 2>::result;
    static_assert(is_same<res1, char>::value, "Type Mismatch");

    // Go out of bounds, return sentinels:
    using res2 = TypeAt<t1, 10>::result;
    static_assert(is_same<res2, Sentinel>::value, "Type Mismatch");

    using t2 = Create<Sentinel, Sentinel>::result;
    using res2 = TypeAt<t2, 0>::result;
    static_assert(is_same<res2, Sentinel>::value, "Type Mismatch");
}