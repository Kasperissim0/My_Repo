#include <random>

int RandomNumber() {
  std::random_device RandomSeed; // Get a Random Number to use as a Seed
  std::mt19937 GenerateNumber(RandomSeed()); // Generate a Random Number Using The Seed
  std::uniform_int_distribution<> DistributionRange(1111, 999999999); // Define The Range Of The Number

  return DistributionRange(GenerateNumber); // Generate and return a random number within the specified range
}
