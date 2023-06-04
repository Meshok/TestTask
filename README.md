# Daily Planner
### WHAT IS IT?
This is daily planner.

You can create and store records of two types:  
- Event  
  - Creation date _(filled in automatically)_  
  - Expiration date  
  - Description  
- Birthday  
  - Date of birthday  
  - Surname  
  - Name  
  - Patronymic _(Optional)_

Also you can view them:
- all
- by today's date
- by date (creation/expiration/date of birthday)
- by full name of person

And you can save/load state of program.  
**(Be careful! Loading clears the current state of the program!)**
### HOW TO INSTALL
In main directory do this:
#### Makefile
```
make
```  
#### CMake
```  
cmake -S . -B build  
cmake --build build
```
