
//  Progamming_Challenge.cpp
//  Illumio Coding Challenge

//inclduing all the necessary libraries

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

//Struture to return the saerch fields with a boolean and the pair of the FLOW file
struct ReturnSearch{
    bool isTrue;
    string pairOfIP;
    //vector<string> pairsOfIp;
};
// to create a new return search object
ReturnSearch* getNewSearch(){
    ReturnSearch* search = new ReturnSearch;
    search->isTrue=false;
    return search;
}

//Structure to define a Trie
struct Trie {
  
    // isEndOfIP is true if the node
    // represents end of a word
    bool isEndOfIP;
  
    /* nodes store a map to child node */
    unordered_map<char, Trie*> map;
    // to store the paired ip and port
    string pairOfIPAndPort;
    //vector<string> pairsOfIPAndport;
    
};
  
//craeting a new trie node
Trie* getNewTrieNode()
{
    Trie* node = new Trie;
    node->isEndOfIP = false;
    return node;
}
  
//to insert into a trie
void insert(Trie*& root, const string& str,string pair)
{
    //checks if the root is null then creates a new trie node
    if (root == nullptr)
        root = getNewTrieNode();
    // else takes a node to iterate through the trie
    Trie* current = root;
    for (int i = 0; i < str.length(); i++) {
        char x = str[i];
  
       // if there is no path creates a new path
        if (current->map.find(x) == current->map.end())
            current->map[x] = getNewTrieNode();
  
        current = current->map[x];
    }
  // checks till the end of the IP then inserts the pair and marks it as end of the IP.
    current->isEndOfIP = true;
    current->pairOfIPAndPort=pair;
    //current->pairsOfIPAndport.push_back(pair);
}
  
/*function to search in trie*/
ReturnSearch* searchForIpPair(Trie* root, const string& str)
{
    ReturnSearch* search = getNewSearch();
    /*return false if Trie is empty*/
    if (root == nullptr)
        return search;
  
    Trie* current = root;
    for (int i = 0; i < str.length(); i++) {
  
        /* go to next node*/
        current = current->map[str[i]];
  
        if (current == nullptr)
            return search;
    }
    search->isTrue=true;
    search->pairOfIP = current->pairOfIPAndPort;
    //search->pairsOfIp = current->pairsOfIPAndport;
    return search;
}
/*string getPairOfIP(Trie* root, const string& str){
    //return false if Trie is empty
      if (root == nullptr)
          return nullptr;
    
      Trie* current = root;
      for (int i = 0; i < str.length(); i++) {
    
          // go to next node
          current = current->map[str[i]];
    
          if (current == nullptr)
              return nullptr;
      }
    return current->pairOfIPAndPort;
}*/
// returns a vector of string after reading a  NAT file 
vector<string> readNATFile(){
    fstream openNATFile; 
    // creating a filestream object
    vector<string> storeIPandPortPairs; 
    //vector to store strings
    openNATFile.open("NAT.txt",ios::in); 
    //open NAT file to perform read operation using file object
    if (openNATFile.is_open()){   
    //checking whether the file is open
        string newLine;  
        // creating a string to read the each new line from the file
        while(getline(openNATFile, newLine)){ 
        //read data from file object and put it into string.
           //cout<<"Splitting the line" << newLine << "\n";
                char* ipAndPortPair = new char[newLine.length()]; // to split the string creating a char Array
                strcpy(ipAndPortPair,newLine.c_str());
                char *singleIPandPort;
                singleIPandPort = strtok (ipAndPortPair,",");   // splitting the line by "," to get two ip:port pairs.
                while (singleIPandPort != NULL)
                {
                    //cout<<singleIPandPort<<"\n";
                    storeIPandPortPairs.push_back(singleIPandPort);  
                    // storing the ip:port pairs in a vector
                    singleIPandPort = strtok (NULL, "");
                }//print the data of the
        }
       openNATFile.close(); //close the file object.
    }
    return storeIPandPortPairs;  // returns ab ovject of vecotr to the calling function.
}
// returns a vector of strings adter reading hte FLOW file
vector<string> readFLOWFile(){
    fstream openFlowFile; 
    // creating a new fstream object
    vector<string> storeFLOWIpandPort; 
    // creating a vector of string to return 
    openFlowFile.open("FLOW.txt",ios::in); 
    //open a file to perform read operation using file object
    if (openFlowFile.is_open()){   
    //checking whether the file is open
        string flowIPandPort;
       while(getline(openFlowFile, flowIPandPort)){ 
       //read data from file object and put it into string.
               storeFLOWIpandPort.push_back(flowIPandPort); 
               // storing the string in a vecotr
           }//print the data of the string
       }
       openFlowFile.close(); 
       //close the file object.
    
    return storeFLOWIpandPort; 
    // returns the ovject to the calling function.
}


// function to store in the trie data structure input is the root and a vector of IP addresses
Trie* storeInTrie(Trie* root,vector<string> storedString){
    for (int i=0;i<storedString.size();i+=2) {
        //cout<<storedString[i]<<"\n";
        insert(root, storedString[i],storedString[i+1]);
    }
    return root;
}

// OUTPUT file being written after reading the FLOW file being returned from the readFLOWfile
void outputForFlow(Trie* root,vector<string> flowIpandPort){
    string pairedIP; 
    // to retreive the paired ip
    string starSearchBefore,starSearchAfter; 
    // to search for *:* elements in the FLOW file
    ofstream file; 
    // creating a file stream object
    file.open ("OUTPUT.txt");  
    for (int i=0;i<flowIpandPort.size();i++)
    {
           string currentIp = flowIpandPort[i];  
           // having to copies of the current ip from the FLOW file to convert them in *:port and ip:* format and search in the trie
           string currentIpCopy = flowIpandPort[i];
           int position = (int)currentIp.find(":");
            // to know the position of the ':' delimiter
           //cout<<currentIp<<" "<<position<<"\n";
           starSearchAfter = currentIpCopy.replace(currentIpCopy.begin()+position+1,currentIpCopy.end(),"*");  //
           starSearchBefore = currentIp.replace(0, position, "*");
           ReturnSearch *search = searchForIpPair(root, flowIpandPort[i]), *searchForStarAfter=searchForIpPair(root, starSearchAfter), *searchForStartBefore=searchForIpPair(root, starSearchBefore);
           //searching for the ip with normal and , *:port and ip:* 
           // if true in a case rest won't be true so one copy per ip address is store in the o/p file
            if(search->isTrue){
                file<<flowIpandPort[i]<<"->"<<search->pairOfIP<<"\n";
                //cout<<search->pairOfIP<<"\n";
            }
            else if (searchForStarAfter->isTrue){
                file<<flowIpandPort[i]<<"->"<<searchForStarAfter->pairOfIP<<"\n";
                //cout<<searchForStarAfter->pairOfIP<<"\n";
            }
            else if (searchForStartBefore->isTrue){
                file<<flowIpandPort[i]<<"->"<<searchForStartBefore->pairOfIP<<"\n";
                //cout<<searchForStartBefore->pairOfIP<<"\n";
            }
            else{
                file<<"No NAT Match for ->"<<flowIpandPort[i]<<"\n";
                //cout<<"There is no IP Pair\n";
            }
           //cout<<starSearchAfter<<starSearchBefore<<"\n";
           //cout<<starSearchBefore<<"\n"<<starSearchAfter;
            
            
    
    }
    //closing the file
    file.close();
}

int main(int argc, const char * argv[]) {
    // creating a new Trie
    Trie* root = nullptr;
    // Reading the NAT FIle
    cout<<"Reading the NAT File\n";
    //vector<string> storedString = readNATFile();
    // Reading the FLOW FIle
    cout<<"Reading the FLOW File\n";
    //vector<string> flowIpandPort = readFLOWFile();
    cout<<"Storing the NAT in Trie\n";
    // Storign the NAT FIle and pairs in a Trie
    root  =storeInTrie(root,readNATFile());
    
    cout<<"Start of FLOW file\n";
    cout<<"Searching for the FLOW pairs\n";
    //Assuming the entries are valid and well formed entries
    // output for the FLOW file in a new OUTPUT file
    outputForFlow(root,readFLOWFile());
   
}
