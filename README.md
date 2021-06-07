# EventScheduler
simple C++ command line event scheduler.
### about 
- This program contains code native to windows only, such as the windows.h library, which is utilized to create and navigate directories.
- Data for this project are stored in text files.
# Modules
- DateTimeGenerator is used to get instances of local time in tm struct form, as well as compare two dates.
- FileManager is used to read & write username, passwords as well as events  information to txt files.
# Classes
- user class contains user specific data and some functions to manage events
- event class contains details specific to a single instance event.
- console class contains the main program and control flow.
