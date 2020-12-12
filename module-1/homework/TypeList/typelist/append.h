#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;


// TypeList NewType
template<typename THead, typename TTail, typename NewType>
struct Append<TypeList<THead, TTail>, NewType> {
  typedef TypeList<THead, typename Append<TTail, NewType>::NewTypeList> NewTypeList;
};

// NullType NewType
template<typename NewType>
struct Append<NullType, NewType> {
  typedef TypeList<NewType, NullType> NewTypeList;
};

// NullType NullType
template<>
struct Append<NullType, NullType> {
  typedef NullType NewTypeList;
};
