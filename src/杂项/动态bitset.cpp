#include <bits/stdc++.h>
using i64 = long long;

struct dynamic_bitset {
    dynamic_bitset() = default;
    dynamic_bitset(const uint64_t &n) : v(1, n), _count(std::popcount(n)), _size(64) {}
    dynamic_bitset(const int sz, bool bit) {
        resize(sz);
        if(bit) {
            set();
        }
    }
    dynamic_bitset(const std::string &s) {
        resize(s.size());
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '0') continue;
            set(i);
        }
    }

#define blk(x) (x >> 6)
#define idx(x) (x & 63)
    bool operator==(const dynamic_bitset &o) const {
        return _size == o._size && v == o.v;
    }
    bool operator!=(const dynamic_bitset &o) const {
        return !(*this == o);
    }
    dynamic_bitset operator&=(const dynamic_bitset &o) {
        return combine(o, std::bit_and());
    }
    dynamic_bitset operator|=(const dynamic_bitset &o) {
        return combine(o, std::bit_or());
    }
    dynamic_bitset operator^=(const dynamic_bitset &o) {
        return combine(o, std::bit_xor());
    }
    friend dynamic_bitset operator&(dynamic_bitset x, const dynamic_bitset &y) {
        return x &= y;
    }
    friend dynamic_bitset operator|(dynamic_bitset x, const dynamic_bitset &y) {
        return x |= y;
    }
    friend dynamic_bitset operator^(dynamic_bitset x, const dynamic_bitset &y) {
        return x ^= y;
    }

    dynamic_bitset operator~() const {
        dynamic_bitset res;
        res.resize(_size);
        for (size_t i = 0; i < v.size(); ++i) {
            res.v[i] = ~v[i];
        }
        if(!v.empty()) {
            res.v.back() &= get(0, idx(_size - 1));
        }
        res._count = _size - _count;
        return res;
    }
    dynamic_bitset operator>>(int dx) const {
        dynamic_bitset res;
        res.resize(std::max(0, (int)_size - dx));
        for(int i = 0; i < res.v.size() ; ++i) {
            int l = (i << 6) + dx;
            int r = std::min((int)_size - 1, l + 63);
            assert(blk(l) < v.size());
            res.v[i] = (v[blk(l)] >> idx(l)) | (v[blk(r)] << idx(r));
            res._count += std::popcount(res.v[i]);
        }
        res.reset(res._size, (res.v.size() << 6) - 1);
        return res;
    }
    dynamic_bitset operator<<(int dx) const {
        dynamic_bitset res;
        res.resize(_size + dx);
        for(int i = 0; i < v.size(); ++i) {
            int l = (i << 6) + dx;
            int r = std::min((int)res._size - 1, l + 63);
            res.v[blk(l)] |= v[i] << idx(dx);
            res.v[blk(r)] |= v[i] >> (64 - idx(dx));
        }
        res._count = _count;
        return res;
    }

    dynamic_bitset sub(int l, int r) const {
        dynamic_bitset res = *this >> l;
        res.resize(r - l + 1);
        return res;
    }
    bool operator[](const int &pos) const {
        return v[blk(pos)] >> idx(pos) & 1ULL;
    }

    unsigned long to_ulong() const { return v.empty() ? 0 : (unsigned long)v[0]; }
    unsigned long long to_ullong() const { return v.empty() ? 0 : (unsigned long long)v[0]; }
    std::string to_string() const {
        std::string res(_size, '0');
        for(int i = 0; i < _size; ++i) {
            res[i] = '0' + (*this)[i];
        }
        return res;
    }
    void set(int l, int r) {
        update(l, r, [](auto &x, auto mask) { x |= mask; });
    }
    void reset(int l, int r) {
        update(l, r, [](auto &x, auto mask) { x &= ~mask; });
    }
    void flip(int l, int r) {
        update(l, r, [](auto &x, auto mask) { x ^= mask; });
    }
    void set() { set(0, _size - 1); }
    void reset() { reset(0, _size - 1); }
    void flip() { flip(0, _size - 1); }
    void set(int pos) { set(pos, pos); }
    void reset(int pos) { reset(pos, pos); }
    void flip(int pos) { flip(pos, pos); }

    void push_back(bool bit) {
        resize(_size + 1);
        if(!bit) return;
        set(_size - 1);
    }
    void pop_back() {
        resize(_size - 1);
    }

    size_t size() const { return _size; }
    size_t count() const { return _count; }
    size_t num_blocks() const { return v.size(); }
    bool any() const { return _count != 0; }
    bool all() const { return _count == _size; }
    bool none() const { return _count == 0; }

    void resize(size_t sz) {
        if(sz < _size) {
            reset(sz, _size - 1);
        }
        v.resize((sz + 63) / 64);
        _size = sz;
    }

    uint64_t get(int l, int r) const {
        return (~0ULL << l) & (~0ULL >> (63 - r));
    }
    void update(int l, int r, auto func) {
        for(int i = blk(l); i <= blk(r); ++i) {
            _count -= std::popcount(v[i]);
            int bl = i == blk(l) ? idx(l) : 0;
            int br = i == blk(r) ? idx(r) : 63;
            func(v[i], get(bl, br));
            _count += std::popcount(v[i]);
        }
    }
    dynamic_bitset combine(const dynamic_bitset &o, auto func) {
        resize(std::max(_size, o._size));
        _count = 0;
        for(int i = 0; i < v.size(); ++i) {
            v[i] = func(v[i], i < o.v.size() ? o.v[i] : 0ULL);
            _count += std::popcount(v[i]);
        }
        return *this;
    }
    friend std::ostream &operator<<(std::ostream &os, const dynamic_bitset &db){
        for(int i = (int)db.v.size() - 1; i >= 0; --i) {
            if(i + 1 == db.v.size()) {
                for(int j = (int)db._size - 1; j >= i * 64; --j) {
                    os << db[j];
                }
            } else {
                os << std::bitset<64>(db.v[i]);
            }
        }
        return os;
    }
    std::vector<uint64_t> v;
    size_t _count = 0;
    size_t _size = 0;

#undef blk
#undef idx
};

int main() {
    dynamic_bitset A("10"), B("100");
    return 0;
}