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
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  auto maxlen = setting.rows() + setting.columns() - 2;
  path best; path candidate;
  for(int len=0;len<maxlen;len++)
    for(int bits=0;bits<2^len-1;bits++){
      //candidate = start
      for(int k=0;k<len-1;k++){
        //bit=(bits>>k)&1
        if(bits ==1)
          candidate.add_step(STEP_DIRECTION_RIGHT);
        else
          candidate.add_step(STEP_DIRECTION_DOWN);
      }
      if(candidate.is_step_valid(STEP_DIRECTION_RIGHT))
        if(candidate.total_gold()>best.total_gold())
          best=candidate;
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

  // TODO: implement the dynamic programming algorithm, then delete this
  // comment.
  path best(setting);
  return path(setting);
}

}
