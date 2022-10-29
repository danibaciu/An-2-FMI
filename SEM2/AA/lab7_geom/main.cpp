#include <iostream>

const int max_val = 1000009, min_val = -1000009;

int main() {

    long long n, a, b, c, top_x = max_val, top_y = max_val, bottom_x = min_val, bottom_y = min_val;

    std::cin >> n;

    for (int i = 0; i < n; i++) {

        std::cin >> a >> b >> c;

        if (a == 0) {
            // acum ecuatie e de forma by + c <= 0
            if (b < 0) {
                // acum ecuatia este y >= -c/abs(b)
                bottom_y = std::max(bottom_y, -c / b);
            } else {
                //acum ecuatia e de forma y <= -c/b
                top_y = std::min(top_y, -c / b);
            }
        } else {
            if (b == 0) {
                // acum ecuatie e de forma ax + c <= 0
                if (a < 0) {
                    // acum ecuatia este x >= -c/abs(a)
                    bottom_x = std::max(bottom_x, -c / a);
                } else {
                    //acum ecuatia e de forma x <= -c/a
                    top_x = std::min(top_x, -c / a);
                }
            }
        }
    }

    if (top_y < bottom_y or top_x < bottom_x)
        std :: cout << "VOID";
    else {
        if (top_y == max_val or top_x == max_val or bottom_x == min_val or bottom_y == min_val)
            std :: cout << "UNBOUNDED";
        else
            std :: cout << "BOUNDED";
    }

    return 0;
}

/*
epsilon = 1e-5

inf = 1e10


def vertical_check(plane):
    return plane[0] == 0

n = int(input())

planes = []

for _ in range(n):
    coeffs = input().strip().split(" ")
    planes.append((float(coeffs[0]), float(coeffs[1]), float(coeffs[2])))

m = int(input())

for k in range(m):
    pointCoords = input().strip().split(" ")

    point = [float(pointCoords[0]), float(pointCoords[1])]

    maxim_x, maxim_y = inf, inf
    minim_x, minim_y = -inf, -inf

    for plane in planes:
        if vertical_check(plane):
            if (plane[2] + plane[1] * point[1]) >= 0:
                continue
        else:
            if (plane[2] + plane[0] * point[0]) >= 0:
                continue

        if vertical_check(plane):

            if -1 * plane[2] / plane[1] < point[1]:

                minim_y = max(minim_y, -1 * plane[2] / plane[1])
            else:
                maxim_y = min(maxim_y, -1 * plane[2] / plane[1])
        else:

            if -1 * plane[2] / plane[0] < point[0]:

                minim_x = max(minim_x, -1 * plane[2] / plane[0])
            else:
                maxim_x = min(maxim_x, -1 * plane[2] / plane[0])

    if max(maxim_x, maxim_y) == inf or min(minim_x, minim_y) == -inf:
        print("NO")
    else:
        area = (maxim_x - minim_x) * (maxim_y - minim_y)

        if abs(float(area) - epsilon) <= int(area):
            area = int(area)
        print("YES")
        print(area)

 */