#!/usr/bin/python3
import mice

def main():
    if(mice.getDistanceToNextSignal(0, 17) < 10):
        traffic_light_id=mice.getNextSignalId(0, 17)
        if(mice.getTrafficLightState(traffic_light_id, 0) == 0):
            mice.setTrafficLight(traffic_light_id, GREEN, ALL, ALL_VEHICLES, OFF)
        #setTrafficLight(ID, COLOR, DIRECTION, VEHICLES, STATE)
        #More information on: Scripting help
        #mice.doDebug("TL forced to green")
    return 0.0
