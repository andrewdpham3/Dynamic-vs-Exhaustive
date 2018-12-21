///////////////////////////////////////////////////////////////////////////////
// gnomes_algs.hpp
//
// Algorithms that solve the greedy gnomes problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on gnomes_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <bitset>
#include <math.h>
#include <vector>

#include "gnomes_types.hpp"

namespace gnomes {

// Solve the greedy gnomes problem for the given grid, using an exhaustive
// search algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path greedy_gnomes_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  
  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 1;
  assert(max_steps < 64);
  
  path best(setting);
  std::bitset<63> bits;
  for(int len=1;len<max_steps;len++){
    bits=0;
    for(int c=0;c<pow(2,len)-1;c++){
      path candidate(setting);
      for(int k=0;k<len;k++)
        //int bit = (bits>>k) & 1;
        if(bits[k] == 0){
          if(candidate.is_step_valid(STEP_DIRECTION_RIGHT))
            candidate.add_step(STEP_DIRECTION_RIGHT);
        } else if (bits[k]==1)
          if(candidate.is_step_valid(STEP_DIRECTION_DOWN))
            candidate.add_step(STEP_DIRECTION_DOWN);
      if (candidate.total_gold()>best.total_gold())
        best = candidate;
      int bit_int = bits.to_ullong();
     	bits = bits.to_ulong() + 1;
    }
  }
  return best;
}

// Solve the greedy gnomes problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
path greedy_gnomes_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  
  auto r=setting.rows();
  auto c=setting.columns();

  step_direction a[setting.rows()][setting.columns()];
  //base case
  a[0][0]={STEP_DIRECTION_START};
  /*general cases
  for(int i=0;i<r;i++)
    for(int j=0;c-1;j++){
      //if(setting[i][j]=='X')
        //a[i][j]=
      //from_above = from left = none
      //if(i>0 && a[i-1][j])
      
    }*/
  
  path best(setting);
  return path(setting);
}

}
