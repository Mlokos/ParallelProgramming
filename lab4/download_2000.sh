#!/bin/bash
for i in {1..2000}
do
    wget "http://www.gutenberg.org/files/$i/$i.txt"
    wget "http://www.gutenberg.org/files/$i/$i-0.txt"
done
