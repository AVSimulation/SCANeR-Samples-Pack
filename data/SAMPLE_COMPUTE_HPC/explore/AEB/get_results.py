#!/usr/bin/python
# -*- coding: utf-8 -*-
import ctypes
import sys
import os
import csv
import time
import xml.etree.ElementTree as ET

import plotly.express as px
import plotly.graph_objects as go
from plotly.subplots import make_subplots

import pandas as pd

import compute_output_parsing as computeOutputParser

TestParameters ={
    "scenario_name" : "",
    "test_parameters" : []
}

TestParameter = {
    "name" : "",
    "value" : 0.0
}

ComputeTestResult = {
    "name": "",
    "date": time.time(),
    "results": []
}

writers = dict()
fieldnames = []

xtc_file = sys.argv[1]
result_folder=sys.argv[2]

tree = ET.parse(xtc_file)
root = tree.getroot()

# Search for scenario basename
sce_basename = root.find('name').text
#print(sce_basename)
paramNames = []

#Read parameters names
for parameter in root.findall("parameter"):
    param = parameter.get('name')
    paramNames.append(param)
    #print(param)
    
tests = dict()
#Read parameters values per scenarios
for testcase in root.findall("./testcases/testcase"):
    testParameters = []
    testParameters = TestParameters.copy()
    id = testcase.get('id')
    testParameters['scenario_name'] = sce_basename+id
    #print(sce_basename+id)
    i = 0
    testParameters["test_parameters"] = []
    for child in testcase:
        #print(child)
        testParam = []
        testParam = TestParameter.copy()
        
        testParam['name'] = paramNames[i]
        testParam['value'] = child.text
        testParameters["test_parameters"].append(testParam)
        i = i+1
    tests[sce_basename+id] = testParameters
#input()
#print("test params: ")
#print(tests)


#Browse result folder

allEntries = os.listdir(result_folder)
allDirs = []
allDirnames = []
for e in allEntries:
    path = os.path.join(result_folder, e)
    if (os.path.isdir(path)):
        allDirs.append(path)
        allDirnames.append(e)
        
testResult = ComputeTestResult.copy()
testResult['name'] = "AEB"
i = 0
for dirent in allDirs:
    res = computeOutputParser.getComputeScenarioResult(dirent, allDirnames[i])
    res['parameters'] = tests[res['scenario_name']]["test_parameters"]

    testResult["results"].append(res)   
    i += 1

#print(testResult)

################### Write CSV

######### Prepare columns
fieldnames.append('scenario')

#Parameters
for param in paramNames:
    fieldnames.append(param)

for crit in testResult["results"][0]['criterion_results']:
    fieldnames.append(crit['name'])

fieldnames.append('result')

#print(fieldnames)

######### Fill the data
with open('results.csv', 'w') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=fieldnames)

    writer.writeheader()
    for res in testResult["results"]:
        row = {}
        row['scenario'] = res['scenario_name']
        for par in res['parameters']:
            #print(par)
            row[par['name']] = par['value']
        for crit in res['criterion_results']:
            crit_res= ""
            if crit['red'] == 1:
                crit_res= 0
            elif crit['yellow'] == 1:
                crit_res= 0.5
            else:
                crit_res= 1
            row[crit['name']] = crit_res
        if res['failed']:
            row['result'] =  0
        else:
            row['result'] =  1
        writer.writerow(row)

lab = {}
for field in fieldnames:
    lab[field]=field
       


df = pd.read_csv("results.csv")

#fig = make_subplots(rows=2, cols=1)

#fig.add_trace(px.parallel_coordinates(df, color="result", labels=lab,
#                             color_continuous_scale=px.colors.sequential.Inferno,
#                             color_continuous_midpoint=0.5), row=1, col=1)

# prepare data for pie chart
df2 = df.value_counts('result').to_frame().reset_index()
df2.columns = ['results', 'counts']

fig = px.pie(df2, values='counts', names='results', title='test results')

#fig.show()

