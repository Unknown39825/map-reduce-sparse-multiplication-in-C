# map-reduce-sparse-multiplication-in-C
this is the implimentation of map reduce  for sparse multiplication in c language 

# the get and  and create function 
they are the basic function to create and input the matrix 

# the combine function 
it is used to combining the matrix in mapreducible form
firstly it makes seperate file for the the matrix one and two named as file1.txt and file2.txt and then combine them in D.txt

# the map function
it takes the input from the D.txt and makes key value pairs and put it in 



# the reduce function 
it takes input from the Dpart.txt and firstly sort them
and takes input one by one if same key occurs then it will add product of 
arr 1 and arr2 into result else
makes new terms
finally all result is written to result.txt 
in the form of row ,col ,value pair.

# then the put fuction 
it is used to takes result from the result.txt and 
display the result into sparse form;


