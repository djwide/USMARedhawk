from HeatMap import HeatMap
import math

hm= HeatMap()
'''
KNOWN GOOD
	Distance
		Return the pythagorean distance between two coordinates
'''
if(hm.distance(0,0,3,4) ==5): print("test 0: distance(0,0,3,4)==5 passed")
else: print("test 0: distance(0,0,3,4)==5 failed")
print("\n")
if(hm.distance(-1,-1,11,4) ==13): print("test 1: distance(-1,-1,11,4) ==13 passed")
else: print("test 1: distance(-1,-1,11,4) ==13 failed")
print("\n")
'''
	Intensty
		Return a scalar value representative of the relative likelihood	that 
		the radio is in a certain location given the known location of the 
		sensor and the power reading of the sensor
'''
if(math.fabs(hm.intensity([[2,2],3], 3,3)-.55)<.01): print("test 2: math.fabs(intensity([[2,2],3], 3,3)-.55)<.01 passed")
else: print("test 2: math.fabs(intensity([[2,2],3], 3,3)-.55)<.01 failed")
print("\n")
'''
	Center of gravity
		Return the geometric mean of the all of the sensor readings.  Higher power 
		readings will bias the estimate towards the sensor location.
'''
if(hm.centerOfGravity([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]])==(1,1)): print("test 3: centerOfGravity([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]])==(1,1) passed")
else: print("test 3: centerOfGravity([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]])==(1,1) failed")
print("\n")

''' 
	Update map
		return the heat map that has been updated with a list of new data readings.  
		The function will iterate through each ceel of the Array and adjust the likelihood
		based onnewly acquired information

'''
if(len(hm.powerDistanceUpdate([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]]))==10): print("test 4: len(powerDistanceUpdate([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]]))==10 passed")
else: print("test 4: len(powerDistanceUpdate([[[0,0],1],[[0,2],1],[[2,0],1],[[2,2],1]]))==10 failed")
print("\n")
'''
KNOWN BAD RESULTS
	distance
	intensty
	center of gravity 
	update map




'''
'''
POSSIBLE MALFORMED INPUTS
	type check all input that could potentially come from a user
	distance
	intensty
	center of gravity 
	update map






'''