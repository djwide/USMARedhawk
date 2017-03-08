#include <iostream>
#include "ossie/ossieSupport.h"

#include "accumulator.h"
int main(int argc, char* argv[])
{
    accumulator_i* accumulator_servant;
    Component::start_component(accumulator_servant, argc, argv);
    return 0;
}

