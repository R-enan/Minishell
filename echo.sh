#!/bin/bash
((i++))
((i--))
i=0
while [ $i -le 255 ];
do
printf "Echo com $(printf "%s" $i)%2c = $(echo ~0)\n" 
#echo ~0
#printf "\x$(printf %x 65)"

((i++))
done
printf "%b" "Tha-" "tha-" "tha-" "that's all folks.\n" # teste