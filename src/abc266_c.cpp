#include <iostream>
#include <cmath>
using namespace std;

// 2つのベクトルの外積を計算
double crossProduct(double x1, double y1, double x2, double y2) {
    return x1 * y2 - y1 * x2;
}

// 4点が凸四角形かどうかを判定
bool isConvexQuadrilateral(double ax, double ay, double bx, double by, double cx, double cy, double dx, double dy) {
    // 外積を計算
    double cross1 = crossProduct(bx - ax, by - ay, cx - ax, cy - ay); // AB x AC
    double cross2 = crossProduct(cx - bx, cy - by, dx - bx, dy - by); // BC x BD
    double cross3 = crossProduct(dx - cx, dy - cy, ax - cx, ay - cy); // CD x CA
    double cross4 = crossProduct(ax - dx, ay - dy, bx - dx, by - dy); // DA x DB

    // すべての外積が同じ符号であれば凸四角形
    return (cross1 >= 0 && cross2 >= 0 && cross3 >= 0 && cross4 >= 0) || (cross1 <= 0 && cross2 <= 0 && cross3 <= 0 && cross4 <= 0);
}

int main() {
    double a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y;
    cin >> a_x >> a_y;
    cin >> b_x >> b_y;
    cin >> c_x >> c_y;
    cin >> d_x >> d_y;

    if (isConvexQuadrilateral(a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y)) {
        cout << "Yes" << endl; // 凸四角形
    } else {
        cout << "No" << endl; // 凸四角形でない
    }

    return 0;
}
