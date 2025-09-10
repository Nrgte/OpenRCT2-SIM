#include "AdvancedGuestStats.h"

#include "../core/DataSerialiser.h"
#include "../ride/Ride.h"
#include "Guest.h"

#include <algorithm>
#include <iostream>

using namespace OpenRCT2;

// Empty constructor with no arguments
AdvancedGuestStats::AdvancedGuestStats()
{
}

void AdvancedGuestStats::InsertRideIntensityRating(RideId id, uint8_t rating, RideRating_t rideRating)
{
    GuestRideRating temp(id, rating, rideRating);
    int test = 1;
    if (this == nullptr)
        test++;
    this->RideIntensitySatisfaction.push_back(temp);
}

float AdvancedGuestStats::GetMedianIntensityRating(RideId id, RideRating_t currentIntensity)
{
    // Delete old intensityRatings in case the ride has changed.
    this->DeleteOldIntensityRatings(id, currentIntensity);

    std::vector<GuestRideRating> matches = FindRideIntensityRatingsByRideId(id);

    size_t n = matches.size();

    if (n == 0)
        return 0;

    std::sort(
        matches.begin(), matches.end(), [](const GuestRideRating& a, const GuestRideRating& b) { return a.Rating < b.Rating; });

    if (n % 2 == 0)
    {
        // Even number of elements
        int mid1 = n / 2 - 1;
        int mid2 = n / 2;
        return roundf((matches[mid1].Rating + matches[mid2].Rating) / 2.0f * 10) / 10;
    }
    else
    {
        // Odd number of elements
        int mid = n / 2;
        return matches[mid].Rating;
    }
    /*
    int totalRideRating = 0;
    for (GuestRideRating& ride : matches)
    {
        totalRideRating += ride.getRating();
    }

    return roundf((float)totalRideRating / matches.size() * 10) / 10;
    */
}

std::string AdvancedGuestStats::GetMedianIntensityRatingString(RideId id, RideRating_t currentIntensity)
{
    float medianIntensity = GetMedianIntensityRating(id, currentIntensity);
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << medianIntensity;
    return ss.str();
}

std::vector<GuestRideRating> AdvancedGuestStats::FindRidesByRideId(std::vector<GuestRideRating>& ratings, RideId targetId)
{
    // Use std::find_if to search for matching RideRating objects
    std::vector<GuestRideRating> matchingRides;
    std::copy_if(ratings.begin(), ratings.end(), std::back_inserter(matchingRides), [targetId](GuestRideRating& rating) {
        return rating.getRideID() == targetId;
    });

    return matchingRides;
}

std::vector<GuestRideRating> AdvancedGuestStats::FindRideIntensityRatingsByRideId(RideId id)
{
    return this->FindRidesByRideId(this->RideIntensitySatisfaction, id);
}

void AdvancedGuestStats::DeleteOldIntensityRatings(RideId id, RideRating_t currentIntensity)
{
    this->RideIntensitySatisfaction.erase(
        std::remove_if(
            this->RideIntensitySatisfaction.begin(), this->RideIntensitySatisfaction.end(),
            [id, currentIntensity](const GuestRideRating& rating) {
                return rating.ID == id && rating.MeasuredRideValue != currentIntensity;
            }),
        this->RideIntensitySatisfaction.end());
}

// Set the default Queue Time Tolerance to 7 minutes.
uint8_t AdvancedGuestStats::GetQueueTimeThreshold()
{
    return 7;
}

// Set the default QueueTimeCancelChance to 25%
uint8_t AdvancedGuestStats::GetQueueTimeCancelChance()
{
    return 0x4000U;
}

/*
void AdvancedGuestStats::Serialise(DataSerialiser& stream)
{
    // stream << RideIntensitySatisfaction;
    stream << testbla;
}

void GuestRideRating::Serialise(DataSerialiser& stream)
{
    stream << ID;
    stream << Rating;
}
*/
