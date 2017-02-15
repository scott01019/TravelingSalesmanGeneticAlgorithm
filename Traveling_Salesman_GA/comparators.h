#ifndef COMPARATORS_H_
#define COMPARATORS_H_

#include "ts_genotype.h"

#include <utility>
using std::pair;

//  Compartor for comparing two fitnesses of two TS_Genotype objects
struct FitnessComp {
  bool operator()(const TS_Genotype &lhs, const TS_Genotype &rhs) const {
    return lhs.fitness() < rhs.fitness();
  }
} fitness_comp;

//  Comparator for comparing fitness (the float value) of two pair objects of type int, float.
struct PairOrderComp {
  bool operator()(const pair<int, float> &lhs, const pair<int, float> &rhs) const {
    return lhs.second < rhs.second;
  }
} pair_order_comp;

#endif  //  COMPARATORS_H_