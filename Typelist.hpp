namespace Typelist {
    /** Used solely as marker for end of Typelist. */
    class Sentinel{};

    /**
     * Typelist structure. Holds two types in linked list fashion.
     * @tparam type T functions as head of Typelist
     * @tparam type U functions as tail of Typelist
     */
    template<typename T, typename U>
    struct Typelist{
        using Head = T;
        using Tail = U;
    };

    /**
     * Operations on Typelists
     * -----------------------
     *
     * All work in a similar way. Defining edge cases by total or partial specialisation
     * and then typedef'ing or using their results. By recursively calling ourselves we're
     * able to incrementally build the result.
    */

    /**
     * Create<T1, T2, ..., TN>:
     * ------------------------
     * Works by recursively building a Typelist. Define a template that accepts an arbitrary
     * amount of type parameters in a pack and passes them on to itself after extracting the
     * first type.
     *
     * A specialization handles the case where a single type is supplied (and it is also the base
     * case for our recursion returning a Typelist with a Sentinel as it's Tail)
     */
     template<typename T, typename ... Types>
     struct Create{
         using result = Typelist<T, typename Create<Types...>::result>;
     };
     // Base case:
     template<typename T>
     struct Create<T>{
         using result = Typelist<T, Sentinel>;
     };

}