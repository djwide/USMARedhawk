Notes
	-Sensor Node components are written in c++ for efficiency.  The efficiency of the central node isn't a limiting factor and is therefore written in python.  
	-The array iteration within the heatmap can be parellelized for efficiency if you are so inclined
	-Any additional "confidence" ratings (i.e. more power readings or angle of arrival confidence) can be incorporated into the heatmap by simply multiplying them to the previous heatmap value.  Look up Bayes Rule.  
	-Update the power readings and the line of bearing readings within the same for loop  so you don't unnecessarily double you computation time.
	-To make a component from scratch:
		-File->New-> Redhawk Component Project.  Fill out however you deem fit from there
	- To import a component:  I have had most success downloading straight from github or downloading all raw data off of github.  Sometimes it doesn't work for seemingly no reason.  in this case you just need to make a component with the same name, the same structure and the same ports.  Recompile.  At that point, copy and paste the substantive files.  ("name.h, name.cpp") and recompile.  This will work sometimes.  
	- Look up more complex path loss algorithms.  Find a math person to work it through the same steps as the original mathematical progression to reach a new center and radius equation except based on a more accurate path loss formula.

Screen Record
	byzanz-record --duration=10 -v filename.ogg #10 seconds.  Look up byzanz documentation if you need to
	I couldn't figure out how to activate the sound.  Try if you'd like.  The workaround I used to make videos was that I recorded the screen capture on the centos machine uploaded it to dropbox and retroactively commented on my cadet labtop.  Complicated, I know.
