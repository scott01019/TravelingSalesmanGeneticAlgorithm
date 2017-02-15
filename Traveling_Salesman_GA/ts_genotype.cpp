#include "functions.h"
#include "ts_genotype.h"

#include <iostream>
#include <stdlib.h>
#include <vector>
using std::cout;
using std::endl;
using std::left;
using std::vector;

//  Default constructor generates random genes
TS_Genotype::TS_Genotype() {
  //  generate 100 genes and give them a random float between 0,1
  for (unsigned int i = 0; i < 100; ++i)
    this->genes_.push_back(RandomFloat(0, 1));
}

//  Constructor given genes and fitness
//  Inputs: const vector of float reference for genes
//  float for fitness
TS_Genotype::TS_Genotype(const vector<float> &genes, float fitness)
  : genes_(genes), fitness_(fitness) { }

//  Name: Breed
//  Purpose: Breeds the current Genotype with the parameter Genotype and returns a child genotype
//  Inputs: const reference to a TS_Genotype which will be the second part
//  Ouput: TS_Genotype which is the result of the reproduction
TS_Genotype TS_Genotype::Breed(const TS_Genotype &parent) const {
  vector<float> child_genes;
  int crossover = rand() % this->genes_.size();
  child_genes.insert(child_genes.end(), this->genes_.begin(),
    this->genes_.begin() + crossover);
  child_genes.insert(child_genes.end(), parent.genes().begin() + crossover,
                      parent.genes().end());
  return TS_Genotype(child_genes);
}

//  Name: Mutate
//  Purpose: Mutates a single gene in the genotype
void TS_Genotype::Mutate() {
  this->genes_[rand() % this->genes_.size()] = RandomFloat(0, 1);
}

//  Name: PrintFitness
//  Purpose: Prints fitness to console.
void TS_Genotype::PrintFitness() const {
  cout << "Fitness: " << this->fitness() << endl;
  cout << endl;
}