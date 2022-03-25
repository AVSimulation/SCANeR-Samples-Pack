#!/usr/bin/python3
import mice

def main():
    if(mice.getDistanceToNextSignal(0, 17) < 10):
        traffic_light_id=mice.getNextSignalId(0, 17)
        if(mice.getTrafficLightState(traffic_light_id, 0) == 0):
            mice.setTrafficLight(traffic_light_id, 3, 7, -1, 0)
        #setTrafficLight(ID, COLOR, DIRECTION, VEHICLES, STATE)
        #COLOR: Green=3; Amber=2; Red=1
        #DIRECTION: TRAFFIC_DIRECTION_STRAIGHT_FORWARD=1; TRAFFIC_DIRECTION_LEFT=2; TRAFFIC_DIRECTION_RIGHT=4; TRAFFIC_DIRECTION_ALL=7
        #VEHICLES: All=-1
        #mice.doDebug("TL forced to green")
    return 0.0