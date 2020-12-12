#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType>
struct Replace;


// THead != OldType
template<typename THead, typename TTail, typename OldType, typename NewType>
struct Replace<TypeList<THead, TTail>, OldType, NewType> {
  typedef TypeList<THead, typename Replace<TTail, OldType, NewType>::NewTypeList> NewTypeList;
};

// THead == OldType
template<typename TTail, typename OldType, typename NewType>
struct Replace<TypeList<OldType, TTail>, OldType, NewType> {
  typedef TypeList<NewType, TTail> NewTypeList;
};

// TList end reached
template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
  typedef NullType NewTypeList;
};