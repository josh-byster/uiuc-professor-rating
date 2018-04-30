# Development

In this file, I will keep track of the changes that I've made to my project.

Updated Monday, April 30th

I have gone through the process of creating the following:
 - Added a legend to the GUI
 - Fixed a bug that was computing GPAs for incorrect values when an instructor taught different courses the same semester
 - Adding comments to the file
 - Started writing testing framework to make sure calculations are correct
 - Updated Proposal.md to the final version
 - Generated a new OpenFrameworks project
 - Installed the ofxDatGui addon to display relevant data
 - Added search functionality to search for instructors within the GUI
 - Worked on making this a "soft search" so that only typing part of the name would yield search results
 - Created ability to load directly from CSV
 - Constructed hashmaps, both ordered and unordered, as a primary way of storing objects in the dataframe
 - Implemented a custom hashing function and comparator to store custom section objects in the hashmap along with a way to keep them sorted chronologically.
 - Started getting basic GPA calculations working (although this needs work since it's currently only by course but we want the calculation to be by section)
 - Worked on const correctness to make sure nothing was accidentally being modified
 - Able to get all courses that a given instructor has taught in the past (since 2010) and display them visually in the GUI.
