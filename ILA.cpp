#include <bits/stdc++.h>
using namespace std;

typedef struct Node {
	map<string, string> value;
	string result;
} node;

vector<node>data;
vector<string>features;
map<string, vector<int> > buckets;
vector<int>trueData, falseData;
map<map<string, string>, string >rules;

int maxTrue;
map<string, string> currentRule;
vector<int>selects;
void checkFeature(int current, vector<int> selected, int toSelect) {
	if(selected.size()>toSelect)	return;
	if(current == features.size()) {
		if(toSelect != selected.size())	return;
		map<vector<string>, int>truePart, falsePart;
		for (int i=0; i<trueData.size(); i++) {
			vector<string> feat;
			for (int j=0; j<selected.size(); j++) {
				feat.push_back(data[trueData[i]].value[features[selected[j]]]);
			}
			truePart[feat]++;
		}
		for (int i=0; i<falseData.size(); i++) {
			vector<string> feat;
			for (int j=0; j<selected.size(); j++) {
				feat.push_back(data[falseData[i]].value[features[selected[j]]]);
			}
			falsePart[feat]++;
		}

		for (auto it:truePart) {
			if(falsePart.find(it.first)!=falsePart.end())	continue;
			if(maxTrue<it.second) {
				maxTrue=it.second;
				currentRule.clear();
				for (int i=0; i<selected.size(); i++) {
					currentRule[features[selected[i]]]=it.first[i];
				}
				selects.clear();
				selects=selected;
			}
		}
		return;
	}
	checkFeature(current+1, selected, toSelect);
	selected.push_back(current);
	checkFeature(current+1, selected, toSelect);
	selected.pop_back();
}
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
		// for (auto j:data[i].value) {
		// 	cout<<j.first<<" "<<j.second<<endl;
		// }
		// cout<<data[i].result<<endl<<endl;

		if(data[i].result=="yes" || data[i].result=="Yes")	trueData.push_back(i);
		else	falseData.push_back(i);
	}
	cout<<endl;
	int j=1;
	while (!trueData.empty()) {
		for (int i=1; i<=features.size(); i++) {
			maxTrue=0;
			currentRule.clear();
			selects.clear();
			vector<int>select;
			checkFeature(0, select, i);
			// cout<<i<<" "<<maxTrue<<endl;
			if(maxTrue==0)	continue;
			cout<<"Rule No. "<<j++<<endl;
			vector<int> rtrueData;
			for (int i=0; i<trueData.size(); i++) {
				bool ch=0;
				for (int j=0; j<selects.size(); j++) {
					if(data[trueData[i]].value[features[selects[j]]]!=currentRule[features[selects[j]]]) {
						ch=1;
						break;
					}
				}
				if(ch) {
					rtrueData.push_back(trueData[i]);
				}
			}
			for (auto it:currentRule) {
				cout<<it.first<<": "<<it.second<<endl;
			}
			cout<<"Result: Yes"<<endl;
			cout<<endl;
			rules[currentRule]="yes";
			trueData=rtrueData;
			break;
		}
	}

	
	// for (auto i:rules) {
	// 	cout<<"Rule No. "<<j++<<endl;
	// 	for (auto j:i.first) {
	// 		cout<<j.first<<": "<<j.second<<endl;
	// 	}
	// 	cout<<"Result: "<<i.second<<endl;
	// 	cout<<endl;
	// }
	cout<<"Rule No. "<<j++<<endl;
	cout<<"else result is no\n";

	
}
