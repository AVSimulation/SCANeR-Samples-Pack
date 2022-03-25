#!/usr/bin/python3
import mice

currentLateralShift = 0.0

def main():
    global currentLateralShift

    LateralShift = mice.variables["Agent_LateralShift"]

    veh = 50
    
    if (currentLateralShift != LateralShift):
        mice.setLaneLateralShift(veh, 1, LateralShift, abs(LateralShift), 1)
        currentLateralShift = LateralShift
    return 0.0
	
	
