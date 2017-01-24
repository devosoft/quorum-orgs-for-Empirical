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

// local includes
#include "QuorumGenome.h"

/**
 * This class represents a quorum-sensing organism
 *
 */
class QuorumOrganism {

public:

  /// Constructor (default)
  QuorumOrganism() = delete;

  /// Copy constructor
  QuorumOrganism(QuorumOrganism const & other) : genome(other.genome){
  }

  /** Constructor
   * 
   * \param lin the lineage tag used to identify this organism and its offspring
   * \param coop the probability this organism will cooperate, assesed per tick
   * \param hcm bool if this org has the machinery to cooperate/signal
   * \param rad the radius of the AI signal this organism can produce
   * \param thresh the quorum threshold for this organism
   */
  QuorumOrganism(unsigned int lin, double coop, bool hcm, unsigned int rad, double thresh) :
    genome(lin, coop, hcm, rad, thresh){
  }

  /// Destructor
  ~QuorumOrganism() {
  };

  /// Getter for age
  unsigned int GetAge() const { return age; }
  /// Getter for points
  unsigned int GetPoints() const { return points; }

  // getters and setters for the above
  void IncrementAge() { ++age; }
  void SetLocation(unsigned int newLocation) { loc = newLocation; }
  unsigned int GetLoc() const { return loc; }

  // functions to configure random
  void SetRandom(emp::Random * ptr) { rand = ptr; }
  emp::Random * GetRandom() const { return rand; }

  /** Reset all state parameters
   * 
   * Used during reproduction, since we don't actually produce a single new offspring but
   * divide into two 'daughter' orgs, both of which are 'new'
   */
  void reset() {
    points = 0;
    age = 0;
    loc = 0;
  }

  /** Mutate function
   * 
   * Calls the genome's mutate function
   * \param random ref to the random object to use
   * \returns true/false if magic happens
   */
  bool Mutate(emp::Random& random) { return genome.Mutate(random);}


  // passthrough getters/setters
  // ought to be a better way to do this, not sure what it is tho
  unsigned int GetLineage() const { return genome.GetLineage(); }
  bool HasCooperativeMachinery() const { return genome.HasCooperativeMachinery(); }
  double GetCooperationProbability() const { return genome.GetCooperationProbability(); }
  unsigned int GetSignalRadius() const { return genome.GetSignalRadius(); }
  double GetQuorumThreshold() const { return genome.GetQuorumThreshold(); }


private:
  /// our genome
  QuorumGenome genome;

  /// pointer to the pseudorandom number generator used by this org
  emp::Random * rand = nullptr;

  //
  // state-specific properties
  //

  /// the 'energy-points' this organism has
  unsigned int points = 0;
  /// the age of this organism, since it was born
  unsigned int age = 0;
  /// the location of this organism on the grid
  unsigned int loc = 0;

};
