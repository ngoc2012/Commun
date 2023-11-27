::schtasks /create /sc MINUTE /mo 2 /tn "Commun" /tr "C:\Users\Nguyen Minh Ngoc\Commun\pull.bat"
@echo off
cd C://Users/Nguyen Minh Ngoc/Commun
git pull