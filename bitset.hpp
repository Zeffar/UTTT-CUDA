#ifndef BITSET_HPP
#define BITSET_HPP

#include <bitset>
#include <iostream>
template <short M, short N>
class bitset2D
{
private:
  std::bitset<M * N> m_bits;

public:
  typedef typename std::bitset<M * N>::reference reference;
  bitset2D() : m_bits() {}

  // Bit access
  short operator()(short x, short y, short m, short n) const
  {
    // Get two bits from the bitset and combine them
    return short(m_bits[(m + x * 3) * N + (n + y * 3) * 2] << 1) + short(m_bits[(m + x * 3) * N + (n + y * 3) * 2 + 1]);
  }
  // myB (x, y, a, b) = myB[a+x*3][b+y*3]

  short operator[](short m, short n) const
  {
    return short(m_bits[9 * N + m * 3 + n * 2] << 1) + short(m_bits[9 * N + m * 3 + n * 2 + 1]);
  }

  bitset2D<M, N> &operator=(const bitset2D<M, N> &other)
  {
    if(this != &other)
      m_bits = other.m_bits;

    return *this;
  }

  friend std::istream &operator>>(std::istream &in, bitset2D<M, N> &b)
  {
    short x;
    for (short i{}; i < M-1; ++i)
    {
      for (short j{}; j < N/2 - 1; ++j)
      {
        in >> x;
        if(x)
          b.set(i, j, x);
      }
    }
    return in;
  }

  // Bit operations:
  bitset2D<M, N> &set(short m, short n, short val)
  {
    m_bits.set(m*N + n*2 + 2 - val, 1);
    return *this;
  }
};

#endif