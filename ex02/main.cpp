#include "PmergeMe.hpp"

int main(int argc, char **argv){
  if (argc < 2){
    std::cerr << "Error" << std::endl;
    return 1;
  }
  PmergeMe sorter(argv);
  sorter.sortAndDisplay();
  return 0;
}