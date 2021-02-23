
#include"Suffix.h"


int main(){
    
    std::string input;
    input = "mississi$";
    //std::cin >> input;

    PrintableSuffixTree st;

    /*st += 's';
    st += "mississi$";*/
    st.addStepWise(input);

    st.print();
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

