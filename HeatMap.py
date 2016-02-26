import math

class HeatMap:

	def __init__(self):
		self.ASSUMEDPOWER= 5.0 			#in Watts  #2 Watts?
		self.WAVELENGTH= .64811			#in meters
		self.arraySize= 10  			#number of segments per dimmension.  ie 10x10 map
		self.heatMapArray= [[0 for x in range(self.arraySize)] for x in range(self.arraySize)]
		self.totalReadings= 0.0
		self.maxInd= (-1,-1)
		self.maxHMVal= 0




	#adjust values of the array to between 0 and 1
	def normalize(self, totalP):
		for x in range(len(self.heatMapArray)):
			for y in range(len(self.heatMapArray[0])):
				self.heatMapArray[x][y]=self.heatMapArray[x][y]/totalP#relocate in the future
		self.maxHMVal= self.maxHMVal/totalP
		return self.heatMapArray


	def intensity(self,reading, x,y):#path loss
		#determine the distance using the path loss equation
		#values still need experimental calibration so I simplified it
		# my simplification simply assummes the reading has a linear inverse relation to distance
		# the path loss equation (commented out) also varies inversely but according to a more complicated equation
		distanceFromSource= self.ASSUMEDPOWER- reading[1]#math.pow(10,(self.ASSUMEDPOWER- reading[1])/20)*self.WAVELENGTH/(4*math.pi)
		#intensity should be refelctive of likelihood in a specific square
		#so if the square distance is the same distance from teh sensor as the reading it will have a high probability
		#.1 = bias tso max value would be 10
		return 1/(.1+math.pow((distanceFromSource-self.distance(reading[0][0], reading[0][1],x,y)),2))

	def distance(self,x0, y0, x1, y1): return math.sqrt((x0-x1)**2+(y0-y1)**2)

	#returns a weighted sum approximation of the location
	#analogous to center of mass in physics
	def centerOfGravity(self,data):
		massSum= xSum = ySum= 1
		for reading in data:
			massSum+= reading[1]
			xSum= xSum + reading[1]* reading[0][0]
			ySum= ySum + reading[1]* reading[0][1]
		return (xSum/massSum, ySum/massSum)

	
	#takes a list of data, makes a map,heatMapArray updates the number of 
	#data=list(individual datum)
	#individualdatum= (gpsx,gpsy),power-> add a wavelength component
	def powerDistanceUpdate (self,data):
		for newReading in data:
			self.maxHMVal=0
			totalProb= 0
			for x in range(len(self.heatMapArray)):
				for y in range(len(self.heatMapArray[0])):
					self.heatMapArray[x][y]= (self.heatMapArray[x][y]*self.totalReadings/(self.totalReadings+1))+ self.intensity(newReading, x,y)*(1/(self.totalReadings+1))
					totalProb+= self.heatMapArray[x][y]
					if(self.heatMapArray[x][y] > self.maxHMVal):
						self.maxHMVal= self.heatMapArray[x][y]
						self.maxInd= (x,y)
			self.totalReadings +=1
		self.normalize(totalProb)
		return self.heatMapArray

hm = HeatMap()
x= hm.powerDistanceUpdate([[[0,0],1],[[0,9],1],[[9,0],1],[[9,9],1]])
for a in x:
	print(a)

print(hm.maxInd)
print(hm.maxHMVal)

