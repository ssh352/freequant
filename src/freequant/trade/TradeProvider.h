#ifndef FQ_TRADE_TRADEPROVIDER_H
#define FQ_TRADE_TRADEPROVIDER_H

#include <map>
#include <string>
#include <vector>

namespace FreeQuant {
class Order;
class Instrument;
}

namespace FreeQuant {

class TradeProvider {
public:
    typedef std::map<std::string, std::string> Params;
    class Callback {
        virtual ~Callback() {}
    };

    explicit TradeProvider(FreeQuant::TradeProvider::Callback *callback = 0) {}
    virtual ~TradeProvider() {}
    virtual void connect() = 0;
    virtual void disconnect() = 0;
    virtual bool isConnected() const = 0;
    virtual std::string name() const = 0;

    virtual void logon() = 0;
    virtual void logout() = 0;

    virtual std::vector<std::string> availableExchanges() const = 0;
    virtual std::vector<std::string> availableInstruments() const = 0;

    virtual void sendOrder(FreeQuant::Order& order) = 0;
    virtual void cancelOrder(FreeQuant::Order& order) = 0;
    virtual void replaceOrder(FreeQuant::Order& order) = 0;

    virtual void subscribe(std::vector<std::string> symbols) = 0;
    virtual void unsubscribe(std::vector<std::string> symbols) = 0;

    virtual void updateIntrument(std::string symbol, bool block = false) = 0;
    virtual void updateIntrument(FreeQuant::Instrument& instrument) = 0;
};

}

#endif // FQ_TRADE_TRADEPROVIDER_H