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

  /// Constructor (default)
  QuorumOrganism() {};

  /// Copy constructor
  QuorumOrganism(QuorumOrganism const & other) {
    lineage = other.lineage;
    cooperationProbability = other.cooperationProbability;
    hasCooperativeMachinery = other.hasCooperativeMachinery;
    signalRadius = other.signalRadius;
    quorumThreshold = other.quorumThreshold;
  }

  /** Constructor
   * 
   * \param lin the lineage tag used to identify this organism and its offspring
   * \param coop the probability this organism will cooperate, assesed per tick
   * \param hcm bool if this org has the machinery to cooperate/signal
   * \param rad the radius of the AI signal this organism can produce
   * \param thresh the quorum threshold for this organism
   */
  QuorumOrganism(unsigned int lin, double coop, bool hcm, unsigned int rad, double thresh) {
    lineage = lin;
    cooperationProbability = coop;
    hasCooperativeMachinery = hcm;
    signalRadius = rad;
    quorumThreshold = thresh;
  }

  /// Destructor
  ~QuorumOrganism() {};

  /// Getter for age
  unsigned int GetAge() const { return age; }
  /// Getter for points
  unsigned int GetPoints() const { return points; }
  /// Getter for the chance of cooperation, for this organism
  double get_cooperative_probability() const { return cooperationProbability; }


  // getters and setters for the above
  void IncrementAge() { ++age; }
  void SetLocation(unsigned int newLocation) { loc = newLocation; }
  unsigned int GetLoc() const { return loc; }

  // functions to configure random
  void SetRandom(emp::Random * ptr) { random = ptr; }
  emp::Random * GetRandom() const { return random; }

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

  // getters for genome properties
  unsigned int GetLineage() const { return lineage; }
  bool HasCooperativeMachinery() const { return hasCooperativeMachinery; }
  double GetCooperationProbability() const { return cooperationProbability; }
  unsigned int GetSignalRadius() const { return signalRadius; }
  double GetQuorumThreshold() const { return quorumThreshold; }

private:

  //
  // Less interesting attributes
  //

  /// pointer to the pseudorandom number generator used by this org
  emp::Random * random = nullptr;

  //
  // state-specific properties
  //

  /// the 'energy-points' this organism has
  unsigned int points = 0;
  /// the age of this organism, since it was born
  unsigned int age = 0;
  /// the location of this organism on the grid
  unsigned int loc = 0;

  
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
  unsigned int signalRadius = 10;
  /// The proportion of local suqares that must be signalling for this org to be at quorum
  double quorumThreshold = 1.0;

  friend bool operator== (QuorumOrganism const & lhs, QuorumOrganism const & rhs);  
};


/// equality operator--necessary for various structurings
bool operator== (QuorumOrganism const & lhs, QuorumOrganism const & rhs) {
  return (lhs.lineage == rhs.lineage &&
          lhs.hasCooperativeMachinery == rhs.hasCooperativeMachinery &&
          lhs.cooperationProbability == rhs.cooperationProbability &&
          lhs.signalRadius == rhs.signalRadius &&
          lhs.quorumThreshold == rhs.quorumThreshold);
}
