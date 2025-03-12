#ifndef OFFLINE_RANDOM_H
#define OFFLINE_RANDOM_H

#include <random>


int get_random_number() {
  std::random_device rd;
  std::mt19937 generator(rd());

  // Lambda value for the Poisson distribution
  double lambda = 10000.234;
  std::poisson_distribution<int> poissonDist(lambda);
  return poissonDist(generator);
}

int get_random_from_array(double* arr, int size) {
  return arr[get_random_number() % size];
}

#endif
