/**************************************************************************

    This is the component code. This file contains the child class where
    custom functionality can be added to the component. Custom
    functionality to the base class can be extended here. Access to
    the ports can also be done from this class

**************************************************************************/

#include "runningAve.h"
#include <queue>

PREPARE_LOGGING(runningAve_i)

runningAve_i::runningAve_i(const char *uuid, const char *label) :
    runningAve_base(uuid, label)
{
    // Avoid placing constructor code here. Instead, use the "constructor" function.

}

runningAve_i::~runningAve_i()
{
}

void runningAve_i::constructor()
{
    /***********************************************************************************
     This is the RH constructor. All properties are properly initialized before this function is called
    ***********************************************************************************/
}

/***********************************************************************************************

    Basic functionality:

        The service function is called by the serviceThread object (of type ProcessThread).
        This call happens immediately after the previous call if the return value for
        the previous call was NORMAL.
        If the return value for the previous call was NOOP, then the serviceThread waits
        an amount of time defined in the serviceThread's constructor.

    SRI:
        To create a StreamSRI object, use the following code:
                std::string stream_id = "testStream";
                BULKIO::StreamSRI sri = bulkio::sri::create(stream_id);

	Time:
	    To create a PrecisionUTCTime object, use the following code:
                BULKIO::PrecisionUTCTime tstamp = bulkio::time::utils::now();


    Ports:

        Data is passed to the serviceFunction through the getPacket call (BULKIO only).
        The dataTransfer class is a port-specific class, so each port implementing the
        BULKIO interface will have its own type-specific dataTransfer.

        The argument to the getPacket function is a floating point number that specifies
        the time to wait in seconds. A zero value is non-blocking. A negative value
        is blocking.  Constants have been defined for these values, bulkio::Const::BLOCKING and
        bulkio::Const::NON_BLOCKING.

        Each received dataTransfer is owned by serviceFunction and *MUST* be
        explicitly deallocated.

        To send data using a BULKIO interface, a convenience interface has been added
        that takes a std::vector as the data input

        NOTE: If you have a BULKIO dataSDDS or dataVITA49  port, you must manually call
              "port->updateStats()" to update the port statistics when appropriate.

        Example:
            // this example assumes that the component has two ports:
            //  A provides (input) port of type bulkio::InShortPort called short_in
            //  A uses (output) port of type bulkio::OutFloatPort called float_out
            // The mapping between the port and the class is found
            // in the component base class header file

            bulkio::InShortPort::dataTransfer *tmp = short_in->getPacket(bulkio::Const::BLOCKING);
            if (not tmp) { // No data is available
                return NOOP;
            }

            std::vector<float> outputData;
            outputData.resize(tmp->dataBuffer.size());
            for (unsigned int i=0; i<tmp->dataBuffer.size(); i++) {
                outputData[i] = (float)tmp->dataBuffer[i];
            }

            // NOTE: You must make at least one valid pushSRI call
            if (tmp->sriChanged) {
                float_out->pushSRI(tmp->SRI);
            }
            float_out->pushPacket(outputData, tmp->T, tmp->EOS, tmp->streamID);

            delete tmp; // IMPORTANT: MUST RELEASE THE RECEIVED DATA BLOCK
            return NORMAL;

        If working with complex data (i.e., the "mode" on the SRI is set to
        true), the std::vector passed from/to BulkIO can be typecast to/from
        std::vector< std::complex<dataType> >.  For example, for short data:

            bulkio::InShortPort::dataTransfer *tmp = myInput->getPacket(bulkio::Const::BLOCKING);
            std::vector<std::complex<short> >* intermediate = (std::vector<std::complex<short> >*) &(tmp->dataBuffer);
            // do work here
            std::vector<short>* output = (std::vector<short>*) intermediate;
            myOutput->pushPacket(*output, tmp->T, tmp->EOS, tmp->streamID);

        Interactions with non-BULKIO ports are left up to the component developer's discretion

    Messages:

        To receive a message, you need (1) an input port of type MessageEvent, (2) a message prototype described
        as a structure property of kind message, (3) a callback to service the message, and (4) to register the callback
        with the input port.

        Assuming a property of type message is declared called "my_msg", an input port called "msg_input" is declared of
        type MessageEvent, create the following code:

        void runningAve_i::my_message_callback(const std::string& id, const my_msg_struct &msg){
        }

        Register the message callback onto the input port with the following form:
        this->msg_input->registerMessage("my_msg", this, &runningAve_i::my_message_callback);

        To send a message, you need to (1) create a message structure, (2) a message prototype described
        as a structure property of kind message, and (3) send the message over the port.

        Assuming a property of type message is declared called "my_msg", an output port called "msg_output" is declared of
        type MessageEvent, create the following code:

        ::my_msg_struct msg_out;
        this->msg_output->sendMessage(msg_out);

    Properties:

        Properties are accessed directly as member variables. For example, if the
        property name is "baudRate", it may be accessed within member functions as
        "baudRate". Unnamed properties are given the property id as its name.
        Property types are mapped to the nearest C++ type, (e.g. "string" becomes
        "std::string"). All generated properties are declared in the base class
        (runningAve_base).

        Simple sequence properties are mapped to "std::vector" of the simple type.
        Struct properties, if used, are mapped to C++ structs defined in the
        generated file "struct_props.h". Field names are taken from the name in
        the properties file; if no name is given, a generated name of the form
        "field_n" is used, where "n" is the ordinal number of the field.

        Example:
            // This example makes use of the following Properties:
            //  - A float value called scaleValue
            //  - A boolean called scaleInput

            if (scaleInput) {
                dataOut[i] = dataIn[i] * scaleValue;
            } else {
                dataOut[i] = dataIn[i];
            }

        Callback methods can be associated with a property so that the methods are
        called each time the property value changes.  This is done by calling
        addPropertyListener(<property>, this, &runningAve_i::<callback method>)
        in the constructor.

        The callback method receives two arguments, the old and new values, and
        should return nothing (void). The arguments can be passed by value,
        receiving a copy (preferred for primitive types), or by const reference
        (preferred for strings, structs and vectors).

        Example:
            // This example makes use of the following Properties:
            //  - A float value called scaleValue
            //  - A struct property called status

        //Add to runningAve.cpp
        runningAve_i::runningAve_i(const char *uuid, const char *label) :
            runningAve_base(uuid, label)
        {
            addPropertyListener(scaleValue, this, &runningAve_i::scaleChanged);
            addPropertyListener(status, this, &runningAve_i::statusChanged);
        }

        void runningAve_i::scaleChanged(float oldValue, float newValue)
        {
            LOG_DEBUG(runningAve_i, "scaleValue changed from" << oldValue << " to " << newValue);
        }

        void runningAve_i::statusChanged(const status_struct& oldValue, const status_struct& newValue)
        {
            LOG_DEBUG(runningAve_i, "status changed");
        }

        //Add to runningAve.h
        void scaleChanged(float oldValue, float newValue);
        void statusChanged(const status_struct& oldValue, const status_struct& newValue);


************************************************************************************************/
int runningAve_i::serviceFunction()
{

    bulkio::InFloatPort::dataTransfer *tmp = input->getPacket(bulkio::Const::BLOCKING);

    if (not tmp) { // No data is available
    	return NOOP;
    }
	float THRESHOLD= 0;
	float recentAve=0;
	float runningAve=0;
	float poppedVal=0;
	int recentInpTotal=0;

	std::vector<float>* intermediate = (std::vector<float>*) &(tmp->dataBuffer);

	for (unsigned int i=0; i<tmp->dataBuffer.size()/2-1; i++) {
		recentInpTotal += (*intermediate)[i];//adds allocator to intermediate
	}

	//std::cout<< "a";
	//(*intermediate).size();
	recentAve= recentInpTotal/(*intermediate).size();
    //get average
    //add average to running average
	std::queue<float> aveQueue;
	aveQueue.push(recentAve);
	int size= aveQueue.size();
	if(aveQueue.size() > 99){
		poppedVal= aveQueue.front();
		aveQueue.pop();
		runningAve = (recentAve-poppedVal + (size-1)*runningAve)/(size-1);
	}//alternate cases for full queue?
	else{
		runningAve = (recentAve + (size-1)*runningAve)/(size);
	}
	runningAve_struct message;
	message.ave= runningAve;
	this-> outMess-> sendMessage(message);
	if (runningAve> THRESHOLD){
	    LOG_DEBUG(runningAve_i, message.ave);
		runningAve_struct message;
		message.ave= runningAve;
		this-> outMess-> sendMessage(message);
	}

	delete tmp;
    return NORMAL;
}

