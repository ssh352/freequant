#include <freequant/marketdata/ctp/ctpmarketdataprovider.h>

#include "MarketDataProviderFactory.h"

namespace FreeQuant {

MarketDataProvider *MarketDataProviderFactory::createMarketDataProvider(std::string name) {
    MarketDataProvider *provider = 0;
    if (name == "ctp") {
        provider = new FreeQuant::CtpMarketDataProvider();
    } else {
        provider = new FreeQuant::CtpMarketDataProvider();
    }
}

}
