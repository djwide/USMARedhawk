/*
Author:
Cadet David Weidman USMA Class of 2016
321.297.9323
david.j.weidman2.mil@mail.mil
*/
#include "accumulator.h"
#include <stdio.h>
#include <curl/curl.h>


PREPARE_LOGGING(accumulator_i)

accumulator_i::accumulator_i(const char *uuid, const char *label) :
    accumulator_base(uuid, label)
{
    // Avoid placing constructor code here. Instead, use the "constructor" function.
}

accumulator_i::~accumulator_i()
{
}

void accumulator_i::constructor()
{
    /***********************************************************************************
     This is the RH constructor. All properties are properly initialized before this function is called
    ***********************************************************************************/
	message_inRA->registerMessage("runningAve", this, &accumulator_i::messageReceivedRA);
	message_inC->registerMessage("Compass", this, &accumulator_i::messageReceivedC);
	this->NODEID=1; //change per implementation
	this->localAoa=0;
	this->localComp=0;
	this->result="";

	this->localLat=41.234154;
	this->localLong=-73.573175;
}


void accumulator_i::messageReceivedRA(const std::string &id, const runningAve_struct &msg){
	LOG_INFO(accumulator_i, " runningAve received: "<<msg.ave);
	accumMess_struct message;
	message.aveA= msg.ave;
	message.wavelengthA= msg.ave;
	message.aoaA= this->localAoa;
	message.compassA= this->localComp;
	message.locLatA= this->localLat;
	message.locLongA= this->localLong;
	message.nodeID= this->NODEID;
    this-> message_out->sendMessage(message);
}

void accumulator_i::messageReceivedC(const std::string &id, const Compass_struct &msg){
	LOG_INFO(accumulator_i, "compassReceived:  "<< msg.aoa);
	this->localAoa=msg.aoa;
	this->localComp=msg.compass;
}



int accumulator_i::serviceFunction()
{
	LOG_INFO(accumulator_i, this->result);
    return NOOP;

}

