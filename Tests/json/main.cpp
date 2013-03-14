#include <iostream>
#include <fstream>
#include <string>
using namespace std; 

#include "json.h"

int ParseJsonFromFile(const char* filename)  
{  
    std::ifstream is;  
    is.open (filename);
    string temp_text;
    string out_text;
    
    if(is.is_open())
    {
        while(is>>temp_text) 
        { 
            out_text += temp_text; 
        } 
        cout << out_text<<endl;
    }
    is.close();
    /*
    Json::Reader reader;  
    Json::Value root;  
    if (reader.parse(out_text, root))  
    {  
        //string upload_id = root["uploadid"].asString();  
        //int code = root["code"].asInt(); 
    }  
    */
    return 0;  
}  

int main() {
    ParseJsonFromFile("jddata.json");
	return 0;
}
