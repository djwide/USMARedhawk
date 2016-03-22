#!/usr/bin/env python
#
#
# AUTO-GENERATED
#
# Source: dbwriter.spd.xml
from ossie.resource import start_component
import logging
import MySQLdb as mdb
import sys
import time


from dbwriter_base import *

class dbwriter_i(dbwriter_base):
    """<DESCRIPTION GOES HERE>"""
    def initialize(self):
        """
        """
        dbwriter_base.initialize(self)
        self.count = 0
        print "connecting to db..."
        try:
            self.con = mdb.Connect('192.168.1.54', 'webserve', 'redhawk', 'RHtest')
            print "success"
            self.cursor = self.con.cursor()
        except mdb.Error, e:
            print "fail /n"
            print "Error " + str(e.args[0]) + ": " + str(e.args[1])
            sys.exit(1)
        # TODO add customization here.
       

    def process(self):
        """
           
        """

        # TODO fill in your code here
        dataX, T, EOS, streamID, sri, sriChanged, inputQueueFlushed = self.port_dataFloat_in.getPacket()
        data= [30.000, 777.777, 41.394083, -73.955667, 90.549,  1]
        
        if data == None:
            return NOOP
        insertString= '20160322103000, '
        #YYYMMDDHHMMSS = datetime
        #f = open("rhtest.txt", "wr")
        self.count += 1
        for i in range(0, 5):
            insertString += str(data[i]) + ", "
        insertString += str(data[5])
#        self.cursor.execute("INSERT INTO TestTable(time, dp1, dp2, dp3, dp4, dp5, dp6, dp7, dp8, dp9, dp10, count) VALUES(" + insertString[0:len(insertString) - 3])
        self.cursor.execute("INSERT INTO transmissions(time, db, frequency, latitude, longitude, angle, transmitting) VALUES(" + insertString +");")
        # NOTE: You must make at least one valid pushSRI call
        outData = 'a'
        if sriChanged:
            self.port_dataFloat_out.pushSRI(sri);

        self.port_dataFloat_out.pushPacket(outData, T, EOS, streamID)
        return NORMAL
        self._log.debug("process() example log message")
        return NOOP
#INSERT INTO TestTable(vals) VALUES(vals)

if __name__ == '__main__':
    logging.getLogger().setLevel(logging.INFO)
    logging.debug("Starting Component")
    print "hello"
    start_component(dbwriter_i)
    print "test"
