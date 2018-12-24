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
    for(int len=1;len<max_steps;len++){
      for(int bits=0;bits<pow(2,len)-1;bits++){
        path candidate(setting);
        for(int k=0;k<len;k++){
          auto bit = (bits>>k)&1;
          if(bit==1){
            if(candidate.is_step_valid(STEP_DIRECTION_RIGHT))
              candidate.add_step(STEP_DIRECTION_RIGHT);
          }else
          if(candidate.is_step_valid(STEP_DIRECTION_DOWN))
            candidate.add_step(STEP_DIRECTION_DOWN);
        }
        if (candidate.total_gold()>best.total_gold())
          best = candidate;
      }
    }
    return best;
  }

// Solve the greedy gnomes problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
  path greedy_gnomes_dyn_prog(const grid& setting) {
    const size_t r = setting.rows();
    const size_t c = setting.columns();

  // grid must be non-empty.
    assert(r > 0);
    assert(c > 0);

  // Creating a new rxc matrix
    path ***A;
    A = new path**[r];
    for (int i=0;i<r;++i) {
      A[i] = new path*[c];
    }

  // Initialize A to be all NULL
    for (int i=0;i<r;i++){
      for (int j=0;j<c;j++) {
        A[i][j] = NULL;
      }
    }

    A[0][0] = new path(setting);
    path best(setting);

    int zero = 0;
    path from_above(setting);
    path from_left(setting);

    for (int i=0;i<r;i++){

      for (int j=0;j<c;j++){

        if (setting.get(i,j)==CELL_ROCK){
          continue;
        }

        //fromabover = from left = none
        int *above = NULL;
        int *left = NULL;

        if (i>0 && A[i-1][j] != NULL){
          from_above = *A[i-1][j];

        // from_above != None anymore
          above = &zero;
          if (from_above.is_step_valid(STEP_DIRECTION_DOWN)){
            from_above.add_step(STEP_DIRECTION_DOWN);
          }
        }

        if (j>0 && A[i][j-1] != NULL){
          from_left = *A[i][j-1];

        // from_above != None anymore
          left = &zero;
          if (from_left.is_step_valid(STEP_DIRECTION_RIGHT)){
            from_left.add_step(STEP_DIRECTION_RIGHT);
          }
        }

        if(above != NULL && left != NULL){
          if(from_above.total_gold() >= from_left.total_gold()){
            A[i][j] = new path(from_above);
          }
          else if (from_above.total_gold() < from_left.total_gold()){
            A[i][j] = new path(from_left);
          }
        }
        else if(above == NULL && left!= NULL)
          A[i][j] = new path(from_left);
        else if (above != NULL && left == NULL)
          A[i][j] = new path(from_above);
      }
    }

  // Post Processing to find Max. gold path
    for (int i=0;i<r;i++){
      for (int j=0;j<c;j++){
        if (A[i][j] != NULL && A[i][j]->total_gold() > best.total_gold()){
          best = *A[i][j];
        }
      }
    }

    return best;
  }
}
