// constexpr i64 P = 998244353;
// 
// i64 qpow(i64 a, i64 b) {
//     i64 res = 1;
//     while(b) {
//         if(b & 1) {
//             res = res * a % P;
//         }
//         b >>= 1;
//         a = a * a % P;
//     }
//     return res;
// }
// 
// TODO: 任意模数
// void NTT(std::vector<i64> A, int opt = 1) {
//     int n = A.size();
//     std::vector<int> p(n);
//     for(int i = 0; i < n; ++i) {
//         p[i] = p[i / 2] / 2 + (n / 2) * (i & 1);
//     }
//     for(int i = 0; i < n; ++i) {
//         if(i < p[i]) {
//             std::swap(A[i], A[p[i]]);
//         }
//     }
//     const int G = 3;
//     const int INVG = 332748118;
//     for(int len = 2; len <= n; len <<= 1) {
//         i64 g1 = qpow(opt == 1 ? G : INVG, (P - 1) / len);
//         for(int i = 0; i < n; i += len) {
//             i64 gk = 1;
//             for(int j = 0; j < len / 2; ++j) {
//                 i64 x = A[j];
//                 i64 y = A[j + len / 2] * gk % P;
//                 A[i + j] = x + y;
//                 A[i + j + len / 2] = x - y;
//                 gk = (gk * g1) % P;
//             }
//         }
//     }
// }