
#include"Suffix.h"


int main(){
    using namespace std;
    std::string input;
    input = "mississi$";

    PrintableSuffixTree st;

    st += "mississi$";

    cout << "\n\n\n";

    st.print();


    return 0;
}

