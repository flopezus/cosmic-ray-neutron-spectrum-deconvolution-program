#!/bin/bash

# Create a temporary directory to store renamed files
temp_dir=$(mktemp -d)

# Loop through the range of file numbers from 1 to 289
for ((i=1; i<=289; i++))
	do
		for ((j=1;j<=20; j++))
			do
				# Define the old and new filenames
				old_filename="EM_unfolding_loop_campaign_LCO_event_${i}_steps_${j}_timegrid_15_ndet_11.root"
				new_filename="EM_unfolding_loop_campaign_LCO_event_$((i+1))_steps_${j}_timegrid_15_ndet_11.root"
				
				# Move the file to the temporary directory with the new name
				mv "$old_filename" "$temp_dir/$new_filename"
			done
		done
# Move the renamed files back to the original directory
mv "$temp_dir"/* .

# Remove the temporary directory
rmdir "$temp_dir"
