#ifndef ACCUMULATOR_I_IMPL_H
#define ACCUMULATOR_I_IMPL_H

#include "accumulator_base.h"

class accumulator_i : public accumulator_base
{
    ENABLE_LOGGING
    public:
        accumulator_i(const char *uuid, const char *label);
        ~accumulator_i();

        void constructor();
        void messageReceivedC(const std::string &id, const Compass_struct &msg);// added this
        void messageReceivedRA(const std::string &id, const runningAve_struct &msg);// added this
        void sendAccum();
        int serviceFunction();
};

#endif // ACCUMULATOR_I_IMPL_H
