#!/bin/bash
for f in tests/lexer/*.slice
do
	echo $f
	bin/testlexer $f
done
