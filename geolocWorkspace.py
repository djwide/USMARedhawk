constants gpspair 1,2,3

def pdoa(self):
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	p1,p2,p3= powerReadingsQueue.pop
	# distance ratios
	d12= pow(10, -(p1-p2)/(10*alpha))#p1 is unpacked power reading
	d23= pow(10, -(p2-p3)/(10*alpha))
	d31= pow(10, -(p3-p1)/(10*alpha))
	x1, x2,	x3, y1, y2, y3= 5# constants
	#use  equations to find centers and radii
	cx1, cy1= circleCenters(x1, y1, x2, y2, d13)
	cx2, cy2= circleCenters(x2, y2, x3, y3 d23)
	cx3, cy3= circleCenters(x3, y3, x1, y1, d31)
	rc1= radEqn(x1,y1,x2,y2,d12)
	rc1= radEqn(x2,y2, x3, y3, d23)
	rc1= radEqn(x3, y3,x1,y1,d31)
	for x <- xrange:
		for y <- yrange:
			#will have timestamp data
			d1= distance to c1 - rc1
			d2= distance to c2 - rc2
			d3= distance to c3 - rc3
			array(x)(y)= intensity(d1)*intensity(d2)*intensity(d3)

#join methods for efficiency
def radEqn(self, x1, y1, x2, y2, d):
	return pow(pow((x1-x2*d*d)/(d*d-1),2)+pow((y1-y2*d*d)/(d*d-1),2)-(d*d*x2*x2+d*d*y2*y2-x1*x1-y1*y1)/(d*d-1),.5)

def circleCenters(self, x1, y1, x2, y2, d):
	return (x2*d12*d12-x1)/(d12*d12-1),(y2*d12*d12-y1)/(d12*d12-1)


#merge with pdoa for efficiency
def aoa(self):
	#receive message
	#unpack data
	#check timestamp
	#create 3 queues to hold data
	x1, x2,	x3, y1, y2, y3= 5# constants
	aread1, aRead2, aRead3= 2
	for x <- xrange:
		for y <- yrange:
			#will have timestamp data
			#could index the below and only calculate once
			aActual1= tan((y-y1)/(x-x1))
			aActual2= tan((y-y2)/(x-x2))
			aActual3= tan((y-y3)/(x-x3))
			readingCloseness1= (180- (aRead1-aActual1))/180
			readingCloseness2= (180- (aRead2-aActual2))/180
			readingCloseness3= (180- (aRead3-aActual3))/180	
			array(x)(y)= readingCloseness1*readingCloseness2*readingCloseness3	

