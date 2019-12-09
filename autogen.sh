#!/bin/bash
mkdir -p m4 autoconf-aux
aclocal
autoconf
touch NEWS AUTHORS ChangeLog
automake --add-missing
