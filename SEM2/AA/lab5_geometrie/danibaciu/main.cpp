/*
 * ------------------------------------------------------------------------
 * test orientare
 */
//#include <iostream>
//
//int main() {
//    long long n, ax, ay, bx, by, cx, cy;
//    std::cin >> n;
//    for (int i = 0; i < n; i++) {
//        std::cin >> ax >> ay >> bx >> by >> cx >> cy;
//        long long viraj = bx * cy + ax * by + cx * ay - (bx * ay + cx * by + ax * cy);
//        if (viraj > 0)
//            std::cout << "LEFT" << std::endl;
//        else {
//            if (viraj < 0)
//                std::cout << "RIGHT" << std::endl;
//            else
//                std::cout << "TOUCH" << std::endl;
//        }
//
//    }
//    return 0;
//}



/*------------------------------------------------------------------------
 * roby
 */

//#include <iostream>

//int viraje[3];
//
//void viraj(int ax, int ay, int bx, int by, int cx, int cy) {
//    int viraj = bx * cy + ax * by + cx * ay - (bx * ay + cx * by + ax * cy);
//    if (viraj > 0)
//        viraje[0] += 1;
//    else {
//        if (viraj < 0)
//            viraje[1] += 1;
//        else
//            viraje[2] += 1;
//    }
//}
//
//int main() {
//    int n, xfirst, yfirst, xsecond, ysecond, x1, x2, x3, y1, y2, y3;
//    std::cin >> n;
//    std::cin >> xfirst >> yfirst >> xsecond >> ysecond;
//    x1 = xfirst, x2=xsecond, y1 = yfirst, y2 = ysecond;
//
//    for (int i = 2; i < n; i++) {
//        std::cin >> x3 >> y3;
//        viraj(x1, y1, x2, y2, x3, y3);
//        x1 = x2;
//        x2 = x3;
//        y1 = y2;
//        y2 = y3;
//    }
//    viraj(x1, y1, x2, y2, xfirst, yfirst);
//    for (int i = 0; i <= 2; i++)
//        std::cout << viraje[i] << "  ";
//    return 0;
//}



/*------------------------------------------------------------------------
 * punct in poligon convex
 */

//#include <iostream>
//#include <vector>
//
//long long viraj(std::pair<long long, long long> a, std::pair<long long, long long> b, long long cx, long long cy) {
//    long long viraj = b.first * cy + a.first * b.second + cx * a.second - (b.first * a.second + cx * b.second + a.first * cy);
//    if (viraj > 0)
//        return 1;
//    else {
//        if (viraj < 0)
//            return -1;
//        else
//            return 0;
//    }
//}
//
//int main() {
//    long long n, x1, xr, y1, yr, m, pct = 7;
//    std::vector<std::pair<long long, long long>> points;
//
//    std::cin >> n;
//
//    for (int i = 0; i < n; i++) {
//        std::cin >> x1 >> y1;
//        points.emplace_back(std::make_pair(x1, y1));
//    }
//
//    std::cin >> m;
//
//    for (int p = 0; p < m; p++) {
//        std::cin >> xr >> yr;
//        for (int k = 0; k < n; k++) {
//            pct = viraj(points[k], points[(k + 1) % n], xr, yr);
//            if (pct < 0 or pct == 0)
//                break;
//        }
//        if (pct > 0) {
//            std::cout << "INSIDE\n";
//        } else {
//            if (pct < 0)
//                std::cout << "OUTSIDE\n";
//            else
//                std::cout << "BOUNDARY\n";
//        }
//    }
//    return 0;
//}





/*------------------------------------------------------------------------
 * acoperire convexa in o(n)
 */

// test :
/*

10
5 0
4 1
4 -1
3 0
2 1
2 0
2 -1
1 1
1 -1
0 0

 */

//#include <iostream>
//#include <vector>
//
//int viraj(std::pair<long long, long long> a, std::pair<long long, long long> b, std::pair<long long, long long> c) {
//    long long viraj = b.first * c.second + a.first * b.second + c.first * a.second - (b.first * a.second + c.first * b.second + a.first * c.second);
//    if (viraj < 0)
//        return 1;
//    else {
//        if (viraj > 0)
//            return -1;
//        else
//            return 0;
//    }
//}
//
//int main(){
//    long long n, x, y;
//    std::vector<std::pair<long long, long long>> points;
//    std::vector<int> sus, jos;
//
//    std::cin >> n;
//
//    for (int i = 0; i < n; i++) {
//        std::cin >> x >> y;
//        points.emplace_back(x, y);
//    }
//
//    sus.push_back(0);
//    jos.push_back(0);
//    /*
//     * ideea e ca eu plec din dreapta si in sus si in jos cu frontiera pana ajung la punctul n
//     * in stiva tin minte indici
//     */
//
//    for (int i = 1; i < n; i++) {
//
//        while (sus.size() >= 2 and viraj(points[sus[sus.size() - 2]], points[sus[sus.size() - 1]], points[i]) == 1) {
//            sus.pop_back();
//        }
//        sus.push_back(i);
//
//        while (jos.size() >= 2 and viraj(points[jos[jos.size() - 2]], points[jos[jos.size() - 1]], points[i]) == -1) {
//            jos.pop_back();
//        }
//        jos.push_back(i);
//    }
//
//
//
//    for (auto &nr : sus) {
//        std::cout << "punctul numarul " << nr << " face parte din acoperirea convexa pe partea de sus" << std::endl;
//    }
//
//    std::cout << "\n----------------------------------------\n";
//
//    for (auto &nr : jos) {
//        std::cout << "punctul numarul " << nr << " face parte din acoperirea convexa pe partea de jos" << std::endl;
//    }
//
//
//    return 0;
//}
