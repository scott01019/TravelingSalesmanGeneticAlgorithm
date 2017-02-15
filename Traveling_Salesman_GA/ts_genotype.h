#ifndef TS_GENOTYPE_H_
#define TS_GENOTYPE_H_

#include <vector>
using std::vector;

//  A class to represent a genotype of a member of a population
class TS_Genotype {
public:
  //  constructors
  TS_Genotype();
  TS_Genotype(const vector<float> &genes) : genes_(genes) {}
  TS_Genotype(const vector<float> &, float);

  //  methods
  TS_Genotype Breed(const TS_Genotype &) const;
  void Mutate();
  void PrintFitness() const;
  void PrintToFile() const;
  
  //  getters
  float fitness() const { return this->fitness_; }
  const vector<float> &genes() const { return this->genes_; }

  //  setters
  void set_fitness(float fitness) { this->fitness_ = fitness; }
  void set_genes(const vector<float> &genes) { this->genes_ = genes; }
private:
  float fitness_;       //  value for fitness
  vector<float> genes_; //  Vector of floats for representing genome.
                        //  Float values are weights for order of which
                        //  city should be visited (lowest first, highest last).
                        //  Indicies of the vector correspond to the indicies of the
                        //  cities vector of the TS_GA class. genes_[0] corresponds to
                        //  cities_[0], ..., genes_[i] corresponds to cities_[i], etc.
};

#endif  //  TS_GENOTYPE_H_