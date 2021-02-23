
#include"Suffix.h"


int main(){
    
    std::string input;
    input = "mississi$";
    //std::cin >> input;
    PrintableSuffixTree st;


    st.buildTree(input);
    /*
    st += "aad";
    
    cout << endl << endl;
    st.print();

    st += '$';

    cout << endl << endl;*/
    //st.print();

    // std::cout<<"\nHELLOW";

    return 0;
}

