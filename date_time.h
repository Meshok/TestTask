#ifndef DATE_TIME_H
#define DATE_TIME_H

#include "date.h"

namespace solution {
struct DateTime : public Date {
    int32_t hour;
    int32_t minute;
    int32_t second;
};
}

#endif  // DATE_TIME_H
