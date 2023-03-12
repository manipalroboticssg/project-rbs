# project-rbs
- A Robot which can scan a scrambled 3x3 Rubik's cube, and generate the steps required to sovle it. 
- Those steps are uploaded to a MCU which actuates 6 stepper motors accordingly, which are coupled with a physical 3x3 Rubik's cube.
- Scanning process is done by OpenCV ROI and colour detection features, which are performed multiple times on a particular face of the cube logically to scan the scrambled configuration of the cube.
