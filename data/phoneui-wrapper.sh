#!/bin/sh
CODE=0
while [ $CODE -ne 128 -a $CODE -ne 137 -a $CODE -ne 255 ]
do
	ELM_ENGINE=x11 phoneuid
	CODE=$?
done
