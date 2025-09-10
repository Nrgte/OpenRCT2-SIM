/*****************************************************************************
 * Copyright (c) 2014-2025 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../ride/RideTypes.h"
#include "../world/Location.hpp"
#include "../ride/RideManager.hpp"

#include <memory>
#include <deque>

#include <future>

struct Peep;
struct Guest;

namespace OpenRCT2
{
    struct TileElement;
}

namespace OpenRCT2::PathFinding
{
    Direction ChooseDirection(
        const TileCoordsXYZ& loc, const TileCoordsXYZ& goal, Peep& peep, bool ignoreForeignQueues, RideId queueRideIndex);

    int32_t CalculateNextDestination(Guest& peep);

    int32_t GuestPathFindParkEntranceEntering(Peep& peep, uint8_t edges);

    int32_t GuestPathFindPeepSpawn(Peep& peep, uint8_t edges);

    int32_t GuestPathFindParkEntranceLeaving(Guest& peep, uint8_t edges);

    int32_t CalculateHeuristicPathingScoreWrapper(const CoordsXYZ& loc1, const CoordsXYZ& loc2);

    void InitializePathFinding(Guest& peep);

    //std::vector<TileCoordsXYZ> AStarSearch(const TileCoordsXYZ& start, const TileCoordsXYZ& goal);
    //std::vector<TileCoordsXYZ> GetTileNeighbours(const TileCoordsXYZ& coords);
    //uint8_t CalculateNeighbourZ(const TileCoordsXYZ& current, const TileCoordsXYZ& neighbor, const PathElement* element);

}; // namespace OpenRCT2::PathFinding

namespace AdvancedPathfinding
{
    std::deque<TileCoordsXYZ> AStarSearch(
        const TileCoordsXYZ& start, const TileCoordsXYZ& goal, Peep& guest, bool useProxyRides = true);
    std::deque<TileCoordsXYZ> AStarSearch(
        const TileCoordsXYZ& start, const TileCoordsXYZ& target, Peep& peep, bool useProxyRides, Ride* ignoreThisProxyRide);
    std::deque<StationIndex> GetSortedStationQueue(Peep& peep, Ride* ride);
    void CalculatePathfinding(Guest& peep, Ride* ride, TileCoordsXYZ loc, std::promise<TileCoordsXYZ> promise);
};
