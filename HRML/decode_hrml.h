#ifndef DECODE_HRML_H
#define DECODE_HRML_H
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <string>

using namespace std;
class Decode_HRML
{
public:
    Decode_HRML();
    void inputHRML();
    void inputQueries();
    void decodeHRML();
    void querySolution();
private:
    int m_HRML_length=0;
    int m_queryLength=0;
    vector<string> mVect_HRML;
    vector<string> mVect_Query;
    map<string,string> mMapHRML;
};

#endif // DECODE_HRML_H
