#include <iostream>
#include "widget.h"
#include "blob.h"
#include "blobptr.h"
using namespace std;

extern template class Blob<string>;

int main ()
{
    Blob<string> articles= {"a", "an", "the"};
    //articles.pop_back();
    cout<<"articles: "<<articles<<endl;

    Blob<int> squares{0,1,2,3,4,5,6,7,8,9};
    for (size_t i = 0; i != squares.size(); ++i)
        squares[i] = i*i;
    cout<<"squares: "<<squares<<endl;

    Widget::twin<int> nTwin(10,20);
    cout<<nTwin.first<<" "<<nTwin.second<<endl;

    vector<int> vi = {1, 2, 3, 4, 5};
    auto &i = fcn(vi.begin(), vi.end());
    auto t = fcn2(vi.begin(), vi.end());
    cout<<i<<" "<<t<<endl;

    //Variadic Function Template
    int n = 0; double d = 3.14; string s = "how now brown cow";
    print(cout, n, s, 42);

    return 0;
}

