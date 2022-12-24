#!/bin/bash


echo "Generating UI header files..."
uic sources/mainwindow.ui -o headers/ui_mainwindow.h
uic sources/mainmenu.ui -o headers/ui_mainmenu.h
echo "UI header files have been generated!"
