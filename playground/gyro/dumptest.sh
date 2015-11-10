#!/bin/bash
for a in 1 2 3 4 5 6 7 8 9 0 a b c d e f g h i j k l m n o p q r s t u v w x y z
do
	i2cdump -y  -r 0x00-0x7f 1  0x68 b | grep 40:
done
