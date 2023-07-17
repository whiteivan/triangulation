#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

struct Polygon{
    vector<pair<double,double>> points,vecs;
    Polygon(vector<pair<double,double>>& p):points(p){
        if (points.size()>2)
        {
            for (size_t i = 0; i != points.size(); i++)
            {
                pair<double,double> temp;
                if (i!=points.size()-1)
                {
                    temp.first = points[i].first + points[i+1].first;
                    temp.second = points[i].second+points[i+1].second;
                }else{
                    temp.first = points[i].first + points[0].first;
                    temp.second = points[i].second+points[0].second;
                }
                vecs.push_back(temp);
            }
        }else{cout<<"Polygon must have 3 points min"<<endl;}        
    }
};

vector<vector<pair<double,double>>> triangulation(vector<vector<pair<double,double>>>& trs,vector<pair<double,double>>& shape ){
    if (shape.size()!=3)
    {
        vector<pair<double,double>> tr;
        pair<double,double> addition_result;
        addition_result.first = shape[0].first+shape[1].first;
        addition_result.second = shape[0].second+shape[1].second;
        tr.push_back(shape[0]); tr.push_back(shape[1]);tr.push_back(addition_result);
        trs.push_back(tr);
        shape.erase(shape.begin());
        shape.erase(shape.begin());
        shape.insert(shape.begin(),addition_result);
        return triangulation(trs,shape);
    }else{
        return trs;
    }
}

double square(Polygon& p){
    vector<vector<pair<double,double>>> triangles;
    vector<pair<double,double>> triangle;
    Polygon shape = p;
    triangles = triangulation(triangles,shape.vecs);
    double square;
    for(auto t : triangles){
        double a,b,c,halfper;
        a = sqrt(pow(t[0].first,2)+pow(t[0].second,2));
        b = sqrt(pow(t[1].first,2)+pow(t[1].second,2));
        c = sqrt(pow(t[2].first,2)+pow(t[2].second,2));
        halfper = (a+b+c)/2;
        square+=sqrt(halfper*(halfper-a)*(halfper-b)*(halfper-c));
    }
    return square;
}

int main(){
    cout<<"Enter the path to file with point coordinates"<<endl;
    vector<pair<double,double>> dots;
    string path;
    cin>>path;
    ifstream inFile(path);
    vector<string> Sdots;
    string Sdot;
    while(getline(inFile,Sdot)){Sdots.push_back(Sdot);}
    vector<pair<double,double>> dotss;
    for (string s : Sdots)
    {
        pair<double,double> dot;
        string ss;
        size_t i = 0;
        while(i!=s.size()+1){
            if(s[i]!=';'&&i!=s.size())  {ss+=s[i];}
            else{
                if (dot.first)
                {dot.second = stof(ss);}
                else{
                    dot.first = stof(ss);
                    ss = string();
                }
            }
            ++i;
        }
        dotss.push_back(dot);
    }
    Polygon p(dotss);
    cout<<"\n"<<square(p);
    return 0;
}