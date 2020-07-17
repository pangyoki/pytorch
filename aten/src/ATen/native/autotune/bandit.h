#pragma once

#include <chrono>
#include <cstdint>
#include <functional>
#include <map>
#include <random>
#include <string>
#include <vector>

#include <ATen/native/autotune/definitions.h>
#include <ATen/native/autotune/estimator.h>

namespace bandits {

static size_t thompson_k = 1;
using callback = std::function<void(double)>;


class GaussianBandit {
 public:
  GaussianBandit(autotune::cost_priors priors, uint64_t seed);
  autotune::DispatchChoice select();
  void update(autotune::DispatchChoice choice, double value);

 private:
  std::map<autotune::DispatchChoice, autotune::GaussianEstimator> distributions_;
  std::mt19937 engine_;
};






















class Bandit {
 public:
  Bandit(std::vector<double> priors, uint64_t seed, std::string repr);


  class Callback {
   public:
    Callback(Bandit* b, size_t choice): choice_(choice), b_(b) {};
    static Callback make_empty(){ return Callback(nullptr, 0); };
    void start() { t0_ = std::chrono::high_resolution_clock::now(); };
    void end();
    size_t choice_;

   private:
    Bandit* b_;
    std::chrono::time_point<std::chrono::high_resolution_clock> t0_;
  };

  Callback sample();

 private:
  std::string repr_;
  size_t n_;
  std::vector<double> mu_;
  std::vector<size_t> counts_;
  double upper_bound_;
  std::mt19937 engine_;

  double initial_upper_bound_;
  void print();
};
} // namespace bandits