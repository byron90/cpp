/*
 * =====================================================================================
 *
 *       Filename:  setover.cpp
 *
 *    Description:  最小集合覆盖问题
 *
 *        Version:  1.0
 *        Created:  04/22/2015 00:33:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Byron 
 *   Organization:  
 *
 * =====================================================================================
 */


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

int main()
{
    
    cout<<"usage: Input the array in one line, array items separated by space."<<endl;
    cout<<"Every line end with 00"<<endl;
    cout<<"Example: "<<endl;
    cout<<"a b c d e f 00"<<endl;
    cout<<"a c d 00"<<endl;
    cout<<"1 3 5 6 00"<<endl;
    cout<<"00"<<endl;
    cout<<endl;
    
    cout<<"Your inputting: "<<endl;
    vector< vector<string> > vvstrInput; // 数组的存放点
    while(1)
    {
        vector<string> vstrTemp;
        string strTemp;
        while (cin >> strTemp)
        {
            if(strTemp == "00") break;
            vstrTemp.push_back(strTemp);
        }
        if(vstrTemp.size() == 0)
        {
            break;
        }
        vvstrInput.push_back(vstrTemp);
    }

    // 统计各个数组元素分别在哪些数组中岀现
    // 如:
    // array 1: (a, b, c, d)
    // array 2: (a, 1)
    // array 3: (b, 2)
    // 统计后结果为:
    // a, {1, 2}
    // b, {1, 3}
    // c, {1}
    // d, {1}
    // 1, {2}
    // 2, {3}
    // 数字代表数组的编号
    map<string, set<int> > mapCollection;
    int iIndex, iTemp;
    for(iIndex=0; iIndex<vvstrInput.size(); iIndex++)
    {
        for(iTemp=0; iTemp<vvstrInput[iIndex].size(); iTemp++)
        {
            string strKey = vvstrInput[iIndex][iTemp];
            map<string, set<int> >::iterator iteCollection;
            iteCollection = mapCollection.find(strKey);
            if(iteCollection == mapCollection.end())
            {
                set<int> setTemp;
                setTemp.insert(iIndex);
                mapCollection.insert(pair<string, set<int> >(strKey, setTemp));
            }
            else
            {
                iteCollection->second.insert(iIndex);
            }
        }
    }
    
    cout<<endl;

    // 最小集合覆盖的贪心算法
    int iItemCount = vvstrInput.size();
    vector<string> vstrResult;
    set<int> setUnionResult;
    while(setUnionResult.size() != iItemCount)
    {
        set<int> setUnionMax = setUnionResult;
        string strKey;
        map<string, set<int> >::iterator iteMap = mapCollection.begin();
        for(;iteMap!=mapCollection.end(); iteMap++)
        {
            set<int> setTemp;
            set_union(setUnionResult.begin(), setUnionResult.end(),
                iteMap->second.begin(), iteMap->second.end(),
                inserter(setTemp, setTemp.begin())); 
            if(setTemp.size() > setUnionMax.size())
            {
                setUnionMax = setTemp;
                strKey = iteMap->first;
            }
        }
        
        setUnionResult = setUnionMax;
        vstrResult.push_back(strKey);
        mapCollection.erase(mapCollection.find(strKey));
    }
    
    cout<<"One best result is : "<<endl;
    vector<string>::iterator iteKeys = vstrResult.begin();
    for(; iteKeys!=vstrResult.end(); iteKeys++)
        cout<<*iteKeys<<" ";
    cout<<endl;

    return 0; 
}

