#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include "decode_hrml.h"
using namespace std;
int main(){
    Decode_HRML DHobj;
    return 0;
}
int main_2() {
    int N=0, Q=0;
    vector<string> vect_HRML, vect_Query;
    cin>>N>>Q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"N :"<<N<<" #Q :"<<Q;
    string str="";
    for(int i=0;i<N;i++){
        cout<<i<<". input"<<endl;
        getline(cin, str);
        if(str.size()>0){
            vect_HRML.push_back(str);
        }
        cout<<i<<". "<<str<<endl;
        str="";
    }
    cout<<"------------------------------------------INPUT END"<<endl;
    cout<<"Query :"<<endl;
    for(int m=0;m<Q;m++){
        getline(cin, str);
        if(str.size()>0){
            vect_Query.push_back(str);
        }
        cout<<m<<". "<<str<<endl;
        str="";
    }
    cout<<"------------------------------------------QUERY END"<<endl;

    cout<<"HRML ::"<<endl;
    vector<string> vect_tag;
    map<string,string> map_hrml;
    for(auto j=vect_HRML.begin(); j<vect_HRML.end();j++){
        string str = *j;
        if(str.length()>2 && str[0] == '<' && str[str.length()-1] == '>'&& str[1]!='/'){
            //START TAG
            cout<<"START TAG"<<endl;
            string s_tag="";
            string s_attribute="";
            string s_value="";
            string s_temp="";
            map<string,string> map_temp2;
            for(auto y=str.begin();y < str.end(); y++){
                if(*y != '<' && *y != '>' && *y != ' ' && *y != '=' && *y != '"'){
                    s_temp.push_back(*y);
                }else if(*y == ' ' && s_tag.size()==0 &&s_temp.size() >0){
                    s_tag = s_temp;
                    vect_tag.push_back(s_tag);
                    s_temp="";
                }else if(*y == ' ' && s_tag.size() > 0 && s_attribute.size() ==0 && s_temp.size()>0){
                    s_attribute = s_temp;
                    s_temp="";
                }else if(*y == '"' && s_attribute.size()>0 && s_value.size()==0 && s_temp.size()>0){
                    //save to map
                        s_value = s_temp;
                        map_temp2.insert(pair<string,string>(s_attribute,s_value));
                        s_temp="";
                        s_attribute="";
                        s_value="";
                }
            }
            //query answer map
            string str_tempx="";
            for(auto z=vect_tag.begin();z!=vect_tag.end();z++){
                str_tempx.append(*z);
                str_tempx.push_back('.');
            }
            str_tempx.pop_back();

            cout<<endl<<str_tempx<<"-----------Line attribute & value"<<endl;
            for(auto v=map_temp2.begin();v != map_temp2.end();v++){
                cout<<"key :"<<(*v).first<<" #val :"<<(*v).second<<endl;
                string str_tempy = str_tempx;
                str_tempy.push_back('~');
                str_tempy.append((*v).first);
                map_hrml.insert(pair<string,string>(str_tempy,(*v).second));
            }
            cout<<endl<<"--------------------------------"<<endl;

        }else if(str.length()>2 && str[0] == '<' && str[str.length()-1] == '>'&& str[1]=='/'){
            //END TAG
            cout<<"END TAG"<<endl;
            if(vect_tag.size()>0){
            vect_tag.pop_back();
            }
        }else{
            cout<<"INVALID SYNTAX"<<endl;
        }
        cout<<endl<<"----LOOP END-----"<<endl;
    }
    cout<<endl;
    cout<<"--------------------DECODED"<<endl;
    for(auto p=map_hrml.begin();p != map_hrml.end();p++){
        cout<<"key :"<<(*p).first<<" #val :"<<(*p).second<<endl;
    }

    cout<<"--------------------QUERY"<<endl;
    //query: answering
    for(auto n=vect_Query.begin(); n < vect_Query.end(); n++){
        string str_query = *n, str_val = "";
        if(map_hrml.find(str_query)!=map_hrml.end()){
            str_val = map_hrml.at(str_query);
            cout<<str_val<<endl;
        }else{
            cout<<"Not Found!"<<endl;
        }
    }
    return 0;
}

//int main_1() {
//    int N=0, Q=0;
//    vector<string> vect_HRML, vect_Query;
//    cin>>N>>Q;
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    cout<<"N :"<<N<<" #Q :"<<Q;
//    string str="";
//    for(int i=0;i<N;i++){
//        cout<<i<<". input"<<endl;
//        getline(cin, str);
//        if(str.size()>0){
//            vect_HRML.push_back(str);
//        }
//        cout<<i<<". "<<str<<endl;
//        str="";
//    }
//    cout<<"Query :"<<endl;
//    for(int m=0;m<Q;m++){
//        getline(cin, str);
//        if(str.size()>0){
//            vect_Query.push_back(str);
//        }
//        cout<<m<<". "<<str<<endl;
//        str="";
//    }

//    cout<<"HRML ::"<<endl;
//    vector<string> vect_tag;
//    map<string,string> map_hrml;
//    for(auto j=vect_HRML.begin(); j<vect_HRML.end();j++){
//        cout<<*j;
//        string str = *j;
//        if(str.size()>2 && str[0] == '<' && str[str.length()-1] == '>'){
//            cout<<endl<<"valid syntax"<<endl;
//            bool isTagName=false, isAttribute=false, isValue=false, endTag=false;
//            string str_tag="", str_attribute="", str_value="", str_temp="";
//            map<string,string> map_temp;

//            if(str[1] == '/'){
//                endTag = true;
//            }
//            //            0 - 9 == 48 - 57
//            //            A - Z == 65 - 90
//            //            a - z == 97 - 122

//            for(auto k=str.begin(); k < str.end(); k++){
//                int asci_val = int(*k);
//                if((asci_val >= 48 && asci_val <= 57) || (asci_val >= 65 && asci_val <= 90) || (asci_val >= 97 && asci_val <= 122)){
//                    str_temp.push_back(*k);
//                }else if( (*k == ' '|| *k == '>' || *k == '=') && str_temp.size() >0){
//                    if(!isTagName){
//                        str_tag = str_temp;
//                        isTagName = true;

//                    }else if(isTagName && !isAttribute){
//                        str_attribute = str_temp;
//                        isAttribute=true;
//                    }else if(isTagName && isAttribute && !isValue){
//                        str_value = str_temp;
//                        isValue=true;
//                        map_temp.insert(pair<string,string>(str_attribute,str_value));
//                        str_attribute ="";
//                        str_value="";
//                        isAttribute=false, isValue=false;
//                    }
//                    str_temp = "";
//                }

//            }
//            if(!endTag){
//                //start Tag
//                vect_tag.push_back(str_tag);
//                string str_temp2;
//                for(auto l=vect_tag.begin();l<vect_tag.end();l++){
//                    str_temp2.append(*l);
//                    str_temp2.push_back('.');
//                }
//                str_temp2.pop_back();
//                for(auto x=map_temp.begin();x != map_temp.end();x++){
//                    string str_temp3 = str_temp2;
//                    str_temp3.push_back('~');
//                    str_temp3.append((*x).first);
//                    map_hrml.insert(pair<string,string>(str_temp3,(*x).second));
//                }
//            }else if(endTag){
//                //end Tag
//                vect_tag.pop_back();
//            }
//        }else{
//            cout<<"Error: invalid syntax :"<<str<<endl;
//        }
//    }
//    cout<<endl;
//    cout<<"--------------------DECODED"<<endl;
//    for(auto p=map_hrml.begin();p != map_hrml.end();p++){
//        cout<<"key :"<<(*p).first<<" #val :"<<(*p).second<<endl;
//    }

//    cout<<"--------------------QUERY"<<endl;
//    //query: answering
//    for(auto n=vect_Query.begin(); n < vect_Query.end(); n++){
//        string str_query = *n, str_val = "";
//        if(map_hrml.find(str_query)!=map_hrml.end()){
//            str_val = map_hrml.at(str_query);
//            cout<<str_val<<endl;
//        }else{
//            cout<<"Not Found!"<<endl;
//        }
//    }
//    return 0;
//}
