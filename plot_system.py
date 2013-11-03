"""
Python script to plot the data we get from the output_files produced
by the program Project 3.

Pass the name of the output_file you want to plot as a 
commandline argumen.

Usage:
~$ python plot_system.pu output_EarthSunSystem.txt
"""


import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Reads filename of output file from commandline
filename = sys.argv[-1]

input_file = open(filename, 'r')

# Starts with i = -2 because the two first lines
# of the outputfile contains only general information about the problem.
i = -2
for line in input_file:
    column = line.split()
    
    if i == -2:
        # Reads from first line in file:
        object_nr = int(column[1])
        dimensions = int(column[3])
        time_step = float(column[6])
        end_time = float(column[9])

        # Initialize arrays and matrices:
        steps = int(np.ceil(end_time/time_step))+1
        
        positions = np.zeros([object_nr, dimensions, steps])
        time = np.zeros(steps)
        kinetic_energy = np.zeros([object_nr, steps])
        potential_energy = np.zeros([object_nr, steps])
        total_energy = np.zeros(steps)
        total_momentum = np.zeros([dimensions,steps])
        objects = []

    if i == -1:
        # Reads from second line in file
        for j in range(object_nr):
            objects.append(column[j+1])

    if i >= 0:
        # Reads values of the simulation
        time[i] = float(column[0])
        
        for j in range(object_nr):
            coordinate = column[j+1][1:-1].split(",")
            for k in range(dimensions):
                positions[j][k][i] = float(coordinate[k])
                
            kinetic_energy[j][i] = float(coordinate[dimensions])
            potential_energy[j][i] = float(coordinate[dimensions+1])
            
        total_energy[i] = float(column[object_nr+1])

        momentum = column[object_nr+2][1:-1].split(",")
        for k in range(dimensions):
            total_momentum[k][i] = float(momentum[k])



    i += 1

input_file.close()


if dimensions == 2:
    #Plot 2d plot of positions:
    fig = plt.figure(1)
    ax = fig.add_subplot(111, 
            xlabel=r'x-position [$AU$]',
            ylabel=r'y-position [$AU$]');
    for j in range(object_nr):
        if objects[j] == "Sun":
            ax.plot(positions[j][0], positions[j][1], 'or',
                    label=objects[j])
        else:
            ax.plot(positions[j][0], positions[j][1],
                    label=objects[j])
    
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width*0.8, box.height])
    ax.axis("equal")
    ax.grid('on')
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5),
            fancybox=True, shadow=True)

    # Plot of total momentum for 2 dimensions
    plt.figure(2)
    for j in range(dimensions):
        plt.plot(time, total_momentum[j])
        plt.hold('on')
    plt.hold('off')
    plt.grid('on')
    plt.xlabel(r'Time [$yr$]')
    plt.ylabel(r'Total Momentum [$M_{sun} \cdot \frac{AU}{yr}$]')
    plt.legend(['x-direction', 'y-direction'])

elif dimensions == 3:
    # Plot 3d plot of position
    fig = plt.figure(1)
    ax = fig.gca(projection='3d',
            xlabel='x-position [AU]',
            ylabel='y-position [AU]',
            zlabel='z-position [AU]')
    # Get dark background for 3d plot:
    # ax.w_xaxis.set_pane_color((0.0,0.0,0.0,0.8))
    # ax.w_yaxis.set_pane_color((0.0,0.0,0.0,0.8))
    # ax.w_zaxis.set_pane_color((0.0,0.0,0.0,0.8))
    for j in range(object_nr):
        if objects[j] == "Sun":
            ax.plot(positions[j][0], positions[j][1],
                    positions[j][2], 'or',
                    label=objects[j])
        else:
            ax.plot(positions[j][0], positions[j][1],
                    positions[j][2],
                    label=objects[j])
    
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width*0.8, box.height])
    ax.grid('on')
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5),
            fancybox=True, shadow=True)

    # Plot of total momentum for 3 dimensions
    plt.figure(2)
    for j in range(dimensions):
        plt.plot(time, total_momentum[j])
        plt.hold('on')
    plt.hold('off')
    plt.grid('on')
    plt.xlabel(r'Time [$yr$]')
    plt.ylabel(r'Total Momentum [$M_{sun} \cdot \frac{AU}{yr}$]')
    plt.legend(['x-direction', 'y-direction',
        'z-direction'])

# Plot of Total energy
plt.figure(3)
plt.plot(time,total_energy)
plt.grid('on')
plt.xlabel(r'Time [$yr$]')
plt.ylabel(r'Total Energy [$M_{sun} \cdot \frac{AU^2}{yr^2}$]')

if ( object_nr <= 3 ):
    # Plot of kinetic and potential energy of Earth for
    # cases with 3 or less objects, like the Earth-Sun system or
    # the Jupiter-Earth-Sun system.
    plt.figure(4)
    for i in range(object_nr):
        if( objects[i] == "Earth" ):
            plt.plot(time, kinetic_energy[i])
            plt.hold('on')
            plt.plot(time, potential_energy[i])
    plt.hold('off')
    plt.grid('on')
    plt.xlabel(r'Time [$yr$]')
    plt.ylabel(r'Energy [$M_{sun} \cdot \frac{AU^2}{yr^2}$]')
    plt.legend(['Kinetic energy', 'Potential energy'])

plt.show()
