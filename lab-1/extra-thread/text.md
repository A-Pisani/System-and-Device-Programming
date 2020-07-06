# Extra Exercise on Threads
A file, of undefined length and in ASCII format, contains a list of integer numbers. 
Write a program that, after receiving a value k (integer) and a string from command line, generates k threads and wait them 
Each thread  
-	Reads concurrently the file, and performs the sum of the read integer numbers 
-	When the end of file is reached, it must print the number of integer numbers it has read and the computed sum 
-	Terminates  
After all threads terminate, the main thread has to print the total number of integer numbers and the total sum 

