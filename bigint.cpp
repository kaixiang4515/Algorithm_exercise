//#include <iostream>
//#include <cstdio>
#include <bits/stdc++.h>
#define Inf 0x3f3f3f3f
#define NeInf 0xc0c0c0c0

using namespace std;

struct bigint{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s;

    bigint(long long n = 0){ *this = n; }
    bigint(const string& str){ *this = str; }

    void Resize(){
        int i = s.size() - 1;
        while(!s[i] && i) --i;
        if(i != s.size() - 1) s.resize(i+1);
    }

    int GetLen() const{
        int len = 0, t = s.back();
        while(t > 0){
            ++len;
            t /= 10;
        }
        if(s.size() > 1) len += (s.size() - 1) * WIDTH;
        return len;
    }

	bigint& operator = (long long n){
        s.clear();
        do{
            s.push_back(n % BASE);
            n /= BASE;
        }while(n);
        return *this;
    }

    bigint& operator = (const string& str){
        s.clear();
        int len = (str.length() - 1) / WIDTH + 1;
        for(int i = 0;i < len;++i){
            int End = str.length() - i * WIDTH, Start = max(0,End - WIDTH), a=0;
            for(int j = Start;j < End;++j) a = a * 10 + str[j] - '0';
            s.push_back(a);
        }
        return *this;
    }

    bigint& operator = (const bigint& b){
        s.clear();
        for(int i = 0;i < b.s.size();++i)
            s.push_back(b.s[i]);
        return *this;
    }

    bigint operator + (const bigint& b) const{
        int t = 0, i;
        bigint a = *this;
        for(i = 0;i < b.s.size();++i){
            if(i >= a.s.size()) a.s.push_back(0);
            a.s[i] += b.s[i] + t;
            t = a.s[i] / BASE;
            a.s[i] %= BASE;
        }
        while(t){
            if(i >= a.s.size()) a.s.push_back(0);
            a.s[i] += t;
            t = a.s[i] / BASE;
            a.s[i++] %= BASE;
        }
        return a;
    }

    bigint& operator += (const bigint& b){
        *this = *this + b;
        return *this;
    }

    bigint operator - (const bigint& b) const{
        bigint x,y;
        bool f=1;
        if(*this == b){
            return bigint(0);
        }
        else if(*this > b){
            x = *this, y = b;
        }
        else{
            x = b, y = *this;
            f=0;
        }
        int t = 0;
        for(int i = 0; ;++i){
            if(!t && i >= y.s.size()) break;
            if(i < y.s.size()) x.s[i] -= y.s[i];
            x.s[i] -= t;
            t = 0;
            if(x.s[i] < 0){ x.s[i] += BASE; t = 1; }
        }
        x.Resize();
        if(!f) x.s[ x.s.size() - 1 ] *= -1;
        return x;
    }

    bigint& operator -= (const bigint& b){
        *this = *this - b;
        return *this;
    }

    bigint operator * (const bigint& b) const{
        bigint c = 0;
        for(int j = 0;j < b.s.size();++j){
            long long t = 0;
            int i;
            for(i = 0;i < s.size();++i){
                while(i+j >= c.s.size()) c.s.push_back(0);
                long long a = 1LL * s[i] * b.s[j] + t;
                t = (1LL * c.s[i+j] + a) / BASE;
                c.s[i+j] = (1LL * c.s[i+j] + a) % BASE;
            }
            while(t){
                if(i+j >= c.s.size()) c.s.push_back(0);
                long long a = (1LL * c.s[i+j] + t);
                t = a / BASE;
                c.s[i+j] = a % BASE;
                ++i;
            }
        }
        return c;
    }

    bigint& operator *= (const bigint& b){
        *this = *this * b;
        return *this;
    }

    bigint operator / (const bigint& b) const{ //¨ú°Ó
        if(*this < b) return bigint(0);
        else if(*this == b) return bigint(1);
        else{
            bigint c;
            int ex = (*this).GetLen() - b.GetLen();

            bigint q(0), a = *this, t = bigint(10);
            bigint k[ex+1];
            k[0] = bigint(1);
            for(int j = 1;j <= ex;++j) k[j] = k[j-1] * t;
            c = b * k[ex];

            while(1){
                if(a >= c){
                    a -= c;
                    q += k[ex];
                }
                else{
                    if(ex == 0) break;
                    c = b * k[--ex];
                }
            }
            return q;
        }
    }

    bigint& operator /= (const bigint& b){
        *this = *this / b;
        return *this;
    }

    bool operator < (const bigint& b) const{
        if(s.size() != b.s.size()) return s.size() < b.s.size();
        for(int i = s.size() - 1;i >= 0;--i)
            if(s[i] != b.s[i]) return s[i] < b.s[i];
        return 0; //相等
    }
    bool operator > (const bigint& b) const{
        return b < *this;
    }
    bool operator <= (const bigint& b) const{
        return !(*this > b);
    }
    bool operator >= (const bigint& b) const{
        return !(*this < b);
    }
    bool operator != (const bigint& b) const{
        return *this < b || b < *this;
    }
    bool operator == (const bigint& b) const{
        return !(*this < b) && !(b < *this);
    }
};
ostream& operator << (ostream& a, const bigint &b){
    a << b.s.back();
    for(int i = b.s.size() - 2;i >= 0;--i){
        char str[20];
        sprintf(str,"%08d",b.s[i]);
        int len = strlen(str);
        for(int j = 0;j < len;++j) a << str[j];
    }
    return a;
}
istream& operator >> (istream& a, bigint& b){
    string str;
    if(!(a >> str)) return a;
    b = str;
    return a;
}

int main()
{
    //freopen("../file/input_ascii.txt","r",stdin);
    //freopen("../file/output.txt","w",stdout);
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    bigint a,b;
    char ch;
    while(cin >> a >> ch >> b){
        if(ch == '+') cout << a+b << "\n";
        if(ch == '-') cout << a-b << "\n";
        if(ch == '*') cout << a*b << "\n";
        if(ch == '/') cout << a/b << "\n";
    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

