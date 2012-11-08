#ifndef FQ_STRATEGY_STRATEGY_H
#define FQ_STRATEGY_STRATEGY_H

#include <memory>
#include <string>
#include <set>
#include <vector>

#include <memory>

#include <freequant/FreeQuantPlatform.h>
#include <freequant/marketdata/Bar.h>
#include <freequant/marketdata/Tick.h>
#include <freequant/marketdata/Quote.h>
#include <freequant/utils/DateTime.h>
#include <freequant/strategy/BaseStrategy.h>
#include <freequant/strategy/Task.h>
#include <freequant/strategy/Order.h>
#include <freequant/experiment/Indicator.h>
#include <freequant/experiment/TimeSeries.h>

namespace FreeQuant {

class Account;
class MarketDataProvider;
class TradeProvider;
class Indicator;
class Portfolio;
class Trade;
class OrderBook;
class Position;
class Instrument;

/*!
 *  \class Strategy
 *  \brief dddddddddd
 *
 *  Detailed description starts here.
 */
class Strategy : public BaseStrategy {
public:
    typedef std::shared_ptr<FreeQuant::Exp::Indicator> IndicatorPtr;
    typedef std::vector<IndicatorPtr> Indicators;

    typedef std::shared_ptr<Task> TaskPtr;
    typedef std::vector<TaskPtr> Tasks;

    typedef std::shared_ptr<FreeQuant::Order> OrderPtr;
    typedef std::vector<OrderPtr> Orders;

    typedef std::shared_ptr<FreeQuant::Instrument> InstrumentPtr;
    typedef std::vector<InstrumentPtr> Instruments;

    typedef FreeQuant::MarketDataProvider MarketDataProvider;
    typedef FreeQuant::TradeProvider TradeProvider;

//    typedef FreeQuant::Exp::TimeSeries<Bar> BarSeries;
    typedef FreeQuant::Exp::TimeSeries<Tick> TickSeries;
    typedef FreeQuant::Exp::TimeSeries<Trade> TradeSeries;

    typedef std::map<std::string, BarSeries> BarSeriesMap;
    typedef std::vector<std::string> Symbols;

    explicit Strategy();
	virtual ~Strategy();

    void onInit() {}
    void onDestroy() {}

    /*!
     *  onStart – called when strategy first starts up, before the first bar
     */
    void onStart() {}

    /*!
     *  onStop – called when the strategy shuts down, after the last bar
     */
    void onStop() {}

    void init();
    void start();
    void stop();

    /*!
     * A pure virtual member.
     * \see testMe()
     * \param c1 the first argument.
     * \param c2 the second argument.
     */

    virtual void onProviderConnected(const std::string& provider) {}
    virtual void onProviderDisconnected(const std::string& provider) {}
    virtual void onProviderError(const std::string& provider) {}

    virtual void onBarOpen(const FreeQuant::Bar&) {}
    virtual void onBar(const FreeQuant::Bar&) {}
    virtual void onTick(const FreeQuant::Tick&) {}
    virtual void onQuote(const FreeQuant::Quote&) {}
    virtual void onTrade(const FreeQuant::Trade&) {}
    virtual void onTask(const FreeQuant::DateTime&) {}
    virtual void onOrderCreated(const Order&) {}
    virtual void onOrderFilled(const Order&) {}
    virtual void onOrderPartiallyFilled(const Order&) {}
    virtual void onOrderCancelled(const Order&) {}
    virtual void onOrderExpired(const Order&) {}
    virtual void onOrderRejected(const Order&) {}
    virtual void onOrderReplaced(const Order&) {}

    /*!
     *  OnPositionOpened - fired whenever a new position is established as a result of
     *  a completed trade.
     */
    virtual void onPositionOpened(const Position& position) {}
    virtual void OnPositionChanged(const Position& position) {}
    virtual void onPositionClosed(const Position& position) {}

    /*!
     * \brief onPositionValueChanged - fired whenever a new incoming trade price changes
     *                                 the value of a position.
     * \param position
     */
    virtual void onPositionValueChanged(const Position& position) {}

    void addIndicator(FreeQuant::Indicator *indicator);
    void addIndicator(IndicatorPtr indicator);
    void addInstrument(const Instrument& instrument) {}

    FreeQuant::Task::TaskId addTask(std::shared_ptr<FreeQuant::Task> task);
    void removeTask(FreeQuant::Task::TaskId taskId);

    void addSymbols(const Symbols& symbols);
    void removeSymbols(const Symbols& symbols);
    const Symbols& symbols() const;

    void chooseTradeProvider(std::string name) {}
    void chooseMarketProvider(std::string name) {}

    void setTradeProvider(FreeQuant::TradeProvider *provider);
    void setTradeProvider(std::shared_ptr<FreeQuant::TradeProvider> provider);
    void setMarketDataProvider(FreeQuant::MarketDataProvider *provider);
    void setMarketDataProvider(std::shared_ptr<FreeQuant::MarketDataProvider> provider);

    const Instruments& instruments() const { return _instruments; }
    const Orders& orders() const { return _orders; }
    const Orders& orders(FreeQuant::Order::Status status) const { return _orders; }
    const Orders& orders(std::string symbol) const { return _orders; }

    bool hasPosition() const { return false; }
    MarketDataProvider *marketDataProvider() const { return _mdProvider; }
    TradeProvider *tradeProvider() const { return m_tradeProvider; }
    OrderBook *orderBook() const { return 0; }

    BarSeries *createBarSeries();
//    const BarSeries& barSeries() const { return _barSeries; }
    const BarSeries& barSeries(const std::string symbol) {
        return _barSeriesMap[symbol];
    }


    long position(std::string symbol) { return 0; }
    void clearPositions();
    void clearPosition(std::string symbol);
    void cancelOrders();

    Account *account() { return nullptr; }
private:
    void onStep();
    virtual void onMarketDataProviderConnected();
    void onMarketDataProviderBar(const FreeQuant::Bar&);
    void handleBar(const FreeQuant::Bar&);
    std::vector<FreeQuant::Indicator *> m_indictors;

    Indicators _indicators;
    Instruments _instruments;
    Orders _orders;
    Tasks _tasks;

//    TimeSeriesVector _tsVector;
//    TimeSeriesMap _tsMap;
    MarketDataProvider *_mdProvider;
    TradeProvider *m_tradeProvider;

    std::shared_ptr<TradeProvider> _tradeProvider;
    class MdProviderCallback;
    class TradeProviderCallback;
    friend class MdProviderCallback;
    friend class TradeProviderCallback;
    MdProviderCallback *_mdCallback;
    TradeProviderCallback *_tradeCallback;
    std::set<std::string> _symbols;

    TickSeries _tickSeries;
    BarSeries _barSeries;
    BarSeriesMap _barSeriesMap;
};

} // FQ_STRATEGY_STRATEGY_H

#endif /* FQ_STRATEGY_STRATEGY_H */
