#include <bits/stdc++.h>
using namespace std;

const int maxn=1e5+5;

typedef struct Node {
    map<string, string> value;
    string result;
} node;

vector<node>data;
vector<string>features;
map<pair<int, int>, pair<string, string>>rule;
vector<int>treeNode[maxn];

int main() {
    freopen("Task.in","r",stdin);freopen("Task.out","w",stdout);

    int n;
    cout<<"Enter number of features: \n";
    cin>>n;

    for (int i=0; i<n; i++) {
        string x;
        cin>>x;

        features.push_back(x);
    }

    ifstream in;
    in.open("ILAData2.cvv");

    string val;
    while (in>>val) {
        node newData;
        newData.value[features[0]] = val;
        for (int i=1; i<features.size(); i++) {
            in>>val;
            newData.value[features[i]] = val;
        }
        in>>val;
        newData.result = val;

        data.push_back(newData);
    }

    for (int i=0; i<data.size(); i++) {
        treeNode[1].push_back(i);
    }
    int lastNode=1, currNode=1;
    while (currNode<=lastNode) {
        if(treeNode[currNode].size()==0) {
            currNode++;
            continue;
        }
        long double maxGain=0;
        int featureNum=-1;
        bool ck=0;
        bool ch=0;
        int ap, bp;
        for (int i=0; i<features.size(); i++) {
            map<string, int>y, n;
            set<string>allFeat;
            int ny=0, nn=0;
            for (int j=0; j<treeNode[currNode].size(); j++) {
                allFeat.insert(data[treeNode[currNode][j]].value[features[i]]);
                if(data[treeNode[currNode][j]].result == "Yes" || data[treeNode[currNode][j]].result == "yes") {
                    y[data[treeNode[currNode][j]].value[features[i]]]++;
                    ny++;
                } else {
                    n[data[treeNode[currNode][j]].value[features[i]]]++;
                    nn++;
                }
            }
            ap=ny, bp=nn;
            if(ny==0 || nn==0) {
                ch=1;
                break;
            }
            long double yprob = (long double)ny/((long double)ny + (long double)nn), nprob = (long double)nn/((long double)ny + (long double)nn);
            long double entrp = ((-1) * yprob * log(yprob)) - (nprob * log(nprob)), tentrp = 0;
            for (auto it:allFeat) {
                int yes=y[it], no=n[it];
                long double py = (long double) yes / (long double) (yes + no);
                long double pn = (long double) no / (long double) (yes + no);

                long double ent = 0;
                if(py!=0) {
                    ent+=((-1) * py * log(py));
                }
                if(pn!=0) {
                    ent+=((-1) * pn * log(pn));
                }
                long double multiplier = ((long double) (yes + no))/((long double) (ny + nn));
                tentrp += (multiplier * ent);
            }
            long double gain = entrp - tentrp;
            if(gain > maxGain || !ck) {
                ck=1;
                maxGain = gain;
                featureNum = i;
            }
        }
        if(ch) {
            currNode++;
            continue;
        }
        map<string, int>goodFeat;
        for (int j=0; j<treeNode[currNode].size(); j++) {
            string val=data[treeNode[currNode][j]].value[features[featureNum]];
            int curr;
            if(goodFeat.find(val)==goodFeat.end()) {
                curr=lastNode+1;
                lastNode++;
                goodFeat[val]=curr;
                // cout<<currNode<<" g "<<curr<<endl;
                rule[make_pair(currNode, curr)] = make_pair(features[featureNum], val);
            } else {
                curr=goodFeat[val];
            }
            treeNode[curr].push_back(treeNode[currNode][j]);
        }
        currNode++;
    } 
    cout<<"Number of Nodes: "<<lastNode<<endl<<endl;   
    for (auto i:rule) {
        cout<<i.first.first<<" "<<i.first.second<<endl;
        cout<<"Rule: \n";
        cout<<i.second.first<<" should be "<<i.second.second<<endl;
        cout<<endl;
    }
}
