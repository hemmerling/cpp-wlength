@echo off
rem * MASM 5.x
rem masm /Mx /Zi %1 %2 %3 %4 %5 %6 %7 %8 %9
rem * MASM 6.x, 7.x
rem * keine "_" vor den Globals:
rem ml /omf /c /Cx /Gd /Fl%1.lst %1.asm %2 %3 %4 %5 %6 %7 %8 %9
rem * mit "_" vor den Globals:
ml /omf /c /Cx /Fl%1.lst %1.asm %2 %3 %4 %5 %6 %7 %8 %9
