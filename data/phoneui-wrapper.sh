#!/bin/sh
CODE=0
while [ $CODE -ne 128 -a $CODE -ne 137 ]
do
	phoneuid
	CODE=$?
done
