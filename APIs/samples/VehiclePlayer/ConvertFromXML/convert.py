import os
import sys

import xml.etree.ElementTree as ET

from pyproj import Proj,Transformer


def createSCANeRMDL(fileName,type):
	#Creation du fichier MDL
	templateFileName = "template/template_"+type+".mdl"
	templateFile = open(templateFileName, "r")
	template= templateFile.read()

	content = template.replace('template_vehicle_name', os.path.basename(fileName))

	f = open(fileName + ".mdl", "w")
	f.write(content)

	templateFile.close()
	f.close()


def createSCANePlayer(fileName):
	#Creation du fichier Player
	templateFileName = "template/template.vhplayer"
	templateFile = open(templateFileName, "r")
	template= templateFile.read()

	content = template.replace('template_vehicle_name', os.path.basename(fileName))

	f = open(fileName + ".vhplayer", "w")
	f.write(content)

	templateFile.close()
	f.close()



def createGPX(fileName, root, startNode):
	#Creation du fichier GPX
	f = open(fileName + ".gpx", "w")

	f.write( "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
	f.write( "<gpx version=\"1.1\" creator=\"GpxTraceNet6.2\"\n")
	f.write( "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xmlns=\"http://www.topografix.com/GPX/1/1\"\n")
	f.write( "xsi:schemaLocation=\"http://www.topografix.com/GPX/1/1 http://www.topografix.com/GPX/1/1/gpx.xsd\">\n")		
	f.write( "<trk>\n")
	f.write( "<name> RDE </name>\n")		
	f.write( "<trkseg>\n")

	for geo in root.findall(startNode):
		#print geo.attrib
		strLine = "<trkpt lat=\""+geo.get('lat')+"\"  lon=\"" + geo.get('long') + "\"></trkpt>"
		f.write( strLine )
		f.write( "\n" )

	f.write( "</trkseg>\n") 
	f.write( "</trk>\n")
	f.write( "</gpx>\n")
	f.close()


def writeCSVLine(f, strLine, col):
	for icol in col[:-1]:
		strLine += str(icol)+";"
	strLine+=str(col[-1])+"\n"
	f.write( strLine )

def createCSV(fileName, root, startNode, inProj, outProj):
	offsetX = 171338.11
	offsetY = 388410.20

	f = open(fileName+ ".csv", "w")
	col = [0.0]*36
	strLine=""
	writeCSVLine(f, strLine, col) 
	strLine=""
	writeCSVLine(f, strLine, col) 


	for geo in root.findall(startNode):
		transformer=Transformer.from_proj(inProj,outProj)
		X,Y=transformer.transform(geo.get('long'),geo.get('lat'))
		x=X-offsetX
		y=Y-offsetY
		yaw = 0.017453*float(geo.get('course'))

		col = [0.0]*36
		col[0]=geo.get('secs')
		col[1]=col[7]=x
		col[2]=col[8]=y
		col[6]=col[12]=yaw

		strLine=""
		writeCSVLine(f, strLine, col) 

	f.close()


def main():

	#Parameters
	if len(sys.argv) < 2:
		print('argument missing : name of the file to import')
		exit()
	
	infilename = sys.argv[1]
	outfoldername = os.path.splitext(infilename)[0] + "_vhlplayer/"
	try:
		os.mkdir(outfoldername)
	except:
		pass

	#Projections
	inProj=Proj(proj='latlong',datum='WGS84')
	outProj=Proj(init='epsg:28992', towgs84='565.417,50.3319,465.552,-0.398957,0.343988,-1.8774,4.0725')
	offsetX = 171338.11
	offsetY = 388410.20

	tree = ET.parse(infilename)
	root = tree.getroot()

	#Creation du fichier GPX
	createGPX(outfoldername + "hostvehicle", root, ".//hostvehicle/traj/geo")
	createCSV(outfoldername + "hostvehicle", root, ".//hostvehicle/traj/geo", inProj, outProj)
	createSCANeRMDL(outfoldername + "hostvehicle","car")
	createSCANePlayer(outfoldername + "hostvehicle")

if __name__ == '__main__':
	sys.exit(main())