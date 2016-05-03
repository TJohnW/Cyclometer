//
// Created by Tristan Whitcher on 3/10/16.
//

#include "States.h"
#include "AutoMode.h"
#include "ManualMode.h"
#include "UnitSet.h"
#include "TireSet.h"

State* States::AUTO_MODE = new AutoMode("AutoMode");
State* States::MANUAL_MODE = new ManualMode("ManualMode");
State* States::UNIT_SET = new UnitSet("UnitSet");
State* States::TIRE_SET = new TireSet("TireSet");