/*
 * order.h
 *
 *  Created on: 2012-7-1
 *      Author: alex
 */

#ifndef FQ_STRATEGY_ORDER_H
#define FQ_STRATEGY_ORDER_H

namespace FreeQuant { namespace Strategy {

class Order {
public:
    enum Type {
        Market,
        Limit,
        Stop,
        StopLimit
    };

    enum OrderSide { Buy , Sell };

    enum OrderStatus {
        PendingNew,
         New,
         PartiallyFilled,
         Filled,
         PendingCancel,
         Cancelled,
         Expired,
         PendingReplace,
         Replaced,
         Rejected
    };
	Order();
	virtual ~Order();

    void cancel();
    void replace();
    void send();

    bool isFilled();
    bool isRejected();
    bool isNew();
    bool isExpired();
    bool isPartiallyFilled();
    bool isCancelled();
    bool isPendingNew();
    bool isPendingReplace();
    double price();
    double qty();
    void side();


};

}} /* namespace FreeQuant */

#endif /* FQ_STRATEGY_ */