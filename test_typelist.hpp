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
    // Allow sentinels.
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
    static_assert(Length<t3>::value == 2, "Length Mismatch");

    using t4 = Create<
        Sentinel, Sentinel, double, Sentinel, Sentinel, Sentinel, int, Sentinel
        >::result;
    static_assert(Length<t4>::value == 8, "Length Mismatch");
    using t5 = Create<Sentinel>::result;
    static_assert(Length<t5>::value == 1, "Length Mismatch");
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
    //using res2 = TypeAt<t1, 3>::result;
    // static_assert(is_same<res2, Sentinel>::value, "Type Mismatch");

    using t2 = Create<Sentinel, Sentinel>::result;
    using res2 = TypeAt<t2, 0>::result;
    static_assert(is_same<res2, Sentinel>::value, "Type Mismatch");
}

/**
 * Basic test for pop from empty Typelist in non-applicable; we can't create an empty
 * Typelist.
 */
void test_pop(){
    using Typelist::Create;
    using Typelist::Pop;
    using std::is_same;
    using Typelist::Length;

    using t1 = Create<int, double, char>::result;
    using res1 = Pop<t1>;
    static_assert(is_same<res1::type, char>::value, "Error type mismatch");
    static_assert(Length<res1::result>::value == 2, "Error length mismatch");

    using res2 = Pop<Typelist::Typelist<int, Typelist::Sentinel>>;
    static_assert(is_same<res2::type, int>::value, "Error type mismatch");
    static_assert(Length<res2::result>::value == 0, "Error length mismatch");
}

void test_count(){
    using Typelist::Count;
    using Typelist::Create;
    using Typelist::Sentinel;

    // Basic checking.
    using t1 = Create<int, int, int, double>::result;
    static_assert(Count<t1, int>::value == 3, "Error Count mismatch");
    static_assert(Count<t1, double>::value == 1, "Error Count mismatch");
    static_assert(Count<t1, void>::value == 0, "Error Count mismatch");

    // We don't count the end Sentinel, ever.
    using t2 = Create<Sentinel, Sentinel, Sentinel>::result;
    static_assert(Count<t2, Sentinel>::value == 3, "Error count mismatch");
}

void test_append(){
    using Typelist::Count;
    using Typelist::Create;
    using Typelist::Append;
    using Typelist::TypeAt;
    using Typelist::Length;
    using Typelist::Sentinel;
    using std::is_same;

    // Basic checking.
    using t1 = Create<int, int, int, double>::result;
    using t2 = Append<t1, float>::result;

    static_assert(Length<t2>::value == 5, "Error Length mismatch");
    static_assert(Count<t2, float>::value == 1, "Error Count mismatch");
    using t = TypeAt<t2, 4>::result;
    static_assert(is_same<t, float>::value, "Error TypeAt mismatch");

    // Create a one element typelist
    using t3 = Append<Sentinel, int>::result;
    static_assert(Length<t3>::value == 1, "Error Length mismatch");
    static_assert(is_same<TypeAt<t3, 0>::result, int>::value, "Error TypeAt mismatch");
}

void test_contains(){
    using Typelist::Contains;
    using Typelist::Create;
    using Typelist::Sentinel;

    // Basic checking.
    using t1 = Create<int, int, int, double>::result;
    static_assert(Contains<t1, int>::value, "Error Contains mismatch");
    static_assert(Contains<t1, double>::value, "Error Contains mismatch");
    static_assert(Contains<t1, void>::value == 0, "Error Contains mismatch");
    // We don't count the end Sentinel, ever.
    static_assert(Contains<t1, Sentinel>::value == 0, "Error Contains mismatch");
}
