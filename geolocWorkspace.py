import math
xsize, ysize= 8,8
array= [[0 for x in range(xsize)] for x in range(ysize)]
def pdoa():
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	#p1,p2,p3= powerReadingsQueue.pop
	p1, p2, p3= 5,1.1,.9
	alpha= 3 #2 to 4 where 2 is free space
	# distance ratios
	d12= pow(10, -(p1-p2)/(10*alpha))#p1 is unpacked power reading
	d23= pow(10, -(p2-p3)/(10*alpha))
	d31= pow(10, -(p3-p1)/(10*alpha))
	print(d12)
	print(d23)
	print(d31)
	x1, x2,	x3, y1, y2, y3= 0,0,7,0,7,0# constants for GPS locations of sensors
	c1 = circleCenters(x1, y1, x2, y2, d12)
	print(c1)
	c2 = circleCenters(x2, y2, x3, y3, d23)
	print(c2)
	c3 = circleCenters(x3, y3, x1, y1, d31)
	print(c3)
	rc1= radEqn(x1,y1,x2,y2,d12) 
	print(rc1)
	rc2= radEqn(x2,y2, x3, y3, d23)
	print(rc2)
	rc3= radEqn(x3, y3,x1,y1,d31)
	print(rc3)
	for x in range(0, xsize):
		for y in range(0,ysize):
			#will have timestamp data
			#print(c1[0])
			d1= math.fabs(distance(x,y, c1[0], c1[1]) - rc1)
			d2= math.fabs(distance(x,y, c2[0], c2[1]) - rc2)
			d3= math.fabs(distance(x,y, c3[0], c3[1]) - rc3)
			array[x][y]= intensity((x,y), c1[0], c1[1],rc1)*intensity((x,y), c2[0], c2[1],rc2)*intensity((x,y), c3[0], c3[1],rc3)
	array[0][0]="OOOOO"
	array[0][7]="ypos"
	array[7][0]="xpos"
	return array
	
#join methods for efficiency
def radEqn(x1, y1, x2, y2, d):
	return pow(pow((x1-x2*d*d)/(d*d-1),2)+pow((y1-y2*d*d)/(d*d-1),2)-(d*d*x2*x2+d*d*y2*y2-x1*x1-y1*y1)/(d*d-1),.5)

def circleCenters(x1, y1, x2, y2, d):
	return (x2*d*d-x1)/(d*d-1),(y2*d*d-y1)/(d*d-1)#divide by zero

def distance(x0, y0, x1, y1): return math.sqrt((x0-x1)**2+(y0-y1)**2)

def intensity(reading, x,y, distanceFromSource):#pathloss incorporated elsewhere.  Switch this up eventually
		return math.tanh(1/(.001+math.pow((distanceFromSource-distance(reading[0], reading[1],x,y)),2)))
#merge with pdoa for efficiency
def aoa():
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	arraySum=0
	x1, x2,	x3, y1, y2, y3= .001,3.5,3.5,.001,6.999,0.001#constants
	aRead1, aRead2, aRead3= math.pi/4, -math.pi/2, math.pi/2
	for x in range(0, xsize):
		for y in range(0,ysize):
			#will have timestamp data
			#could index the below and only calculate once
			aActual1= angleSignTrans(y,y1,x,x1)
			aActual2= angleSignTrans(y,y2,x,x2)
			aActual3= angleSignTrans(y,y3,x,x3)
			readingCloseness1= (math.pi- radialDistance(aRead1,aActual1))/math.pi
			readingCloseness2= (math.pi- radialDistance(aRead2,aActual2))/math.pi
			readingCloseness3= (math.pi- radialDistance(aRead3,aActual3))/math.pi
			array[x][y]= readingCloseness1*readingCloseness2*readingCloseness3	
			arraySum+= array[x][y]
	array[0][0]="OOOOO"
	array[0][7]="ypos"
	array[7][0]="xpos"
	return array#normalize(arraySum, array)
def angleSignTrans(y,yRead,x,xRead):
	if(y>yRead and x>xRead):
		return math.atan((y-yRead)/(x-xRead))
	elif(y>yRead and x<xRead):
		return math.pi+math.atan((y-yRead)/(x-xRead))
	elif(y<yRead and x>xRead):
		return math.atan((y-yRead)/(x-xRead))
	else:
		return -(math.pi-math.atan((y-yRead)/(x-xRead)))
def radialDistance(x, y): #critical, acounts for discontinuiutes in arctan
	dist= math.fabs(x-y)%(2*math.pi)
	if(dist>math.pi): return 2*math.pi- dist
	return dist
def normalize(totalP, array):
	for x in range(xsize):
		for y in range(ysize):
			array[x][y]=array[x][y]/totalP#relocate in the future
	#self.maxHMVal= self.maxHMVal/totalP
	return array


abcd=pdoa()

for line in abcd:
	print(line)