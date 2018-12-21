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

  // TODO: implement the exhaustive search algorithm, then delete this
  // comment.
  // step definitions   STEP_DIRECTION_START, STEP_DIRECTION_RIGHT, STEP_DIRECTION_DOWN
  // path contains a grid and a #vector<step># path containing only step_start at start
  // must use path.add_step(step) method to get best gold path
  // must use grid.may_step(coord,coord) to check validity
	path best(setting);

	std::bitset<63> bits;
  // check each sequence of size a, then loop to find all variations of that size
	for (int a = 1; a < max_steps; a++) {
		// generate all variations
		bits = 0;
		for (int c = 0; c <= pow(2,a)-1; c++) {
			path temp(setting);
			// read through binary string, generate path vector
			for (int b = 0; b < a; b++) {
				if (bits[b] == 0) {
					if (temp.is_step_valid(STEP_DIRECTION_RIGHT)) {
						temp.add_step(STEP_DIRECTION_RIGHT);
					}
				}
				else if (bits[b] == 1) {
					if (temp.is_step_valid(STEP_DIRECTION_DOWN)) {
						temp.add_step(STEP_DIRECTION_DOWN);
					}
				}
			}
			/*std::cout << std::endl;
			for (int p = 0; p < a; p++) {
				std::cout << bits[p];
			}*/
			if (temp.total_gold() > best.total_gold()) {
				best = temp;
			}		
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

	// TODO: implement the dynamic programming algorithm, then delete this
	// comment.
	path best(setting);
	std::vector<path> paths;
	std::vector<path> solutions;
	std::vector<path> final;
	paths.push_back(best);

	for (int a = 0; a < setting.rows() + setting.columns() - 1; a++) {
		for (int i = 0; i < paths.size(); i++) {
			int row = paths[i].final_row();
			if (row == setting.rows() - 1
				&& paths[i].is_step_valid(STEP_DIRECTION_RIGHT) == false) {
				final.push_back(paths[i]);
			}
			else if (row == setting.rows() - 1) {
				final.push_back(paths[i]);
			}
			else {
				path current_right = paths[i];
				path current_down = paths[i];
				if (current_right.is_step_valid(STEP_DIRECTION_RIGHT)) {
					current_right.add_step(STEP_DIRECTION_RIGHT);
					solutions.push_back(current_right);
				}
				if (current_down.is_step_valid(STEP_DIRECTION_DOWN)) {
					current_down.add_step(STEP_DIRECTION_DOWN);
					solutions.push_back(current_down);
				}
			}
		}
		std::cout << a << std::endl;
		paths = solutions;
		solutions.clear();
	}

	for (int i = 0; i < final.size(); i++) {
		if (final[i].total_gold() > best.total_gold())
			best = final[i];
	}
	return best;
  //return path(setting);
}

}
