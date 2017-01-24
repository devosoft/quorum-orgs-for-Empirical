/*  This file is part of Empirical, https://github.com/devosoft/Empirical
 *  Copyright (C) Michigan State University, 2016.
 *  Released under the MIT Software License; see doc/LICENSE
 */

/** \file QuorumGenome.h
 *  \author Jacob Fenton
 *
 * This file contains the class implementation for the genome of a quorum organism
 */

#pragma once

#include "../../Empirical/tools/Random.h"

/** Genome class
 *
 * this implements the genome of a co-operative quorum organism
 * and contains functionality to copy and mutate the genome
 */
class QuorumGenome {

public:

   /** Constructor
   * 
   * \param lin the lineage tag used to identify this genome and its offspring
   * \param coop the probability this genome will cooperate, assesed per tick
   * \param hcm bool if this org has the machinery to cooperate/signal
   * \param rad the radius of the AI signal this genome can produce
   * \param thresh the quorum threshold for this genome
   */
  QuorumGenome(unsigned int lin, double coop, bool hcm, unsigned int rad, double thresh) {
    lineage = lin;
    cooperationProbability = coop;
    hasCooperativeMachinery = hcm;
    signalRadius = rad;
    quorumThreshold = thresh;
  }

  /// Copy constructor
  QuorumGenome(QuorumGenome const & other) {
    lineage = other.lineage;
    cooperationProbability = other.cooperationProbability;
    hasCooperativeMachinery = other.hasCooperativeMachinery;
    signalRadius = other.signalRadius;
    quorumThreshold = other.quorumThreshold;
  }
  
  /** Mutate function
   *
   * mutates this genome according to some distribution that I'll decide later
   * TODO: distribute:
   *
   * \param random pointer to the pseudorandom number generator to use
   */
  bool Mutate(emp::Random& random) { return false;}

  // getters and setters
  unsigned int GetLineage() const { return lineage; }
  bool HasCooperativeMachinery() const { return hasCooperativeMachinery; }
  double GetCooperationProbability() const { return cooperationProbability; }
  unsigned int GetSignalRadius() const { return signalRadius; }
  double GetQuorumThreshold() const { return quorumThreshold; }

  

private:
  /// ID for the lineage of this organism
  unsigned int lineage = 0;
  /// specifies if this organism has co-operative machinery
  bool hasCooperativeMachinery = false;
  /// the probability this organism has to cooperate
  double cooperationProbability = 0.0;
  /// the signal radius of the AI compound produced by this organism
  unsigned int signalRadius = 10;
  /// the proportion of local cells that must be signaling for this org to be at quorum
  double quorumThreshold = 1.0;

  friend bool operator== (QuorumGenome const & lhs, QuorumGenome const & rhs);  
};


/// equality operator--necessary for various structurings
bool operator== (QuorumGenome const & lhs, QuorumGenome const & rhs) {
  return (lhs.lineage == rhs.lineage &&
          lhs.hasCooperativeMachinery == rhs.hasCooperativeMachinery &&
          lhs.cooperationProbability == rhs.cooperationProbability &&
          lhs.signalRadius == rhs.signalRadius &&
          lhs.quorumThreshold == rhs.quorumThreshold);
}
