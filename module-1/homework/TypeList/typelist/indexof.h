#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;


// THead != TargetType
template<typename THead, typename TTail, typename TargetType>
struct IndexOf<TypeList<THead, TTail>, TargetType> {
  const static int pos = (IndexOf<TTail, TargetType>::pos == -1) ? -1 : IndexOf<TTail, TargetType>::pos + 1;
};

// THead == TargetType
template<typename TTail, typename TargetType>
struct IndexOf<TypeList<TargetType, TTail>, TargetType> {
  const static int pos = 0;
};

// reached end of Tlist
template<typename TargetType>
struct IndexOf<NullType, TargetType> {
  const static int pos = -1;
};
