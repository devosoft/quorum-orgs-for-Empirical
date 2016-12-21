/*  This file is part of Empirical, https://github.com/devosoft/Empirical
 *  Copyright (C) Michigan State University, 2016.
 *  Released under the MIT Software License; see doc/LICENSE
 */

 /** \file QuorumOrg.h
  *  \author Jake Fenton
  *
  * This file contains the specification and implementation for the
  * quorum-sensing digital agents we will use in this system.
  *
  * This module is a re-write of a pre-existing system
  */

#pragma once

// Empirical library includes
// May need to be modified to use a less brittle of
// a method of locating the Empirical library.
#include "../../Empirical/tools/Random.h"
#include "../../Empirical/config/config.h"

/**
 * This class represents a quorum-sensing organism
 *
 */
class QuorumOrganism {

public:

  /// Getter for age
  unsigned int get_age() const { return age; }
  /// Getter for points
  unsigned int get_points() const { return points; }
  /// Getter for the chance of cooperation, for this organism
  double get_cooperative_probability() const { return cooperationProbability; }

private:

  //
  // Less interesting attributes
  //

  /// class-wide number generator
  static emp::Random * random;


  //
  // state-specific properties
  //

  /// the 'energy-points' this organism has
  unsigned int points = 0;
  /// the age of this organism, since it was born
  unsigned int age = 0;


  //
  // genome properties
  // might be worth putting these in their own class
  //

  /// ID for the lineage of this organism
  unsigned int lineage = 0;
  /// Specifies if this org has the machinery to signal high density and cooperate
  bool hasCooperativeMachinery = false;
  /// The probability this organism has to cooperate
  double cooperationProbability = 0;
  /// The signal radius of this organism, when it produces AI compound
  unsigned int signalRaduis = 10;
  /// The proportion of local suqares that must be signalling for this org to be at quorum
  double quorumThreshold = 1.0;
};
