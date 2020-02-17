This is a simple program that can filter the pre-amplifier waveforms to get energy information.
The math form of trapezoidal filter can be found on the page 16 of https://www.science.mcmaster.ca/radgrad/images/6R06CourseResources/4RA34RB3_Lecture_Note_6_Pulse-Processing.pdf

The program takes an entry from the SIS3316 root file, and two parameters peaktime and gaptime can be adjusted to achieve best energy resolution.
This is a root Macro, so just root->.L trapefiltertutorial.cc->trapezoidalfilter(user parameters)

