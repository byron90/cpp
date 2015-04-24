/*
 * =====================================================================================
 *
 *       Filename:  setover.cpp
 *
 *    Description:  最小集合覆盖问题
 *
 *        Version:  2.0 启发式算法
 *        Created:  04/23/2015 00:33:54
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
#include <list>
#include <string>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

void DeleteCovered( set<int> setCovered,
                    map<string,set<int> > &mapAppearence,
                    map<int,set<string> > &mapPrototype,
                    set<int> &setFullset )
{
    set<int>::iterator iteToBeDel;
    for(iteToBeDel=setCovered.begin(); iteToBeDel!=setCovered.end(); iteToBeDel++)
    {
        
        map<string, set<int> >::iterator iteAppear;
        iteAppear = mapAppearence.begin();
        while(iteAppear != mapAppearence.end())
        {
            set<int>::iterator iteFound = iteAppear->second.find(*iteToBeDel);
            if(iteFound != iteAppear->second.end())
            {
                iteAppear->second.erase(iteFound);
                if(iteAppear->second.size() == 0)
                {
                    map<string, set<int> >::iterator iteTempDel;
                    iteTempDel = iteAppear;
                    iteAppear++;
                    mapAppearence.erase(iteTempDel);
                    continue;
                }
            }
            iteAppear++;
        }

        map<int, set<string> >::iterator itePrototype;
        itePrototype = mapPrototype.find(*iteToBeDel);
        if(itePrototype != mapPrototype.end())
            mapPrototype.erase(itePrototype);

        set<int>::iterator iteFullset;
        iteFullset = setFullset.find(*iteToBeDel);
        if(iteFullset != setFullset.end())
            setFullset.erase(iteFullset);
    }
}

void DeleteCoveredChar(string strCovered, map<int,set<string> > &mapPrototype)
{
    map<int,set<string> >::iterator itePrototype;
    itePrototype = mapPrototype.begin();
    while(itePrototype != mapPrototype.end())
    {
        set<string>::iterator iteFounder;
        set<string> &setTempStr = itePrototype->second;
        iteFounder = setTempStr.find(strCovered);
        if(iteFounder != setTempStr.end())
            setTempStr.erase(iteFounder);

        itePrototype++;
    }
}

template<class Type>
int CheckSubset(set<Type> &setFirst, set<Type> &setSecond)
{
    set<Type> setIntersec;
    set_intersection(setFirst.begin(), setFirst.end(), 
                    setSecond.begin(), setSecond.end(),
            insert_iterator<set<Type> >(setIntersec,setIntersec.begin()));
    if(setFirst == setIntersec)
        return 1;
    else if(setSecond == setIntersec)
        return 2;
    
    return 0;
}

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
    map<int, set<string> > mapPrototype;
    cout<<endl;
    int iCounter = 0;
    while(1)
    {
        set<string> setTemp;
        string strTemp;
        while (cin >> strTemp)
        {
            if(strTemp == "00") break;
            setTemp.insert(strTemp);
        }
        if(setTemp.size() == 0)
        {
            break;
        }
        mapPrototype.insert(pair<int, set<string> >(iCounter, setTemp));
        iCounter++;
    }

    // 统计各个数组元素分别在哪些数组中岀现
    // 如:
    // array 1: (a, b, c, d)
    // array 2: (a, 1)
    // array 3: (b, 2)
    // 统计后结果为:
    // {a, [1, 2]}
    // {b, [1, 3]}
    // {c, [1]}
    // {d, [1]}
    // {1, [2]}
    // {2, [3]}
    // 数字代表数组的编号
    map<string, set<int> > mapAppearence;
    map<int, set<string> >::iterator itePrototype;
    for(itePrototype=mapPrototype.begin(); itePrototype!=mapPrototype.end(); itePrototype++)
    {
        set<string>::iterator iteStrings;
        set<string> &setStrings = itePrototype->second;
        for(iteStrings=setStrings.begin(); iteStrings!=setStrings.end(); iteStrings++)
        {   
            map<string, set<int> >::iterator iteFounder = mapAppearence.find(*iteStrings);
            if(iteFounder == mapAppearence.end())
            {
                set<int> setIndexTemp;
                setIndexTemp.insert(itePrototype->first);
                mapAppearence.insert(pair<string, set<int> >(*iteStrings, setIndexTemp));
            }
            else
            {
                iteFounder->second.insert(itePrototype->first);
            }
        }
    }

    // 最小集合覆盖的启发式算法
    set<int> setFullset;
    int iElements = mapPrototype.size();
    int iTemp;
    for(iTemp=0; iTemp<iElements; iTemp++)
        setFullset.insert(iTemp);
    
    map<string, set<int> > mapResult;
    while(1)
    {
        if(mapAppearence.size() == 0)
            break;
        
        // step1
        bool bStop = false;
        bool b234 = false;
        
        map<string, set<int> >::iterator iteSubsets;
        for(iteSubsets = mapAppearence.begin(); iteSubsets!=mapAppearence.end(); iteSubsets++)
        {
            if(iteSubsets->second == setFullset)
            {
                mapResult.insert(*iteSubsets);
                bStop = true;
                break;
            }
        }
        if(bStop == true)
            break;
        
        // step2
        map<int, set<string> >::iterator iteSn;
        for(iteSn=mapPrototype.begin(); iteSn!=mapPrototype.end(); iteSn++)
        {
            if(iteSn->second.size() == 1)
            {
                map<string, set<int> >::iterator iteFounder;
                string strTemp = *iteSn->second.begin();
                iteFounder = mapAppearence.find(*iteSn->second.begin());
                mapResult.insert(*iteFounder);
                set<int> setToDel = mapAppearence.find(*iteSn->second.begin())->second;
                DeleteCovered(setToDel, mapAppearence, mapPrototype, setFullset);
                
                b234 = true;
                // 防自杀
                if(mapPrototype.size() == 0)
                {
                    break;
                }
            }
        }

        // step3
        map<string, set<int> >::iterator iteAppear;
        map<string, set<int> >::iterator iteToBeDel;
        iteAppear = mapAppearence.begin();
        while(iteAppear != mapAppearence.end())
        {
            map<string, set<int> >::iterator iteCompared;
            iteCompared = iteAppear;
            iteCompared++;
            bool bIsSubset = false;
            while(iteCompared != mapAppearence.end())
            {
                int iCheck = CheckSubset<int>(iteAppear->second, iteCompared->second);
                if(iCheck == 1)
                {
                    bIsSubset = true;
                    break;
                }
                else if(iCheck == 2)
                {
                    iteToBeDel = iteCompared;
                    string strKey = iteToBeDel->first;
                    iteCompared++;
                    mapAppearence.erase(iteToBeDel);
                    DeleteCoveredChar(strKey, mapPrototype);
                    b234 = true;
                    continue;
                }
                iteCompared++;
            }
            
            if(bIsSubset == true)
            {   
                iteToBeDel = iteAppear;
                string strKey = iteToBeDel->first;
                iteAppear++;
                mapAppearence.erase(iteToBeDel);
                DeleteCoveredChar(strKey, mapPrototype);
                b234 = true;
                continue;
            }

            iteAppear++;
        }

        // step 4
        map<int, set<string> >::iterator itePrototype;
        map<int, set<string> >::iterator iteToBeDelPro;
        itePrototype = mapPrototype.begin();
        while(itePrototype != mapPrototype.end())
        {
            map<int, set<string> >::iterator iteCompared;
            iteCompared = itePrototype;
            iteCompared++;
            bool bIsSupset = false;
            while(iteCompared != mapPrototype.end())
            {
                int iCheck = CheckSubset<string>(itePrototype->second, 
                                                iteCompared->second);
                if(iCheck == 1)
                {
                    set<int> setTempDel;
                    iteToBeDelPro = iteCompared;
                    setTempDel.insert(iteToBeDelPro->first);
                    iteCompared++;
                    mapPrototype.erase(iteToBeDelPro);
                    DeleteCovered(setTempDel, mapAppearence, mapPrototype, setFullset);
                    b234 = true;
                    // 防自杀，下同
                    if(mapPrototype.size() == 0)
                    {
                        break;
                    }
                    
                    continue;
                }
                else if(iCheck ==2)
                {
                    bIsSupset = true;
                    break;
                }
                iteCompared++;
            }
            
            if(mapPrototype.size() == 0)
            {
                break;
            }
            
            if(bIsSupset == true)
            {
                set<int> setTempDel;
                iteToBeDelPro = itePrototype;
                setTempDel.insert(itePrototype->first);
                itePrototype++;
                mapPrototype.erase(iteToBeDelPro);
                DeleteCovered(setTempDel, mapAppearence, mapPrototype, setFullset);
                b234 = true;
                if(mapPrototype.size() == 0)
                {
                    break;
                }
                continue;
            }

            itePrototype++;
        }
        
        // step 5
        if(b234 == true)
            continue;
        else
        {
            map<string, set<int> >::iterator iteAppear;
            map<string, set<int> >::iterator iteMaxBase;
            iteMaxBase = mapAppearence.begin();
            iteAppear = iteMaxBase++;
            while(iteAppear != mapAppearence.end())
            {
                if(iteAppear->second.size() > iteMaxBase->second.size())
                    iteMaxBase = iteAppear;
                
                iteAppear++;
            }
            
            mapResult.insert(*iteMaxBase);
            DeleteCovered(iteMaxBase->second, mapAppearence, mapPrototype, setFullset);
        }
    }
    
    cout<<"One best result is : "<<endl;
    map<string, set<int> >::iterator iteResult;
    for(iteResult=mapResult.begin(); iteResult!=mapResult.end(); iteResult++)
        cout<<iteResult->first<<" ";
    cout<<endl;

    return 0; 
}

