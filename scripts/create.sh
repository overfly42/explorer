#!/bin/bash
echo "create new module"
read -p "Please type module name: " mod_name
folder_name=mod_$mod_name
rm -rf $folder_name
if [ -d ./$folder_name ]
	then
		echo "Folder already exists...abort"
		exit -1
fi
echo "creating $folder_name for Modul $mod_name"
#creating folders
mkdir $folder_name
mkdir $folder_name/doc
mkdir $folder_name/doc/src
mkdir $folder_name/doc/essentials
mkdir $folder_name/src
mkdir $folder_name/config

#create Makefile
file=$folder_name/Makefile

echo "$mod_name:" >> $file
echo "	@echo customize" >> $file
echo "clean_$mod_name:" >> $file
echo "	@echo customize" >> $file

git add $file
#create empty documentation files
file=$folder_name/doc/src/main.tex
touch $file
git add $file
file=$folder_name/doc/essentials/package.tex
touch $file
git add $file
file=$folder_name/doc/essentials/macro.tex
touch $file
git add $file
file=$folder_name/doc/essentials/abstract.tex
touch $file
git add $file

echo "Commiting new module"
git commit -a -m "Created new Module $mod_name"
git branch $mod_name
