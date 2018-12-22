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

		std::vector<std::vector<path>> A(r);
		for(size_t i = 0; i < r; i++)
			for(size_t j = 0; j < c; j++)
				A[i].push_back(path(setting));

		bool aijNone=true;

		for(size_t i = 0; i < r; i++) {
			for(size_t j = 0; j < c; j++) {
				//base case
				if ((i == 0) && (j == 0)){
					A[0][0] = path(setting);
				}
				if (setting.get(i,j) == CELL_ROCK){
					A[i][j] = path(setting);
					aijNone=false;
					continue;
				}

				//general cases
				path from_above = path(setting);
				path from_left = path(setting);
				bool fromleftisnotnone=false, fromaboveisnotnone=false;

				//above
				//if ((i > 0) && (A[i-1][j])){
				if(i>0){}
					from_above = A[i-1][j];
					if (from_above.is_step_valid(STEP_DIRECTION_DOWN)) {
						from_above.add_step(STEP_DIRECTION_DOWN);
						fromaboveisnotnone=true;
					}
				}

				//left
				//if ((j > 0) && (A[i][j-1])) {
				if(j>0){}
					from_left = A[i][j-1];
					if (from_left.is_step_valid(STEP_DIRECTION_RIGHT)) {
						from_left.add_step(STEP_DIRECTION_RIGHT);
						fromleftisnotnone=true;
					}
				}

				//assignment
				if(fromaboveisnotnone && fromleftisnotnone) {
					A[i][j] = from_above.total_gold() > from_left.total_gold() ? from_above : from_left;
				} else if (fromaboveisnotnone && !fromleftisnotnone) {
					A[i][j] = from_above;
				} else if (fromleftisnotnone && !fromaboveisnotnone) {
					A[i][j] = from_left;
				} else if((!fromaboveisnotnone && !fromleftisnotnone) && i != 0) {
					A[i][j] = path(setting);
					aijNone=false;
				}
			}
		}

		path best(setting);
		for (size_t i = 0; i <= r-1; i++)
			for (size_t j = 0; j <= c-1; j++)
				if(A[i][j].total_gold() > best.total_gold())
					best = A[i][j];
		return best;
	}
}
