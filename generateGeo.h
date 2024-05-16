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

template<class T>
vector<float> vec2tovec1(vector<vector<T>> v) {
    return {
         0.5f,  0.5f, 0.0f,  // top right
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
    };
    vector<float> ans;
    for (auto& v1 : v) {
        for (auto& v2 : v1) {
            ans.push_back(v2);
        }
    }
    return ans;
}