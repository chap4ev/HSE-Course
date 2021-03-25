#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;


template<typename THead, typename TTail>
struct NoDuplicates<TypeList<THead, TTail>> {
  typedef TypeList<THead, typename NoDuplicates<typename EraseAll<TTail, THead>::NewTypeList>::NewTypeList> NewTypeList;
};

template<>
struct NoDuplicates<NullType> {
  typedef NullType NewTypeList;
};