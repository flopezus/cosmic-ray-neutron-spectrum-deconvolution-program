#!/bin/bash

# Loop through files from LasCampanasAtacama_00.dat to LasCampanasAtacama_100.dat
for i in {0..100..2}; do
    input_file="./LasCampanasAtacama_${i}.dat"
    output_file="./csv_files/LasCampanasAtacama_${i}.csv"

    # Check if the input file exists
    if [ -e "$input_file" ]; then
        # Add header and replace spaces with commas
        echo "lower_edge_binvalue,bin_width,flux_value" > "$output_file"
        # Cut the input file to contain only 130 rows and replace spaces with commas
        head -n 130 "$input_file" | sed 's/ /,/g' >> "$output_file"

        echo "Conversion complete for $input_file. Output saved to $output_file"
    else
        echo "Input file $input_file not found. Skipping..."
    fi
done
