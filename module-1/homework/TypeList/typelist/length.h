#pragma once

#include "typelist.h"

template<typename TList>
struct Length;


template<typename THead, typename TTail>
struct Length<TypeList<THead, TTail>> {
  const static int length = Length<TTail>::length + 1;
};

// reached end of Tlist
template<>
struct Length<NullType> {
  const static int length = 0;
};