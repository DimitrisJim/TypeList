namespace Typelist {
    /** Used solely as marker for end of Typelist.
     * Can also use as element but that's asking for trouble.
     **/
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

    /**
     * Pop<Typelist>:
     * --------------
     * Pops and returns the last value of the Typelist as is done in
     * similar list operations. Returns a new Typelist.
     *
     * @tparam Typelist The typelist to pop from.
     *
     * Returns new Typelist as result
     * Returns type popped as type
     *
     */
     template<class Typelist> struct Pop;
     template<class Head, class Tail>
     struct Pop<Typelist<Head, Tail>>{
      private:
        using recurse = Pop<Tail>;
      public:
        using result = Typelist<Head, typename recurse::result>;
        using type = typename recurse::type;
     };
     template<class T>
     struct Pop<Typelist<T, Sentinel>>{
        using result = Sentinel;
        using type = T;
     };

     /**
      * Count<Typelist, T>:
      * -------------------
      * Count occurrences of type T in typelist Typelist.
      *
      * @tparam Typelist
      * @tparam T
      */
     template<class Typelist, class T> struct Count;
     // Initial recursion.
     template<class Head, class Tail, class T>
     struct Count<Typelist<Head, Tail>, T>{
       enum {
         value = Count<Tail, T>::value
       };
     };
     // Match (Typelist contains T as head), increment.
     template<class T, class Tail>
     struct Count<Typelist<T, Tail>, T>{
      enum {
        value = 1 + Count<Tail, T>::value
      };
     };
     // We reach end (See Count<Tail>) and initialize value.
     template<class T>
     struct Count<Sentinel, T>{
       enum {
         value = 0
       };
     };

    /**
     * Append<Typelist, T>:
     * -------------------
     * Append type T at the end of typelist Typelist.
     *
     * @tparam Typelist
     * @tparam T
     */
    template<class Typelist, class T> struct Append;
    // Base Case we finally reach in recursive call
    template<class T> struct Append<Sentinel, T>{
      using result = typename Create<T>::result;
    };
    // Recurse; continously pass Tail with T to ourselves thereby reducing our size
    // on each invocation (until we reach specialization).
    template<class Head, class Tail, class T> struct Append<Typelist<Head, Tail>, T> {
      using result = Typelist<Head, typename Append<Tail, T>::result>;
    };

    /**
     * Contains<Typelist, T>:
     * -------------------
     * Does not make much sense, really, but add it either way. Basically uses Count to check that
     * the value returned is > 0. Simple.
     *
     * @tparam Typelist
     * @tparam T
     */
    template<class Typelist, class T> struct Contains{
      enum {
        value = Count<Typelist, T>::value > 0,
      };
    };

    // End of namespace Typelist
}