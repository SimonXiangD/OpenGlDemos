#pragma once

#include<bits/stdc++.h>
using namespace std;


float random_float(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}



vector<float> getRandomPoint() {
    vector<float> point(3, 1);
    for (int i = 0; i < 3; i++) point[i] = random_float(-1, 1);
    return point;
}

vector<vector<float>> getTraingle2d() {
    vector<vector<float>> triangle;
    for (int i = 0; i < 3; i++) triangle.push_back(getRandomPoint());
    return triangle;
}

void dfs(int i, vector<float>& cur, vector<vector<float>>& ans) {
    if (i == cur.size()) ans.push_back(cur);
    else {
        dfs(i + 1, cur, ans);
        cur[i] *= -1;
        dfs(i + 1, cur, ans);
    }
}
vector<vector<float>> getCube2d() {
    vector<float> start = { -0.5, -0.5, -0.5 };
    vector<vector<float>> ans;
    dfs(0, start, ans);
    
    auto diff = [](vector<float> a, vector<float> b) -> int {
        int ans = 0;
        for (int i = 0; i < a.size(); i++) if (abs(a[i] - b[i]) > 1e-5) ans++;
        return ans;
        };
    vector<vector<float>> tans;
    for (int i = 0; i < 3; i++) {
        int sign = 1;
        for (int j = 0; j < 2; j++) {
            sign *= -1;
            vector<vector<float>> tmp;
            vector<int> index;
            for (auto t : ans) {
                if (t[i] * sign == 0.5) tmp.push_back(t);
            }
            index.push_back(0);
            int diagv = -1;
            for (int k = 1; k < 4; k++) {
                if (diff(tmp[0], tmp[k]) == 2) {
                    diagv = k; break;
                }
            }
            for (auto t : { 0, diagv }) {
                for (int i1 = 0; i1 < 4; i1++) {
                    if (i1 == t) continue;
                    tans.push_back(tmp[i1]);
                }
            }
        }
    }
    //for (auto t : tans) {
    //    cout << "-------------" << endl;
    //    show(t);
    //}
    return tans;
}


template<class T>
vector<float> vec2tovec1(vector<vector<T>> v) {
    //return {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //};
    vector<float> ans;
    for (auto& v1 : v) {
        for (auto& v2 : v1) {
            ans.push_back(v2);
        }
    }
    return ans;
}

void translate(vector<float>& vec) {
    for (auto& t : vec) t += 0.1;
}

