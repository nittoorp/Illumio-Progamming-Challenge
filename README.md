# Illumio-Progamming-Challenge (C++)
To read the NAT and FLOW file and return the FLOW IP address pair.

# Taken around 90 minutes to complete the challenge
# started at 5 pm 01/21 and finished by 6:30pm

I've approached the problem in the following way:

  1.) I've read the NAT.txt file to retreive the pairs of <IP:Port>,<IP:Port> pair
  2.) Split the string using ',' as the delimiter to store the <IP:Port> pair in a vector<string>
  3.) Sent the <IP:Port> vector as an argument to the insert() fucntion of the Trie data Structure.
  4.) Read the FLOW.txt and return a vector of <IP:Port> strings.
  5.) Implemented an Output function to write the pairs of FLOW to an "OUTPUT.txt"
 
I've used a Trie Data Structure to store the IP Addresses.
for example: if i have "10.10.10.103:8080" and "10.10.10.103:8081" as my input trie uses lesser memeory to store as the 
uniqueness of the ip address is very less. 

Stored as: 1-0-.-1-0.-1-0.-1-0-3-:-8-0-8 till here both of them have the same parents. The next character for the insert
fucntion is different so the ip address .....8-0-8-"(0,1)" as it's children and will have the paired <IP:Port> stored in a string.

I've assumed we have a lot of repetitions in the IP Addresses if we take an I/P for a particular region.

When we search for a particular string it returns the structure of {boolean and string} which are if the string exists and the 
paired string.

Because of the time constraints i could only search for valid strings and tried having a vector to store multiple pairs for 
the same <IP:Port> from the NAT file.

I came up with this solution because i felt having a Map would create a new object for every unique string unless there is an 
exact match, by using a Trie it can store the non-unique values without having to create a new object everytime.


If the files are too large, I don't think we can store it on the memory and none of the data strucutres will be of use, but 
for a smaller size in of file I felt this would be good option to store our data.

If i had more time I would have implemented an "external sort" (kind of merge sort on the IP addresses)on both the FLOW and 
NAT files and compare it with every FLOW input to check for a match and if there is a match would write it in a new file.
I feel this would be a better solution than having to store in a data structure, beacuse merge sort can sort the files quickly 
and we'd be just comparing the sorted ip addresses to store in a new file.
