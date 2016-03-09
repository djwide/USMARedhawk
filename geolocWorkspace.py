import math
xsize, ysize= 100, 100
array= [[0 for x in range(xsize)] for x in range(ysize)]
def pdoa():
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	#p1,p2,p3= powerReadingsQueue.pop
	p1, p2, p3= 5,6,7
	alpha= .5
	# distance ratios
	d12= pow(10, -(p1-p2)/(10*alpha))#p1 is unpacked power reading
	d23= pow(10, -(p2-p3)/(10*alpha))
	d31= pow(10, -(p3-p1)/(10*alpha))
	x1, x2,	x3, y1, y2, y3= 5,5,6,6,7,7# constants
	#use  equations to find centers and radii
	c1 = circleCenters(x1, y1, x2, y2, d12)
	c2 = circleCenters(x2, y2, x3, y3, d23)
	c3 = circleCenters(x3, y3, x1, y1, d31)
	rc1= radEqn(x1,y1,x2,y2,d12)
	rc2= radEqn(x2,y2, x3, y3, d23)
	rc3= radEqn(x3, y3,x1,y1,d31)
	for x in range(0, xsize):
		for y in range(0,ysize):
			#will have timestamp data
			#print(c1[0])
			d1= distance(x,y, c1[0], c1[1]) - rc1
			d2= distance(x,y, c2[0], c2[1]) - rc2
			d3= distance(x,y, c3[0], c3[1]) - rc3
			array[x][y]= intensity((x,y), c1[0], c1[1],rc1)*intensity((x,y), c2[0], c2[1],rc2)*intensity((x,y), c3[0], c3[1],rc3)
	return array
	
#join methods for efficiency
def radEqn(x1, y1, x2, y2, d):
	return pow(pow((x1-x2*d*d)/(d*d-1),2)+pow((y1-y2*d*d)/(d*d-1),2)-(d*d*x2*x2+d*d*y2*y2-x1*x1-y1*y1)/(d*d-1),.5)

def circleCenters(x1, y1, x2, y2, d):
	return (x2*d*d-x1)/(d*d-1),(y2*d*d-y1)/(d*d-1)

def distance(x0, y0, x1, y1): return math.sqrt((x0-x1)**2+(y0-y1)**2)

def intensity(reading, x,y, distanceFromSource):#pathloss incorporated elsewhere.  Switch this up eventually
		#determine the distance using the path loss equation
		#values still need experimental calibration so I simplified it
		# my simplification simply assummes the reading has a linear inverse relation to distance
		# the path loss equation (commented out) also varies inversely but according to a more complicated equation
		#distanceFromSource= self.ASSUMEDPOWER- reading[1]#math.pow(10,(self.ASSUMEDPOWER- reading[1])/20)*self.WAVELENGTH/(4*math.pi)
		#intensity should be refelctive of likelihood in a specific square
		#so if the square distance is the same distance from teh sensor as the reading it will have a high probability
		#.1 = bias tso max value would be 10
		return 1/(.1+math.pow((distanceFromSource-distance(reading[0], reading[1],x,y)),2))
#merge with pdoa for efficiency
def aoa():
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	x1, x2,	x3, y1, y2, y3= 5.1,5.1,6.1,6.1,7.1,7.1#constants
	aRead1, aRead2, aRead3= 60, 80, 100
	for x in range(0, xsize):
		for y in range(0,ysize):
			#will have timestamp data
			#could index the below and only calculate once
			aActual1= math.tan((y-y1)/(x-x1))
			aActual2= math.tan((y-y2)/(x-x2))
			aActual3= math.tan((y-y3)/(x-x3))
			readingCloseness1= (180- (aRead1-aActual1))/180
			readingCloseness2= (180- (aRead2-aActual2))/180
			readingCloseness3= (180- (aRead3-aActual3))/180	
			array[x][y]= readingCloseness1*readingCloseness2*readingCloseness3	
	return array

print(aoa())