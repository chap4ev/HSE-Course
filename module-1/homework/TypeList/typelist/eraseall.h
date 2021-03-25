#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;


// THead != TargetType
template<typename THead, typename TTail, typename TargetType>
struct EraseAll<TypeList<THead, TTail>, TargetType> {
  typedef TypeList<THead, typename EraseAll<TTail, TargetType>::NewTypeList> NewTypeList;
};

// THead == TargetType
template<typename TTail, typename TargetType>
struct EraseAll<TypeList<TargetType, TTail>, TargetType> {
  typedef typename EraseAll<TTail, TargetType>::NewTypeList NewTypeList;
};

// TList end reached
template<typename TargetType>
struct EraseAll<NullType, TargetType> {
  typedef NullType NewTypeList;
};
