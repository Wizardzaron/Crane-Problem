///////////////////////////////////////////////////////////////////////////////
// cranes_algs.hpp
//
// Algorithms that solve the crane unloading problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crane_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <math.h>

#include "cranes_types.hpp"

namespace cranes {

// Solve the crane unloading problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path crane_unloading_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  // TODO: implement the exhaustive search algorithm, then delete this
  // comment.
// TODO: implement the exhaustive search algorithm, then delete this
    // comment.

    // THIS IS WHAT WE NEED TO DO, WE NEED TO GET ALL THE VALID POSSIBLE PATHS AND GO THROUGH EACH ONE OF THEM IN THE FOR LOOP
    // THEN SAVE THEM ONTO THE BEST, AFTER WE'RE DONE WE GO THROUGH ANOTHER FOR LOOP TO SEE WHICH PATH HAS THE MOST AMOUNT OF CRANE
    // NOTE LOOK FOR JOHNSONS ALGORITHM TO HELP FIND ALL POSSIBLE PATHS
    //  get all paths 2^setting

    // NEED TO CREATE BINARY STRINGS FOR PATH?

    // This is our data structure that'll hold our valid path
    path best(setting);
    
    //it's really 2^test_path <= 2^max_steps

  //the outer for loop is designed to create paths while also iterating through it

    for (unsigned long test_path = 0; test_path <= (1<< max_steps) - 1; test_path++)
    {
      // "create" the path
      cranes::path test(setting); 

      for (size_t step_ix = 0; step_ix < max_steps; step_ix++)
      { // ste
        //std::cout<<"before adding step" << step_ix<< "\n";
        //test.print();
        
        //we use & to check if the bit in our binary string is set (or is 1)
        cranes::step_direction dir = STEP_DIRECTION_EAST;
        
        //so we are comparing the current bit mask which is calculated by step_ix with our current path to see if they are equal to 
        // not equal to 0 and if they aren't we change direction
        // EX: test_path: 01101 step_ix: 00001, 1=1 therefore we go south, now our second step_ix mask is: 00010 since it's we're
        //shifting the bits by 1, there fore 0!=1 therefore we're going east
        if (test_path & (1 << step_ix))
          dir = STEP_DIRECTION_SOUTH;

        if (!test.is_step_valid(dir)) {
          break;
        }
        //test.print();
        test.add_step(dir);
      }

     
      //std::cout<<"after creation\n";
      //test.print();
      if(test.total_cranes() > best.total_cranes()){
        best = test;
      }
    }

   
        return best;
  }


// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
//path crane_unloading_dyn_prog(const grid& setting) {
path crane_unloading_dyn_prog(const grid& setting) {


//need to use set to store the invalid path for the following values (row, column, direction)

//   // grid must be non-empty.
//   assert(setting.rows() > 0);
//   assert(setting.columns() > 0);

  
//   using cell_type = std::optional<path>;

//   std::vector<std::vector<cell_type> > A(setting.rows(),
//                                         std::vector<cell_type>(setting.columns()));

//   A[0][0] = path(setting);
//   assert(A[0][0].has_value());

//   for (coordinate r = 0; r < setting.rows(); ++r) {
//     for (coordinate c = 0; c < setting.columns(); ++c) {

//       if (setting.get(r, c) == CELL_BUILDING){
//         A[r][c].reset();
//         continue;
//         }

//     cell_type from_above = std::nullopt;
//     cell_type from_left = std::nullopt;

// 	    // TODO: implement the dynamic programming algorithm, then delete this
//   // comment.

//    //assert(best->has_value());
// //  //   std::cout << "total cranes" << (**best).total_cranes() << std::endl;

  path best(setting);


   return best;
	}

}
