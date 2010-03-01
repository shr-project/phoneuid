#!/bin/sh
CODE=-1
while [ $CODE -ne 128 -a $CODE -ne 137 -a $CODE -ne 255 -a $CODE -ne 0 ]
do
	ELM_ENGINE=x11 phoneuid
	CODE=$?
done
