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

  // grid must be non-empty.
		assert(setting.rows() > 0);
		assert(setting.columns() > 0);

				size_t r = setting.rows();
		size_t c = setting.columns();

		// grid must be non-empty.
		assert(r > 0);
		assert(c > 0);

		std::vector<std::vector<path>> A(r);

		// Initalize the path matrix
		for(size_t i = 0; i < setting.rows(); i++) {
			for(size_t j = 0; j < setting.columns(); j++) {
				A[i].push_back(path());
			}
		}


		for(size_t i = 0; i < setting.rows(); i++) {
			for(size_t j = 0; j < setting.columns(); j++) {

				// Skip the first cell, which is our starting path
				if ((i == 0) && (j == 0))
				{
					A[0][0] = path(setting);
				}

				if (setting.get(i,j) == CELL_ROCK)
				{
					A[i][j] = path();
					A[i][j].exists = false;
					continue;
				}

				//Paths
				path from_above = path();

				path from_left = path();

				//Check above path in path matrix
				if ((i > 0) && (A[i-1][j]))
				{
					from_above = A[i-1][j];
					if (from_above.is_step_valid(STEP_DIRECTION_DOWN)) {
						from_above.add_step(STEP_DIRECTION_DOWN);
						from_above.exists = true;
					}
				}

				// Check left path in path matrix
				if ((j > 0) && (A[i][j-1])) {
					from_left = A[i][j-1];
					if (from_left.is_step_valid(STEP_DIRECTION_RIGHT)) {
						from_left.add_step(STEP_DIRECTION_RIGHT);
						from_left.exists = true;
					}
				}

				if(from_above && from_left) {
					A[i][j] = from_above.total_gold() > from_left.total_gold() ? from_above : from_left;

				} else if (from_above && !from_left) {
					A[i][j] = from_above;

				} else if (from_left && !from_above) {
					A[i][j] = from_left;

				} else if((!from_above && !from_left) && i != 0) {
					A[i][j] = path();
					A[i][j].exists = false;
				}
			}
		}

		path best(setting);

		for (size_t i = 0; i <= r-1; i++) {
			for (size_t j = 0; j <= c-1; j++) {
				if(A[i][j].total_gold() > best.total_gold()) {
					best = A[i][j];
				}
			}
		}
		return best;
	}
}
