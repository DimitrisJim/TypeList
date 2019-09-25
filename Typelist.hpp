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
     *
     * @tparam T: we consume Types pack by using this extra type.
     * @tparam Types: template argument pack to grab all types.
     */
    template<typename T, typename ... Types>
    struct Create{
       using result = Typelist<T, typename Create<Types...>::result>;
    };
    // Partial specialisation for leading Sentinel
    template<typename ... Types>
    struct Create<Sentinel, Types ...>{
      using result = typename Create<Types...>::result;
    };
    // Total specialisation for sentinels:
    template<>
    struct Create<Sentinel>{
      using result = Sentinel;
    };
    // Base case:
    template<typename T>
    struct Create<T>{
       using result = Typelist<T, Sentinel>;
    };

    /**
     * Length<Typelist>:
     * ----------------------
     * Recursively create our types by passing Tail to Length.
     *
     * @tparam TypeList: The Typelist for which we count.
     */
    template<class TypeList> struct Length;
    template<> struct Length<Sentinel>{
      enum { value = 0 };
    };
    template<> struct Length<Typelist<Sentinel, Sentinel>>{
      enum { value = 0 };
    };
    template<class Head, class Tail>
    struct Length<Typelist<Head, Tail>>{
      enum { value = 1 + Length<Tail>::value };
    };

    /**
     * TypeAt<Typelist, index>:
     * ------------------------
     * Get type in typelist with index i. Negative indices not allowed
     * by using unsigned for index.
     *
     * TODO: Handle out of bounds access?
     *
     * @tparam Typelist Typelist we operate on
     * @tparam index    index for which we query type.
     */
    template<class Typelist, unsigned int index> struct TypeAt;
    // Specialise for index == 0
    template<class Head, class Tail>
    struct TypeAt<Typelist<Head, Tail>, 0>{
        using result = Head;
    };
    // Recurse:
    template<class Head, class Tail, unsigned int index>
    struct TypeAt<Typelist<Head, Tail>, index>{
        using result = typename TypeAt<Tail, index-1>::result;
    };
    // For out of bounds (I.e we reach end Sentinel) don't raise error.
    // Simply return the Sentinel.
    template<unsigned int i>
    struct TypeAt<Sentinel, i>{
      using result = Sentinel;
    };

    // End of namespace Typelist
}