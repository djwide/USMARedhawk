#ifndef ACCUMULATOR_BASE_IMPL_BASE_H
#define ACCUMULATOR_BASE_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Component.h>
#include <ossie/ThreadedComponent.h>

#include <ossie/MessageInterface.h>
#include "struct_props.h"

class accumulator_base : public Component, protected ThreadedComponent
{
    public:
        accumulator_base(const char *uuid, const char *label);
        ~accumulator_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();

    protected:
        // Member variables exposed as properties
        /// Property: localLat
        float localLat;
        /// Property: localLong
        float localLong;
        /// Property: localComp
        float localComp;
        /// Property: localAoa
        float localAoa;
        /// Property: NODEID
        unsigned char NODEID;
        /// Property: result
        std::string result;
        /// Message structure definition for accumMess
        accumMess_struct accumMess;
        /// Message structure definition for Compass
        Compass_struct Compass;
        /// Message structure definition for runningAve
        runningAve_struct runningAve;

        // Ports
        /// Port: message_inRA
        MessageConsumerPort *message_inRA;
        /// Port: message_inC
        MessageConsumerPort *message_inC;
        /// Port: message_out
        MessageSupplierPort *message_out;

    private:
};
#endif // ACCUMULATOR_BASE_IMPL_BASE_H
