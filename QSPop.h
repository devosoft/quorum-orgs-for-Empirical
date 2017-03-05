//  This file is part of Empirical, https://github.com/devosoft/Empirical
//  Copyright (C) Michigan State University, 2016.
//  Released under the MIT Software license; see doc/LICENSE
//
//  This file defines built-in population managers for use with emp::evo::World
//
//
//  Developer notes:
//  * Rather than deleting organisms ourright, run all deletions through a ClearCell function
//    so that a common signal system can also be run.

#ifndef QS_POPULATION_MANAGER_H
#define QS_POPULATION_MANAGER_H

#include "../Empirical/evo/PopulationManager.h"

namespace emp{
  namespace evo{


    template <typename ORG>
      class PopulationManager_Mixed_NoOverwrite : public PopulationManager_MixedGrid<ORG> {
    public:
      using PopulationManager_Base<ORG>::pop;
      using PopulationManager_Base<ORG>::random_ptr;

      emp::vector<int> FindCellIDs(const std::function<bool(ORG*)> & filter) {
	emp::vector<int> valid_IDs(0);
	for (int i = 0; i < pop.size(); i++) {
	  if (filter(pop[i])) valid_IDs.push_back(i);
	}
	return valid_IDs;
      }

      emp::vector<int> GetEmptyPopIDs() { return FindCellIDs([](ORG*org){ return org == nullptr; }); }

      int AddOrgBirth(ORG * new_org, int parent_pos) {
	emp::vector<int> empty_spots = GetEmptyPopIDs();
	if(empty_spots.size()>0){
	  const int pos = empty_spots[random_ptr->GetInt(empty_spots.size())];
	  emp_assert(!pop[pos], "Empty cell not actually empty", pos);
	  pop[pos] = new_org;
	  return pos;

	} else{
	  delete new_org;
	  return -1;
	}
      }

    };

    template <typename ORG>
      class PopulationManager_Grid_NoOverwrite : public PopulationManager_Grid<ORG> {

    public:
      using PopulationManager_Base<ORG>::pop;
      using PopulationManager_Base<ORG>::random_ptr;
      using PopulationManager_Grid<ORG>::ToX;
      using PopulationManager_Grid<ORG>::ToY;
      using PopulationManager_Grid<ORG>::ToID;

      using PopulationManager_Grid<ORG>::width;
      using PopulationManager_Grid<ORG>::height;

      std::set<int> GetNeighborIDs (int org_id){
	std::set<int> neighbor_ids;
	int org_x, org_y;
	org_x = ToX(org_id);
	org_y = ToY(org_id);

	for(int i = -1; i < 2; i++) {
	  for(int j = -1; j < 2; j++) {
	    if(i==0 && j ==0) continue;
	    neighbor_ids.insert(ToID((org_x + i + width) % width, 
				      (org_y + j + height) % height));
	  }
	}

	return neighbor_ids;
      }

      int AddOrgBirth(ORG * new_org, int parent_pos){
	std::set<int> neighbors = GetNeighborIDs(parent_pos);
	emp::vector<int> empty_neighbors;
	for (auto n : neighbors){
	  if(!pop[n]) empty_neighbors.push_back(n);
	}
	
	if(empty_neighbors.size()>0){
	  int pos = empty_neighbors[random_ptr->GetInt((int) empty_neighbors.size())];
	  emp_assert(!pop[pos], "Empty cell not empty!", pos);
	  pop[pos] = new_org;
	  return pos;
	} else{
	  delete new_org;
	  return -1;
	}
      }

    };

    template <typename ORG>
      class PopulationManager_Pools_NoOverwrite : public PopulationManager_GridPools<ORG> {
    public:
      using PopulationManager_Base<ORG>::pop;
      using PopulationManager_Base<ORG>::random_ptr;
      using PopulationManager_Base<ORG>::GetSize;

      using PopulationManager_GridPools<ORG>::ToX;
      using PopulationManager_GridPools<ORG>::ToY;
      using PopulationManager_GridPools<ORG>::ToID;
      using PopulationManager_GridPools<ORG>::pool_end;




      int AddOrgBirth(ORG * new_org, int parent_pos) {
	//Even though we're inheriting from Grid Pools, we aren't going to bother with neighborhood reproduction inside pool since we are trying to simulate 96-well plates which are mixed within the plate
	int InsertPool = 0;
	int range_l, range_u;
	emp::vector<int> empty;

	for(int i=0; i<pool_end.size(); i++){
	  if(parent_pos < pool_end[i]){InsertPool = i; break;}
	}

	if(InsertPool==0){range_l=0;}
	else{range_l = pool_end[InsertPool-1];}
	range_u = pool_end[InsertPool];

	for(int i=range_l; i<range_u; i++){
	  if(!pop[i]) empty.push_back(i);
	}

	
	if(empty.size()>0){
	  const int pos = empty[random_ptr->GetInt(empty.size())];
	  emp_assert(!pop[pos], "Empty cell not empty!", pos);
	  pop[pos] = new_org;
	  return pos;
	} else{
	  delete new_org;
	  return -1;
	}

      }
    };

  }
}


#endif
