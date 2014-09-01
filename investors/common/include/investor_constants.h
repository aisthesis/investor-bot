/**
 * Copyright (C) 2014 Marshall Farrier, Robert Rodrigues
 *
 * Distribution and use of this software without prior written permission
 * of the authors is strictly prohibitied and will be prosecuted to
 * the full extent of the law.
 * 
 * investor_constants.h
 *
 * abstract base Investor class
 *
 * Author Marshall Farrier
 * Since 2014-08-28
 */

#ifndef INVESTOR_CONSTANTS_H
#define INVESTOR_CONSTANTS_H

namespace investor {
    constexpr double kSellHoldThreshold = 1.0 / 3.0;
    constexpr double kHoldBuyThreshold = 2.0 / 3.0;
}
#endif
