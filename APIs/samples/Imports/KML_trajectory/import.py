import os
import sys
import argparse

import xml.etree.ElementTree as ET

from pyproj import CRS,Transformer


 
def writeCSVLine(f, strLine, col):
    for icol in col[:-1]:
        strLine += str(icol)+";"
    strLine+=str(col[-1])+"\n"
    f.write( strLine )
        
def createCSV(fileName, coords, transformer):
    offsetX = 292085.21
    offsetY = 5629458.42

    f = open(fileName+ ".csv", "w")
    col = [0.0]*36
    strLine=""
    writeCSVLine(f, strLine, col) 
    strLine=""
    writeCSVLine(f, strLine, col) 

    
    for geo in coords:
        X,Y=transformer.transform(geo[0],geo[1])
        x=X-offsetX
        y=Y-offsetY
        yaw = 0.017453*float(geo[2])
        
        col = [0.0]*2
        col[0]=x
        col[1]=y
        
        strLine=""
        writeCSVLine(f, strLine, col) 
        
    f.close()

def readKML(root):
    coordinates = root.findall("*//{http://www.opengis.net/kml/2.2}coordinates")
    #print (coordinates[0].text)
    coordList = []
    for coordtext in coordinates[0].text.split(" "):
        coord = []
        ok = True
        for textval in coordtext.split(","):
            #print (textval)
            try:
                coord.append(float(textval))
            except:
                try:
                    coord.append(float(textval.replace('.',',')))
                except:
                  ok = False
        if (ok):
            coordList.append(coord)
    #print(coordList)
    return coordList

def main():

    #Read args
    parser = argparse.ArgumentParser()
    parser.add_argument("inputFile")
    args = parser.parse_args()
    print(args.inputFile)



    #Projections
    crsTo = CRS.from_epsg(32632)
    crsFrom = CRS.from_proj4("+proj=latlon")
    transformer = Transformer.from_crs(crsFrom,crsTo)
    
    #outProj=Proj(init='epsg:4326')
    offsetX = 292085.21
    offsetY = 5629458.42

    tree = ET.parse(args.inputFile)
    root = tree.getroot()
    
    coords = readKML(root)

    #Creation du fichier GPX
    #createGPX("hostvehicle", root, ".//hostvehicle/traj/geo")
    createCSV("hostvehicle", coords , transformer)
     
if __name__ == '__main__':
    sys.exit(main())


