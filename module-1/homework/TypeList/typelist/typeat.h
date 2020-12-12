#pragma once

#include "typelist.h"

template<typename TList, unsigned int index>
struct TypeAt;

// index > 0
template<typename THead, typename TTail, unsigned int index>
struct TypeAt<TypeList<THead, TTail>, index> {
  typedef typename TypeAt<TTail, index - 1>::TargetType TargetType;
};

// index == 0
template<typename THead, typename TTail>
struct TypeAt<TypeList<THead, TTail>, 0> {
  typedef THead TargetType;
};

// reached end of TList
template<unsigned int index>
struct TypeAt<NullType, index> {
  typedef NullType TargetType;
};