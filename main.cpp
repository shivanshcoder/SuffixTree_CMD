#include"Suffix.h"
// #include<iostream>
// #include<unordered_map>
// #include<memory>

std::shared_ptr<int>tp;
using namespace std;


struct B{

    virtual void print(){
        cout<<"BB"<<a;
    }
    int a;
};

struct D:public B{

    void print(){
        cout<<"DD"<<da;
    }
    int da;
};


int main(){
    using namespace Second;
    
    cout << (int)' ';
    
    SuffixTree st("aabaacaad$");

    st.print();
    
    // std::cout<<"\nHELLOW";

    return 0;
}

void t(std::shared_ptr<int>ftp){
    tp=ftp;
}
int maisn(){
    using namespace std;
{

    std::shared_ptr<int>mtp=make_shared<int>(123);

    t(mtp);
    cout<<&(*mtp)<<endl;
}

    cout<<&(*tp)<<endl;

    unordered_map<char, int>testing;

    testing['a'] = 123;
    testing['b'] = 12312;
    testing['c'] = 123345;
    testing['d'] = 123123;

    cout<<testing.size()<<endl;


    for(auto &pr: testing){
        cout<<pr.first<<": "<<pr.second<<endl;
    }

    // cout<<endl<<(testing.find('g')!= testing.end());

    return 0;
}
