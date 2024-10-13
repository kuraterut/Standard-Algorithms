#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>


using namespace std;


const int base = 1e6;
const int len_f_naive = 64;
const int dig_size = 10;
const int add_zero = base / dig_size;

vector<long long> standardMul(const vector<long long>& first, const vector<long long>& second) {
    auto len = first.size();
    vector<long long> res(2 * len);
    
    for (auto i = 0; i < len; ++i) {
        for (auto j = 0; j < len; ++j) {
            res[i + j] += first[i] * second[j];
        }
    }
    
    return res;
}

vector<long long> karatsubaMul(const vector<long long>& first, const vector<long long>& second) {
    auto len = first.size();    
    vector<long long> res(2 * len);
    
    if (len <= len_f_naive) {
        return standardMul(first, second);
    }
    
    auto half_len = len / 2;
    
    vector<long long> firstL {first.begin(), first.begin() + half_len};
    vector<long long> firstU {first.begin() + half_len, first.end()};
    vector<long long> secondL {second.begin(), second.begin() + half_len};
    vector<long long> secondU {second.begin() + half_len, second.end()};
    
    vector<long long> slag1 = karatsubaMul(firstU, secondU);
    vector<long long> slag2 = karatsubaMul(firstL, secondL);    
        
    vector<long long> firstUL(half_len);
    vector<long long> secondUL(half_len);
    
    for (auto i = 0; i < half_len; ++i) {
        firstUL[i] = firstU[i] + firstL[i];
        secondUL[i] = secondU[i] + secondL[i];
    }
    
    vector<long long> slag3 = karatsubaMul(firstUL, secondUL);
    
    for (auto i = 0; i < len; ++i) {
        slag3[i] -= slag2[i] + slag1[i];
    }
    
    for (auto i = 0; i < len; ++i) {
        res[i] = slag2[i];
    }

    for (auto i = len; i < 2 * len; ++i) {
        res[i] = slag1[i - len];
    }

    for (auto i = half_len; i < len + half_len; ++i) {
        res[i] += slag3[i - half_len];
    }
    
    return res;
}

vector<long long> strToVec(string& str_num, bool& neg) {
    
    vector<long long> vec_num;
    unsigned int dig = 1;
    int n = 0;
    
    
    auto beg = str_num.crbegin();
    auto end = str_num.crend();
    if(str_num[0] == '-'){
        end--;
        neg = true;
    }
    else{
        neg = false;
    }
    for (auto it = beg; it != end; ++it) {
        
        n += (*it - '0') * dig;
        dig *= dig_size;
        
        if (dig == base) {
            vec_num.push_back(n);
            n = 0;
            dig = 1;
        }
    }
    
    if (n != 0) {
        vec_num.push_back(n);
    }
    
    return vec_num;
}

void extendVec(vector<long long>& vec, size_t len) {    
    while (len & (len - 1)) {
        ++len;
    }
    
    vec.resize(len);
}

void finalize(vector<long long>& res) {
    for (auto i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / base;
        res[i] %= base;
    }
}

void printResult(const vector<long long>& v, const bool& neg) {
    auto it = v.crbegin();
    
    if (neg){cout<<"-";}
    
    while (!*it) {
        ++it;
    }
    
    bool flag = false;
    while (it != v.crend()) {
        int z = -1;
        auto num = *it;
        
        if (num == 0) {
            num += 1;
        }
        
        if (num < add_zero) {
            z = 1;         
            
            while ((num *= dig_size) < add_zero) {
                ++z;
            }
        }
        
        if (z > 0) {
            if(!flag){flag = true;}
            else{
                while (z--) {    
                    cout << '0';
                }
            }

        }
        cout << *it++;
    }
    
    cout << endl;
}

void printVec(const vector<long long>& v) {
    size_t pos = 0;
    for (auto& i : v) {
        cout << "v[" << pos++ << "]: " << i << endl;
    }
}


int main() {
    vector<long long> first, second;
    vector<long long> res;
    

    std::string first_str;
    std::string second_str;
    std::cin >> first_str;
    std::cin >> second_str;    
    if(first_str == "0" || second_str == "0"){
        cout << 0 << endl;
        return 0;
    }

    bool neg1, neg2, res_neg;
    
    
    first = strToVec(first_str, neg1);
    second = strToVec(second_str, neg2);

    res_neg = neg1^neg2;

    auto max_len = max(first.size(), second.size());
    
    extendVec(first, max_len);
    extendVec(second, max_len);
    // printVec(first);
    
    
    res = karatsubaMul(first, second);
    finalize(res);
    
    
    

    printResult(res, res_neg);
    
    
    return 0;
}