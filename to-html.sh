#!/bin/bash
OUTPUT="html-output"
mkdir $OUTPUT
for i in `ls *.h`; do
	echo -e "zi:TOhtml\n:wq\n:q\n" | vim $i
	mv $i.html $OUTPUT
done
