// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
            ( 0, uint256("0x5b08cbe328392be8151f5deec2dc92e7609dcbd20e0dac335904ccf538df68e8")) // Genesis Block
            ( 2, uint256("0x25467f804155a90e5578e3d2bfc3341389bb79cbf7292f74b109c47fcf86797d")) // Premine
            ( 777, uint256("0x07e188e6f2f4397a873f8c1e9a6903eba7457c44f5c957c1b006aa568ab39513")) 
            // Block 2913 contains the transaction that DESTROYED the 100,000 POK Premine from Block 2.
            // The entire premine was sent to the destroyer address: 2BuCidDstqL7xDforAjhFxcuStL1V5jzVRa
            ( 2913, uint256("0x702fb5ca8bd664e61fe2d39a99c6a4730d48cfa29cb3e8d4bda2f9612ca925b6"))
            ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
