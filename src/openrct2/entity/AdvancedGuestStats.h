#pragma once

#include "../ride/Ride.h"
#include "../ride/RideRatings.h"
#include "../core/FixedPoint.hpp"
//#include "../core/DataSerialiser.h"

#include <iostream>
#include <vector>
#include <mutex>
#include <deque>
#include <memory>

using namespace OpenRCT2;

struct GuestRideRating
{
public:
    RideId ID;
    uint8_t Rating;
    RideRating_t MeasuredRideValue;

//public:
    GuestRideRating(RideId id, uint8_t rating, RideRating_t measuredRideValue)
        : ID(id)
        , Rating(rating)
        , MeasuredRideValue (measuredRideValue){}
    void SetValues(RideId id, uint8_t rating)
    {
        this->ID = id;
        this->Rating = rating;
    }
    uint8_t getRating()
    {
        return this->Rating;
    }
    RideId getRideID()
    {
        return this->ID;
    }
    Ride* getRide()
    {
        return GetRide(this->ID);
    }
    RideRating_t getMeasuredValue()
    {
        return this->MeasuredRideValue;
    }
    explicit operator RideId() const
    {
        return ID;
    }
    explicit operator uint8_t() const
    {
        return Rating;
    }
    
    //void Serialise(DataSerialiser& stream);
    
};

/* Possible Traits
Traits:
- Stingy
- Superfan
-

*/

class AdvancedGuestStats
{
public:
    mutable std::mutex pathfindingQueueMutex;

    AdvancedGuestStats();
    void InsertRideIntensityRating(RideId id, uint8_t rating, RideRating_t rideRating);
    float GetMedianIntensityRating(RideId id, RideRating_t currentIntensity);
    std::string GetMedianIntensityRatingString(RideId id, RideRating_t currentIntensity);
    uint8_t GetQueueTimeThreshold();
    uint8_t GetQueueTimeCancelChance();
    std::vector<GuestRideRating> FindRidesByRideId(std::vector<GuestRideRating>& ratings, RideId targetId);
    std::vector<GuestRideRating> FindRideIntensityRatingsByRideId(RideId targetId);
    void DeleteOldIntensityRatings(RideId id, RideRating_t currentIntensity);
    //void Serialise(DataSerialiser& stream);
   

//private:
    std::vector<GuestRideRating> RideIntensitySatisfaction{};
    std::deque<TileCoordsXYZ> PathfindingQueue;
    std::vector<std::pair<Ride*, const RideStation*>> proxyRides;

};
