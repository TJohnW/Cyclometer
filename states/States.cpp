//
// Created by Tristan Whitcher on 3/10/16.
//

#include "States.h"

State* States::OPERATING = new Operating("Operating");
State* States::UNIT_SET = new UnitSet("UnitSet");
State* States::TIRE_SET = new TireSet("TireSet");