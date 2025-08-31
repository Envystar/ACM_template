#include <bits/stdc++.h>
using i64 = long long;

// using i128= __int128;
// std::istream&operator>>(std::istream &is,i128 &n){
// 	std::string s;is>>s;
// 	n=0;
// 	for(char i:s) n=n*10+i-'0';
// 	return is;
// }
// std::ostream &operator<<(std::ostream &os,i128 n){
// 	std::string s;
// 	while(n){
// 		s+='0'+n%10;
// 		n/=10;
// 	}
// 	std::reverse(s.begin(),s.end());
// 	return os<<s;
// }

struct Bigint {
    std::string a;
    int sign;
    Bigint() {}
    Bigint(std::string b) {
        (*this) = b;
    }
    int size() {
        return a.size();
    }
    Bigint normalize(int newSign) { //removes leading 0, fixes sign (base)
        for(int i = a.size() - 1; i > 0 && a[i] == '0'; --i) {
            a.erase(a.begin() + i);
        }
        sign = (a.size() == 1 && a[0] == '0') ? 1 : newSign;
        return (*this);
    }
    void operator=(std::string b) {
        a = b[0] == '-' ? b.substr(1) : b;
        reverse(a.begin(), a.end());
        this->normalize(b[0] == '-' ? -1 : 1);
    }
    bool operator<(const Bigint &b) const {
        if(sign != b.sign) {
            return sign < b.sign;
        }
        if(a.size() != b.a.size()) {
            return sign == 1 ? a.size() < b.a.size() : a.size() > b.a.size();
        }
        for(int i = a.size() - 1; i >= 0; --i) {
            if(a[i] != b.a[i]) {
                return sign == 1 ? a[i] < b.a[i] : a[i] > b.a[i];
            }
        }
        return false;
    }
    bool operator==(const Bigint &b) const {
        return (a == b.a && sign == b.sign);
    }
    bool operator!=(const Bigint &b) const {
        return !operator==(b);
    }
    Bigint operator+(Bigint b) {
        if(sign != b.sign) {
            return (*this) -  (-b); //don't modify here
        }
        Bigint c;
        for(int i = 0, carry = 0; i < a.size() || i < b.size() || carry; ++i) {
            carry += (i < a.size() ? a[i] - 48 : 0) + (i < b.a.size() ? b.a[i] - 48 : 0);
            c.a += (carry % 10 + 48);
            carry /= 10;
        }
        return c.normalize(sign);
    }
    Bigint operator-() {
        sign *= -1;
        return (*this);
    }
    Bigint operator-(Bigint b) {
        if(sign != b.sign) {
            return (*this) + (-b);
        }
        int s = sign; sign = b.sign = 1;
        if((*this) < b) {
            return (b - (-(*this))).normalize(-s);
        }
        Bigint c;
        for(int i = 0, borrow = 0; i < a.size(); ++i) {
            borrow = (a[i] - borrow - (i < b.size() ? b.a[i] : 48));
            c.a += (borrow >= 0 ? borrow + 48 : borrow + 58);
            borrow = (borrow >= 0 ? 0 : 1);
        }
        return c.normalize(s);
    }
    Bigint operator*(Bigint b) {
        Bigint c("0");
        for(int i = 0, k = a[i] - 48; i < a.size(); ++i, k = a[i] - 48) {
            while(k--) c = c + b;
            b.a.insert(b.a.begin(), '0');
        }
        return c.normalize(sign * b.sign);
    }
    Bigint operator/(Bigint b) {
        assert(b != Bigint("0"));
        if(b.size() == 1 && b.a[0] == '0') {
            b.a[0] /= (b.a[0] - 48);
        }
        Bigint c("0"), d;
        for(int j = 0; j < a.size(); ++j) {
            d.a += "0";
        }
        int dSign = sign * b.sign; b.sign = 1;
        for(int i = a.size() - 1; i >= 0; --i) {
            c.a.insert( c.a.begin(), '0');
            c = c + a.substr( i, 1 );
            while(!(c < b)) {
                c = c - b, d.a[i]++;
            }
        }
        return d.normalize(dSign);
    }
    Bigint operator%(Bigint b) {
        assert(b != Bigint("0"));
        if(b.size() == 1 && b.a[0] == '0') {
            b.a[0] /= (b.a[0] - 48);
        }
        Bigint c("0");
        b.sign = 1;
        for(int i = a.size() - 1; i >= 0; --i) {
            c.a.insert(c.a.begin(), '0');
            c = c + a.substr(i, 1);
            while(!( c < b )) c = c - b;
        }
        return c.normalize(sign);
    }
    friend std::istream& operator>>(std::istream &is, Bigint &integer) {
        std::string input;
        is >> input;
        integer = input;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const Bigint& integer) {
        if (integer.sign == -1) {
            os << "-";
        }
        for (int i = integer.a.size() - 1; i >= 0; --i) {
            os << integer.a[i];
        }
        return os;
    }
};

int main() {
    Bigint a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
    std::cout << a - b << '\n';
    std::cout << a * b << '\n';
    std::cout << a / b << '\n';
    std::cout << a % b << '\n';
    std::cout << (a == b ? "" : "not ") << "equal\n";
    std::cout << "a is " << (a < b ? "" : "not") << "smaller than b\n";
    std::cout << "the max number is:" << std::max(a, b) << '\n';
    std::cout << "the min number is:" << std::min(a, b) << '\n';
    return 0;
}