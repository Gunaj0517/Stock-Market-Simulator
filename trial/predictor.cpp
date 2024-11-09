#include <iostream>
#include <vector>
#include "predictor.h"
#include <random>

using namespace std;
struct TreeNode {
    double price;
    TreeNode *left, *right;
    TreeNode(double p) : price(p), left(nullptr), right(nullptr) {}
};

//TreeNode::TreeNode(double p) : price(p), left(nullptr), right(nullptr) {}

TreeNode* insert(TreeNode* node, double price) {
    if (node == nullptr) {
        return new TreeNode(price);
    }
    if (price < node->price) {
        node->left = insert(node->left, price);
    } else if (price > node->price) {
        node->right = insert(node->right, price);
    }
    return node;
}

double findMin(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current ? current->price : -1;
}

double findMax(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->right != nullptr) {
        current = current->right;
    }
    return current ? current->price : -1;
}

vector<double> generatePrices(double openingPrice, int count, double minRange, double maxRange) {
    vector<double> prices;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(minRange, maxRange);
    for (int i = 0; i < count; ++i) {
        prices.push_back(dist(gen));
    }
    return prices;
}

/*
int main() {
    double openingPrice = 233.5;
    int sampleCount = 15;
    double minRange = openingPrice - 10;
    double maxRange = openingPrice + 10;

    vector<double> prices = generatePrices(openingPrice, sampleCount, minRange, maxRange);

    TreeNode* root = nullptr;
    for (double price : prices) {
        root = insert(root, price);
    }

    double minPrice = findMin(root);
    double maxPrice = findMax(root);
    double predictedPrice = root ? root->price : -1;

    cout << "Predicted Price Range lies between: " << minPrice << " and " << maxPrice << endl;
    cout << "Predicted Price (Root of BST): " << predictedPrice << endl;

    return 0;
}
*/