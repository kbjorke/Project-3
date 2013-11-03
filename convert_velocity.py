"""
Python script to convert velocities form units of km/s to
units of AU/yr.

Takes velocity in units of km/s as commandline argument.
"""

import sys

velocity_kms = float(sys.argv[-1])

# Conversion constants
length = 149.6e6 # [km/AU]
time = 3.15569e7 # [s/yr]

velocity_AUyr = velocity_kms*time/length

print "%.6f km/s = %.6f AU/yr" % (velocity_kms, velocity_AUyr)
