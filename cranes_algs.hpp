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
#include <memory>
using namespace std;

namespace cranes
{

  // Solve the crane unloading problem for the given grid, using an exhaustive
  // optimization algorithm.
  //
  // This algorithm is expected to run in exponential time, so the grid's
  // width+height must be small enough to fit in a 64-bit int; this is enforced
  // with an assertion.
  //
  // The grid must be non-empty.
  path crane_unloading_exhaustive(const grid &setting)
  {

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

    // it's really 2^test_path <= 2^max_steps

    // the outer for loop is designed to create paths while also iterating through it

    for (unsigned long test_path = 0; test_path <= (1 << max_steps) - 1; test_path++)
    {
      // "create" the path
      cranes::path test(setting);

      for (size_t step_ix = 0; step_ix < max_steps; step_ix++)
      { // ste
        // std::cout<<"before adding step" << step_ix<< "\n";
        // test.print();

        // we use & to check if the bit in our binary string is set (or is 1)
        cranes::step_direction dir = STEP_DIRECTION_EAST;

        // so we are comparing the current bit mask which is calculated by step_ix with our current path to see if they are equal to
        //  not equal to 0 and if they aren't we change direction
        //  EX: test_path: 01101 step_ix: 00001, 1=1 therefore we go south, now our second step_ix mask is: 00010 since it's we're
        // shifting the bits by 1, there fore 0!=1 therefore we're going east
        if (test_path & (1 << step_ix))
        {
          dir = STEP_DIRECTION_SOUTH;
        }

        if (!test.is_step_valid(dir))
        {
          break;
        }
        // test.print();
        test.add_step(dir); // dir = south or east
      }

      // std::cout<<"after creation\n";
      // test.print();
      if (test.total_cranes() > best.total_cranes()) //comparing new path with previous path
      {
        best = test;
      }
    }

    return best;
  }

  // Solve the crane unloading problem for the given grid, using a dynamic
  // programming algorithm.
  //
  // The grid must be non-empty.
  // path crane_unloading_dyn_prog(const grid& setting) {
  path crane_unloading_dyn_prog(const grid &setting)
  {

    // need to use set to store the invalid path for the following values (row, column, direction)

    // grid must be non-empty.
    //assert(setting.rows() > 0);
    //assert(setting.columns() > 0);

    //doesnt work in the code the optional 
    //using cell_type = std::optional<path>; // cell_type object of path
    //using cell_type = unique_ptr<path>;
    using cell_type = shared_ptr<path>;

    vector<vector<cell_type>> A(setting.rows(), vector<cell_type>(setting.columns()));
    //vector<vector<cell_type>> A(setting.rows());

    // for(auto& vec : A)
    // {
    //   vec.resize(setting.columns());
    // }


    path *best = nullptr; // pointing at the cell or coordinates
    //A[0][0] = path(setting);
    //A[0][0] = make_unique<path>(setting); // starting from the beginning 
    //assert(A[0][0].get());
    A[0][0] = make_shared<path>(setting);

    for (coordinate r = 0; r < setting.rows(); ++r)
    {
      for (coordinate c = 0; c < setting.columns(); ++c) // we are creating 2d array of rows or columns 
      { // its gonna move at row 0 then column 1.....5
      // then row 1 then column 0,1.....
        //retriving the current value setting(grid object)
        if (setting.get(r, c) == CELL_BUILDING) // if we checking if the current cell has building
        {
          A[r][c].reset(); // if its a building reset 
          continue; // continue the loop
        }

       

        // TODO: implement the dynamic programming algorithm, then delete this
        // comment.
        

        // is to check the value on the previous row
        //cell_type from_above = nullopt
        cell_type from_above = nullptr; // if its outbound or prevents us to go out of bound from row or column
        // nullopt is failsafe to make us avoid getting out of bound
        // we are using r > 0 because if we want to check from above it will cause on error because 
        // we will start from the 0 rows
        if (r > 0) // so if r randomely greator than zero could be at row 1, 2, ..
        {
          //from_above A[r-1][c]
          from_above = A[r - 1][c]; // we are getting the value above the current cell 
        }

        //cell_type from_left = nullopt
        cell_type from_left = nullptr;  // looking at column corresponds to column
        if(c > 0) // we said c > 0 because we want to check the value before if its greator from above 
        {
          //from_left = A[r][c-1]
          from_left = A[r][c-1]; // retrieving previous column 
        } 

        //  0 -> from above 
        //from_left ->2 2 A[r][c] = profit 
        // checcking if there is a valid path 
        if(from_above == nullptr) // if we cannot go up without going out of bound
        { // 
          if(c > 0 && A[r][c -1] != nullptr)
          {
            //A[r][c] = A[r][c-1]
            //A[r][c] = A[r][c-1]; // getting the value at cell[r][c-1]
            A[r][c] = make_shared<path>(*A[r][c-1]);

            //A[r][c].value().add_step(STEP_DIRECTION_EAST); // going to the rightt 
            A[r][c]->add_step(STEP_DIRECTION_EAST);

          }
        }

        else if(from_left == nullptr && from_above != nullptr)
        {
          //A[r][c] = from_above;

          // if(from_above != nullptr)
          // {
          //  //A[r][c].value().add_step(STEP_DIRECTION_SOUTH); // add this cell value add step
          //  A[r][c] = make_shared<path>(*from_above);
          //  A[r][c]->add_step(STEP_DIRECTION_SOUTH);
          // }
          if(r > 0 && A[r-1][c] != nullptr)
          {
            A[r][c] = make_shared<path>(*from_above);
            A[r][c]->add_step(STEP_DIRECTION_SOUTH);
          }
        }
        

        // else
        // {

        //   //if(from_left.value().total_cranes() > from_above.value().total_cranes()) 
        //    if(from_left->total_cranes() > from_above->total_cranes())
        //    {
        //     //A[r][c] = from_left
        //     A[r][c] = from_left;
        //     //A[r][c].value().add_step(STEP_DIRECTION_EAST);
        //     A[r][c]->add_step(STEP_DIRECTION_EAST);

        //    } 

        //    else
        //    {
        //     //A[r][c] = from_above
        //     A[r][c] = from_above;
        //     //A[r][c].value().add_step(STEP_DIRECTION_SOUTH);
        //     A[r][c]->add_step(STEP_DIRECTION_SOUTH);
        //    }

        // }


        else if(from_left != nullptr && from_above != nullptr)
        {
            if(from_left->total_cranes() > from_above->total_cranes())
            {
                A[r][c] = make_shared<path>(*from_left);
                A[r][c]->add_step(STEP_DIRECTION_EAST);
            }
            else
            {
                A[r][c] = make_shared<path>(*from_above);
                A[r][c]->add_step(STEP_DIRECTION_SOUTH);
            }
        }

        //if (best == nullptr && A[r][c].has_value())
        if (best == nullptr  && A[r][c] != nullptr)
        {
          //best = &A[r][c].value();
          best = A[r][c].get();
        }
        // if (A[r][c].has_value() && A[r][c].total_cranes() > best -> total_cranes())
        if (A[r][c] != nullptr && A[r][c]->total_cranes() > best -> total_cranes())
        { // comparing the new path with the previous path
          
          //best = &A[r][c].value(); // dereferrence value of the cell and assign it to best
          best = A[r][c].get();
        }

        

       //assert(best->has_value());
        //  //  std::cout << "total cranes" << (**best).total_cranes() << std::endl;

       //path best(setting); // setting is the instance of the grid
      }



    }


    // if (best == nullptr) 
    // {
    //   throw runtime_error("No valid path found");
    // }
    return *best; // returning best nullptr
  }
}
