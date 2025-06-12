#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "dataBaseSaham.cpp"
using namespace std;

struct Stock {
    string name;
    string sector;
    double roi;
    double volatility;
    int price;
};

void merge(vector<Stock>& stocks, int left, int mid, int right, bool sortByROI) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Stock> L(n1);
    vector<Stock> R(n2);

    for (int i = 0; i < n1; i++) L[i] = stocks[left+i];
    for (int j = 0; j < n2; j++) R[j] = stocks[mid+1+j];

    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2){
        if (sortByROI){
            if (L[i].roi > R[j].roi) stocks[k++] = L[i++];
            else stocks[k++] = R[j++];
        } else {
            if (L[i].volatility < R[j].volatility) stocks[k++] = L[i++];
            else stocks[k++] = R[j++];
        }
    }
    while(i < n1) stocks[k++] = L[i++];
    while(j < n2) stocks[k++] = R[j++];
}

void mergeSort(vector<Stock>& stocks, int left, int right, bool sortByROI){
    if (left < right){
        int mid = left + (right - left)/2;
        mergeSort(stocks, left, mid, sortByROI);
        mergeSort(stocks, mid+1, right, sortByROI);
        merge(stocks, left, mid, right, sortByROI);
    }
}


struct Solution {
    double totalROI;
    int totalCost;
    vector<int> selectedIndices;
};

Solution knapsack(const vector<Stock>& stocks, int maxInvestment, int maxRisk){
    int n = stocks.size();

    vector<int> selectedIdx;
    double totalROI = 0;
    int totalCost = 0;
    double totalRisk = 0.0;

    vector<pair<double,int>> ratioIdx;
    for (int i=0; i<n; i++){
        double riskValue = stocks[i].volatility * stocks[i].price;
        if (riskValue <= 0) riskValue = 1.0;
        ratioIdx.push_back({stocks[i].roi / riskValue, i});
    }
    sort(ratioIdx.rbegin(), ratioIdx.rend());

    for (auto& pair: ratioIdx){
        int i = pair.second;
        double stockRisk = stocks[i].volatility * stocks[i].price;
        int stockCost = stocks[i].price;
  if (totalCost + stockCost <= maxInvestment && (totalRisk + stockRisk) <= maxRisk){
            selectedIdx.push_back(i);
            totalCost += stockCost;
            totalRisk += stockRisk;
            totalROI += stocks[i].roi;
        }
    }

    return {totalROI, totalCost, selectedIdx};
}


int main() {

return 0;
}
