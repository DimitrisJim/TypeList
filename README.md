# TypeList

[![Build Status](https://travis-ci.com/DimitrisJim/TypeList.svg?token=svLop7oAmpsKYJJMTWFh&branch=master)](https://travis-ci.com/DimitrisJim/TypeList)
[![license](https://img.shields.io/badge/license-MIT-%3Cgreen%3E)](http://www.wtfpl.net/)
[![Language](https://img.shields.io/badge/C++->=11-%3Cgreen%3E)]()

A compile time linked-list like data structure that facilitates the manipulation of C++ types. Implemented using template classes and supporting similar operations as found in runtime equivalent structures.

## Operations:

Name | Arguments | Description
-----|-----------|------------
`Create` | `... Types`: A variable number of types. | Creates a new Typelist out of the given arguments in `Types`. Allows the inclusion of any value. E.g `Create<int, double, char>`.
`Length` | `Typelist`: The typelist for which length is calculated. | Recurses through the typelist counting the number of types contained. The end `Sentinel` is not counted.
`TypeAt` | `Typelist, index`: The typelist and the index of the item in it. | Recurses through typelist until type with index `index` is found. Lack of specialization results in compile time error if out of bounds.
`Pop`    | `Typelist`: The typelist from which we pop the last item and return it. | Recurses and removes last item from the typelist.
`Count`  | `Typelist, T`: Count occurrences of T in typelist | Recurces through typelist incrementally counting the number of times type `T` is contained.