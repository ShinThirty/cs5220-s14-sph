#! /bin/bash

# In a shell script you run with ompsub
 amplxe-cl -collect hotspots -result-dir r001hs -- ./sph.x -F 10
# See hotspots
 amplxe-cl -report hotspots -r r001hs
# Dig down into one function
 amplxe-cl -report hotspots -source-object function=compute_density -r r001hs
