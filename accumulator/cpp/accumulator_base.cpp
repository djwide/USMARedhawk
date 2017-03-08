#include "accumulator_base.h"

/*******************************************************************************************

    AUTO-GENERATED CODE. DO NOT MODIFY

    The following class functions are for the base class for the component class. To
    customize any of these functions, do not modify them here. Instead, overload them
    on the child class

******************************************************************************************/

accumulator_base::accumulator_base(const char *uuid, const char *label) :
    Component(uuid, label),
    ThreadedComponent()
{
    loadProperties();

    message_inRA = new MessageConsumerPort("message_inRA");
    addPort("message_inRA", message_inRA);
    message_inC = new MessageConsumerPort("message_inC");
    addPort("message_inC", message_inC);
    message_out = new MessageSupplierPort("message_out");
    addPort("message_out", message_out);
}

accumulator_base::~accumulator_base()
{
    delete message_inRA;
    message_inRA = 0;
    delete message_inC;
    message_inC = 0;
    delete message_out;
    message_out = 0;
}

/*******************************************************************************************
    Framework-level functions
    These functions are generally called by the framework to perform housekeeping.
*******************************************************************************************/
void accumulator_base::start() throw (CORBA::SystemException, CF::Resource::StartError)
{
    Component::start();
    ThreadedComponent::startThread();
}

void accumulator_base::stop() throw (CORBA::SystemException, CF::Resource::StopError)
{
    Component::stop();
    if (!ThreadedComponent::stopThread()) {
        throw CF::Resource::StopError(CF::CF_NOTSET, "Processing thread did not die");
    }
}

void accumulator_base::releaseObject() throw (CORBA::SystemException, CF::LifeCycle::ReleaseError)
{
    // This function clears the component running condition so main shuts down everything
    try {
        stop();
    } catch (CF::Resource::StopError& ex) {
        // TODO - this should probably be logged instead of ignored
    }

    Component::releaseObject();
}

void accumulator_base::loadProperties()
{
    addProperty(localLat,
                "localLat",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(localLong,
                "localLong",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(localComp,
                "localComp",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(localAoa,
                "localAoa",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(NODEID,
                "NODEID",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(result,
                "result",
                "",
                "readwrite",
                "",
                "external",
                "property");

    addProperty(accumMess,
                accumMess_struct(),
                "accumMess",
                "",
                "readwrite",
                "",
                "external",
                "message");

    addProperty(Compass,
                Compass_struct(),
                "Compass",
                "",
                "readwrite",
                "",
                "external",
                "message");

    addProperty(runningAve,
                runningAve_struct(),
                "runningAve",
                "",
                "readwrite",
                "",
                "external",
                "message");

}


