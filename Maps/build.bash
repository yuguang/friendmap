#!/bin/bash
cd /Developer/SDKs/Research\ In\ Motion/Blackberry\ 10\ WebWorks\ SDK\ 1.0.4.11/dependencies/tools/bin
../../../bbwp ~/RippleSites/Maps/Build/maps.zip -d -o ~/RippleSites/Maps/Build/output
./blackberry-deploy -installApp -password 1a2345 -device 169.254.1.5 -package /Users/Bill/RippleSites/Maps/Build/output/device/maps.bar
