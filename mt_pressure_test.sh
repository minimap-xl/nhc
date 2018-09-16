#!/bin/sh

# This is used as a last resort PATH to cpal2x. It is better users set
# their PATH appropriately, depending on where things are installed on
# their systems, with "export PATH = path_to_where_cpal_install:$PATH". 
# Otherwise, it is assumed that the CPAL toolset is installed under
# ~/Documents/CPAL-Editor/.

CPAL2X_LAST_RESORT=~/Documents/CPAL-Editor/tools

# Check that cpal2x is reachable through the current PATH
path_to_cpal2x=`which cpal2x`

if [ -z "$path_to_cpal2x" ]
then
   echo ">>> cpal2x cannot be reached from PATH, using CPAL2X_LAST_RESORT"
   PATH=$CPAL2X_LAST_RESORT:$PATH

   # Try once more after adjusting PATH
   path_to_cpal2x=`which cpal2x`
   if [ -z "$path_to_cpal2x" ]
   then
       echo ">>> CPAL2X_LAST_RESORT=\"$CPAL2X_LAST_RESORT\" is incorrect"
       exit 1
   fi
fi

# If CPAL_PKG_PATH is unset try to derive it from the path
# to cpal2x, otherwise leave it alone.

if [ -z "$CPAL_PKG_PATH" ]
then
    export CPAL_PKG_PATH=${path_to_cpal2x%/cpal2x}/pkg
    echo ">>> CPAL_PKG_PATH set to \"$CPAL_PKG_PATH\""
fi

# Default path to look up the skeletons for fault tolerance transformation
if [ -z "$CPAL_SKELETON_PATH" ]
then
    export CPAL_SKELETON_PATH=../fault_tolerance
    echo ">>> CPAL_SKELETON_PATH set to \"$CPAL_SKELETON_PATH\""
fi


# Temporarily add ../main to PATH to find nhc easily
PATH=../main:$PATH

# Move to the mt_samples directory and work on all files found there.

cd mt_samples

# Before running the test, remove any previous file.
find . \( -name "beauty_*.cpal" -or -name "mt_*.cpal" \) -type f -delete

for file in $(find . -name "*.cpal" -print); do
    # Remove the ./ that find insists to put in front of $file
    orig=${file##*/}

    # Call nhc on the original file and beautify -> mt_...
    nhc --beautify $orig > mt_$orig
done

