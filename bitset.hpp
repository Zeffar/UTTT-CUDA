#ifndef BITSET_HPP
#define BITSET_HPP

#include <bitset>
#include <iostream>
template <size_t M, size_t N>
class bitset2D
{
private:
  std::bitset<M*N> m_bits;
  
public:
  typedef typename std::bitset<M*N>::reference reference;
  bitset2D() : m_bits(){}

  //Bit access
  bool operator()(size_t m, size_t n) const {
    return m_bits[m*N + n];
  }

  reference operator()(size_t m, size_t n) {
    return m_bits[m*N + n];
  }

  //Bit operations:
  bitset2D<M, N>& reset() {
    m_bits.reset(); 
    return *this;
  }

  bitset2D<M, N>& reset(size_t m, size_t n) {
    m_bits.reset(m*N + n); 
    return *this;
  }

  bitset2D<M, N>& flip() {
    m_bits.flip(); 
    return *this;
  }

  bitset2D<M, N>& flip(size_t m, size_t n) {
    m_bits.flip(m*N + n); 
    return *this;
  }

  bitset2D<M, N>& set() {m_bits.set(); 
  return *this;
  }

  bitset2D<M, N>& set(size_t m, size_t n, bool val = true) {
    m_bits.set(m*N + n, val); 
    return *this;
  }

  //Bitset operations:
  unsigned long to_ulong() const {
    return m_bits.to_ulong();
  }

  template <class charT, class traits, class Allocator>
  unsigned long count() const {
    return m_bits.count();
  }
  unsigned long size() const {
    return m_bits.size();
  }
  unsigned long test(size_t m, size_t n) const {
    m_bits.test(m*N + n); 
    return *this;
  }
  unsigned long any() const {
    return m_bits.any();
  }
  unsigned long none() const {
    return m_bits.none();
  }

  void debug() {
    for(short j{}; j < N; j+=2) {
      std::cout<<(*this)(M-1, j)*2 + (*this)(M-1, j+1)<<" ";
      if((j/2)%3==2) std::cout<<'\n';
    } //big board (toDo: make it clean)

    for(short i{}; i < M-1; ++i) {
        for(short j{}; j < N; j+=2) 
            std::cout<<(*this)(i, j)*2 + (*this)(i, j+1)<<" ";
        std::cout<<'\n';
    } //small board
  }


};
#endif