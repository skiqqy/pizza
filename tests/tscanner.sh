#!/bin/bash
for f in tests/scanner/*.slice
do
	echo $f
	bin/testlexer $f
done
