#!/bin/bash

# Use this script to scrape data from the web using the provided shell scripts provided.
wget -O - https://mihajlovikj.github.io/media/baseballdata.csv | cut -d ',' -f 5 | tail -n +2 > data.txt

