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

#include "../../Empirical/evo/World.h"
#include "../../Empirical/evo/PopulationManager.h"
#include "../../Empirical/evo/FitnessManager.h"

TEST_CASE("Test QuorumOrg construction", "[unit]")
{
  emp::Random dice;

  // test parametarized constructor
  QuorumOrganism coop(0, 1.0, true, 10, 0.8);

  REQUIRE(coop.GetSignalRadius() == 10);
  REQUIRE(coop.GetQuorumThreshold() == 0.8);
  REQUIRE(coop.GetCooperationProbability() == 1.0);
  REQUIRE(coop.HasCooperativeMachinery() == true);

  coop.SetRandom(&dice);
  REQUIRE(coop.GetRandom() == &dice);

  // test copy constructor
  QuorumOrganism copy(coop);
  REQUIRE(copy.GetSignalRadius() == 10);
  REQUIRE(copy.GetQuorumThreshold() == 0.8);
  REQUIRE(copy.GetCooperationProbability() == 1.0);
  REQUIRE(copy.HasCooperativeMachinery() == true);


}

TEST_CASE("Test QuorumOrg emp::evo::world construct", "[functional]")
{
  emp::Random random;
  emp::evo::World<QuorumOrganism, emp::evo::FitCacheOff> pop(random, "TestWorld");

  QuorumOrganism coop(0, 1.0, true, 10, 0.8);

  // fill the world with some initial orgs....
  const uint32_t numTestOrgs = 10;
  for (uint32_t i = 0; i < numTestOrgs; i++) {
    QuorumOrganism nextOrg(coop);
    pop.Insert(nextOrg);
  }

  // precice typespec required 'cuz otherwise SetDefaultMutFun complains about the
  // TEST_CASE_[number]::std::function blah blah
  std::function<bool(QuorumOrganism *, emp::Random&)> mutFun = [](QuorumOrganism * org,
                                                                  emp::Random& random) {
    return org->Mutate(random);
  };


  pop.SetDefaultMutateFun(mutFun);

  // now attempt to run the world
  for (uint32_t ud = 0; ud < 100; ud++) {
    // keep best individual
    
  }
}
