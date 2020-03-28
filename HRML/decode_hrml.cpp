#include "decode_hrml.h"

Decode_HRML::Decode_HRML()
{
    cout<<"Enter number of HRML & number of Queries, space separated. "<<endl;
    cin>>m_HRML_length>>m_queryLength;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"HRML lines: "<<m_HRML_length<<" #Queries :"<<m_queryLength<<endl;

    inputHRML();
    inputQueries();
    decodeHRML();
    querySolution();


}

void Decode_HRML::inputHRML()
{
    //console input
    cout<<"------------Input HRML------------"<<endl;
    for(int i=0; i<m_HRML_length;i++){
        string str;
        getline(cin, str);
        if(str.size()>0){
            mVect_HRML.push_back(str);
        }
    }
    cout<<"-----------------------------------"<<endl;
    //console output
    cout<<"------------Print HRML------------"<<endl;
    for(auto j=mVect_HRML.begin(); j < mVect_HRML.end();j++){
        cout<<*j<<endl;
    }
    cout<<"-----------------------------------"<<endl;
}

void Decode_HRML::inputQueries()
{
    //console input
    cout<<"------------Input Query------------"<<endl;
    for(int i=0;i<m_queryLength;i++){
        string str;
        getline(cin, str);
        if(str.size()>0){
            mVect_Query.push_back(str);
        }
    }
    cout<<"-----------------------------------"<<endl;
    //console output
    cout<<"------------Print Query------------"<<endl;
    for(auto j=mVect_Query.begin(); j < mVect_Query.end();j++){
        cout<<*j<<endl;
    }
    cout<<"-----------------------------------"<<endl;
}

void Decode_HRML::decodeHRML()
{
    //Decode HRML
    vector<string> vect_tag;
    cout<<"------------DECODE HRML-------------"<<endl;
    for(auto i=mVect_HRML.begin(); i!=mVect_HRML.end();i++){
        string s_line = *i;
        cout<<"----Decode ## :"<<s_line<<endl;
        if(s_line.length()>2 && s_line[0]=='<' && s_line[s_line.length()-1]=='>' && s_line[1]!='/'){
            //START TAG
            cout<<"***START TAG***"<<endl;
            string s_tag="", s_attribute="",s_val="",s_temp="";
            bool isAttributeVal=false;
            map<string,string> map_TagAttribute;
            for(auto j=s_line.begin();j!=s_line.end();++j){
                if(*j!='<' && *j!='>' && *j!=' ' && *j!='"' && *j!='='){
                    //SAVE CHARACTERS
                    s_temp.push_back(*j);
                }else if((*j == ' ' || *j=='>') && s_tag.length()==0 &&s_temp.length() >0){
                    //TAG
                    s_tag=s_temp;
                    vect_tag.push_back(s_tag);
                    s_temp.clear();
                }else if(*j==' ' && s_tag.length()>0 && s_attribute.length()==0 && s_temp.length()>0){
                    //ATTRIBUTE
                    s_attribute=s_temp;
                    s_temp.clear();
                }else if((*j=='"'|| isAttributeVal) && s_tag.length()>0 && s_attribute.length()>0 && s_val.length()==0 && s_temp.length()>0){
                    //ATTRIBUTE VALUE
                    s_val=s_temp;
                    map_TagAttribute.insert(pair<string,string>(s_attribute,s_val));
                    s_temp.clear();
                    s_attribute.clear();
                    s_val.clear();
                    isAttributeVal=false;
                }else if(*j=='='){
                    isAttributeVal=true;
                }
            }

            //TAG SUB CHILD
            string s_TagString;
            for(auto k=vect_tag.begin();k!=vect_tag.end();++k){
                s_TagString.append(*k);
                s_TagString.push_back('.');
            }
            if(s_TagString.length()>1){s_TagString.pop_back();}
            cout<<"TAG :"<<s_TagString<<endl;

            //MAP ATTRIBUTES AND VALUES
            for(auto l=map_TagAttribute.begin();l!=map_TagAttribute.end();++l){
                cout<<"Key: "<<(*l).first<<" #Value: "<<(*l).second<<endl;
                string s_attributeTemp= s_TagString;
                s_attributeTemp.push_back('~');
                s_attributeTemp.append((*l).first);
                mMapHRML.insert(pair<string,string>(s_attributeTemp,(*l).second));
            }
        }else if(s_line.length()>2 && s_line[0]=='<' && s_line[s_line.length()-1]=='>' && s_line[1]=='/'){
            //END TAG
            cout<<"***END TAG***"<<endl;
            if(vect_tag.size()>0){
                vect_tag.pop_back();
            }
        }
    }
    cout<<"------------PRINT DECODED DATA----------"<<endl;
    for(auto m=mMapHRML.begin();m!=mMapHRML.end();++m){
        cout<<"key :"<<(*m).first<<" #val :"<<(*m).second<<endl;
    }
    cout<<"------------DECODE HRML END-------------"<<endl;
}

void Decode_HRML::querySolution()
{
    cout<<"------------QUERY SOLUTION------------"<<endl;
    for(auto i=mVect_Query.begin();i!=mVect_Query.end();++i){
        string s_query=*i;
        if(mMapHRML.find(s_query)!=mMapHRML.end()){
            cout<<mMapHRML.at(s_query)<<endl;
        }else{
            cout<<"Not Found!"<<endl;
        }
    }
}

