#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct Erase;

// THead != TargetType
template<typename THead, typename TTail, typename TargetType>
struct Erase<TypeList<THead, TTail>, TargetType> {
  typedef TypeList<THead, typename Erase<TTail, TargetType>::NewTypeList> NewTypeList;
};

// THead == TargetType
template<typename TTail, typename TargetType>
struct Erase<TypeList<TargetType, TTail>, TargetType> {
  typedef TTail NewTypeList;
};

// TList end reached
template<typename TargetType>
struct Erase<NullType, TargetType> {
  typedef NullType NewTypeList;
};