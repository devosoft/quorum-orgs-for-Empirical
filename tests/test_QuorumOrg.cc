/** This file contains tests for QuorumOrg.h in the module/ directory.
 * 
 * This file is a part of the QuorumOrgsForEmpirical module 
 * (https://github.com/devosoft/quorum-orgs-for-Empirical)
 * and is licenced under the MIT Software License
 *
 * Copyright (c) 2017 Michigan State University
 *
 * See doc/LICENSE for details.
 */

#define CATCH_CONFIG_MAIN
#include "../third-party/Catch/single_include/catch.hpp"
#include "../module/QuorumOrg.h"
#include "../../Empirical/tools/Random.h"

TEST_CASE("Test QuorumOrg construction", "[unit]")
{
  // test default constructor
  QuorumOrganism org;
  emp::Random dice;

  // make sure getters/setters/initialization work
  REQUIRE(org.GetPoints() == 0);
  REQUIRE(org.GetAge() == 0);
  REQUIRE(org.GetPoints() == 0);
  REQUIRE(org.GetRandom() == nullptr);
  
  org.SetRandom(&dice);
  REQUIRE(org.GetRandom() == &dice);

  
  // test parametarized constructor
  QuorumOrganism coop(0, 1.0, true, 10, 0.8);

  REQUIRE(coop.GetSignalRadius() == 10);
  REQUIRE(coop.GetQuorumThreshold() == 0.8);
  REQUIRE(coop.GetCooperationProbability() == 1.0);
  REQUIRE(coop.HasCooperativeMachinery() == true);

  // test copy constructor
  QuorumOrganism copy(coop);
  REQUIRE(copy.GetSignalRadius() == 10);
  REQUIRE(copy.GetQuorumThreshold() == 0.8);
  REQUIRE(copy.GetCooperationProbability() == 1.0);
  REQUIRE(copy.HasCooperativeMachinery() == true);


}
