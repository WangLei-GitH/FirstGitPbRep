// HashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<unordered_map>
#include<numeric>
#include <iomanip>
#include <utility>
#include <iterator>
#include <typeinfo>
using namespace std;

template<typename T1,typename T2>
std::ostream& operator <<(std::ostream& strm, const std::pair<T1, T2>& pVal)
{
    return strm << "["<<pVal.first << "," << pVal.second << "]";
}
template<typename T>
void printHashTableState(const T& cont)
{
    cout << "Size:                " << cont.size() << "\n";
    cout << "Max Size:            " << cont.max_size() << endl;
    cout << "buckets:             " << cont.bucket_count() << "\n";
    cout << "load factor:         " << cont.load_factor() << "\n";
    cout << "max load facotr:     " << cont.max_load_factor() << "\n";

    if (typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
        ==typeid(std::bidirectional_iterator_tag))
    {
		cout << "chaining style:    doubly-linked" << "\n";
    }
    else
    {
		cout << "chaining style:    singly-linked" << "\n";
    }

    cout << "data:    " << endl;

    for (auto idx =0;idx!=cont.bucket_count();++idx)
    {
        cout << "b[" << std::setw(2) << idx << "]:";
        for (auto pos=cont.begin(idx);pos!=cont.end(idx);++pos)
        {
            cout << *pos << " ";
        }
        cout << endl;
    }

	cout << endl;
}
// int main()
// {
//     std::unordered_map<string, string> dict = {
//         {"day","Tag"},
//         {"strange","fremd"},
//         {"car","Auto"},
//         {"smart","elegant"},
//         {"trait","Merkmal"},
//         {"strange","seltsam"}
//     };
// 
//     printHashTableState(dict);
// 
// 	std::cout << "Hello World!\n\n";
// 
//     dict.insert({
//         {"smart","raffiniert"},
//         {"smart","klug"},
//         {"clever","raffiniert"}
//         });
//     printHashTableState(dict);
// 
//     std::cout << "Hello World!\n\n";
//     dict.max_load_factor(0.7f);
//     printHashTableState(dict);
//     cout << dict.find("smart") << endl;
// }
