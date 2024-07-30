#!/usr/intel/pkgs/python/2.7/bin/python

import sys
import os
import glob

# DEBUGFEATURE is the prefix for debug defines
SEARCH_TERM = "DEBUGFEATURE"


def main():
  count = 0
  os.chdir(sys.argv[1])
  for file in glob.glob('*.o'):
    with open(file) as f:
      contents = f.read()
    if SEARCH_TERM in contents:
      if count == 0:
        print("______________________________________________\n")
        print("ERROR - There are debug define in these files:\n")
      print("*  " + file)
      count += 1	
  if count > 0: 
    print("\n")
    print("ERROR - There are debug define found in code")
    sys.exit(7) # 7 was randomly chosen
  else :
    print("______________________________________________\n")
    print("SUCCESS - No debug define found in code\n")


if __name__=='__main__':
    main()

