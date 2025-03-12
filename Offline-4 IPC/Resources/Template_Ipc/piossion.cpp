#include <iostream>
#include <random>

// Function to generate a Poisson-distributed random number
int get_random_number(std::mt19937& generator, double lambda) {
  std::poisson_distribution<int> poissonDist(lambda);
  return poissonDist(generator);
}

int main() {
  std::random_device rd;
  std::mt19937 generator(rd());

  double lambda = 10.0;  // Smaller lambda value for more variability

  // Loop to print 30 Poisson-distributed random numbers
  for (int i = 0; i < 10; i++) {
    std::cout << get_random_number(generator, lambda) << std::endl;
  }

  return 0;
}
