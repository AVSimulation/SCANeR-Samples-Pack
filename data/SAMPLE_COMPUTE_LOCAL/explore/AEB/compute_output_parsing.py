import time
import json
import os
import csv

ComputeCriterionResult = {
    "name": "",
    "green": 0,
    "yellow": 0,
    "red": 0
}

ComputeScenarioResult ={
    "scenario_name": "",
    "parameters": [],
    "step_done": 0,
    "simulated_duration": 0,
    "real_duration": 0,
    "average_frequency": 0,
    "real_time_ratio": 0,
    "failed": False,
    "criterion_results": []
}

ComputeTestResult = {
    "name": "",
    "date": time.time(),
    "results": []
}

def printComputeTestResultObj(testResult):
    """Debug function that prints the content of a ComputeTestResult object"""
    print ("TestPlan result for " + testResult['name'])
    print ("Date: " + str(testResult['date']))
    for scenario in testResult['results']:
        print("=== " + scenario['scenario_name'] + "===")
        print("step done: "+ str(scenario['step_done']))
        print("simulation duration: "+ str(scenario['simulated_duration']))
        print("real duration: "+str(scenario['real_duration']))
        print("average frequency: "+str(scenario["average_frequency"]))
        print("real time duration: "+str(scenario["real_time_ratio"]))
        print("failed: "+str(scenario["failed"]))
        for criterion in scenario["criterion_results"]:
            print("    +++ criterion +++    ")
            print("    name: " + criterion['name'])
            print("    green: " + str(criterion['green']))
            print("    yellow: " + str(criterion["yellow"]))
            print("    red: " + str(criterion["red"]))
    return 0

def hasScenarioFailed(scenarioResult):
    """Determines if a scenario has failed by examining its criterion results. Returns true if the scenario has failed"""
    for criterion in scenarioResult["criterion_results"]:
        if (criterion["red"] > 0):
            return True
    return False

def parseCriterionResults(scenarioResult, ScenarioOutDirFullPath):
    """Parses the criterion results of a scenario by using the scenario output folder as param and appends data into a ComputeScenarioResult object"""
    with open(os.path.join(ScenarioOutDirFullPath, "criterionResults.csv"), 'r') as file:
        reader = csv.reader(file, delimiter=';')
        criterionResults = []
        i = 0
        for row in reader:
            criterion = ComputeCriterionResult.copy()
            if (i != 0 and len(row) > 0 ): #Skip the header row
                criterion['name'] =    row[0]
                criterion['green'] =   int(row[1])
                criterion['yellow'] =  int(row[2])
                criterion['red'] =     int(row[3])
                criterionResults.append(criterion)
            i += 1
        scenarioResult["criterion_results"] = criterionResults
    file.close()
    return scenarioResult

def parseOfflineScheduler(scenarioResult, ScenarioOutDirFullPath):
    """Parses the offlineScheduler infos of a scenario by using the scenario output folder as param and appends data into a ComputeScenarioResult object"""
    with open(os.path.join(ScenarioOutDirFullPath, "offlineSchedulerOutputOverall.csv"), 'r') as file:
        reader = csv.reader(file, delimiter=';')
        #print("Read : " + os.path.join(ScenarioOutDirFullPath, "offlineSchedulerOutputOverall.csv"))
        i = 0
        for row in reader:
            #print(row)
            if (i != 0 and len(row) > 0): #Skip the header row
                scenarioResult['step_done'] =          int(row[0])
                scenarioResult['simulated_duration'] = float(row[1])
                scenarioResult['real_duration'] =      float(row[2])
                scenarioResult['average_frequency'] =  float(row[3])
                scenarioResult['real_time_ratio'] =    float(row[4])
            i += 1
    file.close()
    return scenarioResult

def getComputeScenarioResult(ScenarioOutDirFullPath, ScenarioName):
    """crates a ComputeScenarioResult from a scenario output directory"""
    scenarioResult = ComputeScenarioResult.copy()
    scenarioResult['scenario_name'] = ScenarioName.split('-')[0]
    scenarioResult = parseOfflineScheduler(scenarioResult, ScenarioOutDirFullPath)
    scenarioResult = parseCriterionResults(scenarioResult, ScenarioOutDirFullPath)
    scenarioResult['failed'] = hasScenarioFailed(scenarioResult)
    return scenarioResult

def getComputeTestResult(testPlanOutdirFullPath, testPlanName):
    """crates a ComputeTestResult object from a test result \'out\' directory and a test result's name. The returned object is a stringified json object."""
    allEntries = os.listdir(testPlanOutdirFullPath)
    allDirs = []
    allDirnames = []
    for e in allEntries:
        path = os.path.join(testPlanOutdirFullPath, e)
        if (os.path.isdir(path)):
            allDirs.append(path)
            allDirnames.append(e)
    testResult = ComputeTestResult.copy()
    testResult['name'] = testPlanName
    i = 0
    for dirent in allDirs:
        testResult["results"].append(getComputeScenarioResult(dirent, allDirnames[i]))
        i += 1
    #printComputeTestResultObj(testResult)
    jsonData = json.dumps(testResult)
    return jsonData
