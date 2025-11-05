#include <bits/stdc++.h>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'swapNodes' function below.
 *
 * The function is expected to return a 2D_INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY indexes
 *  2. INTEGER_ARRAY queries
 */

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

void swapAtDepth(Node* root, int k, int depth) {
    if (!root) return;
    if (depth % k == 0) swap(root->left, root->right);
    swapAtDepth(root->left, k, depth + 1);
    swapAtDepth(root->right, k, depth + 1);
}

void inorder(Node* root, vector<int>& res) {
    if (!root) return;
    inorder(root->left, res);
    res.push_back(root->data);
    inorder(root->right, res);
}

vector<vector<int>> swapNodes(vector<vector<int>> indexes, vector<int> queries) {
    int n = indexes.size();
    vector<Node*> nodes(n + 1, nullptr);

    // Create root node
    nodes[1] = new Node(1);
    queue<Node*> q;
    q.push(nodes[1]);
    int i = 0;

    // Build the tree level-wise
    while (!q.empty() && i < n) {
        Node* curr = q.front();
        q.pop();

        int leftVal = indexes[i][0];
        int rightVal = indexes[i][1];

        if (leftVal != -1) {
            curr->left = new Node(leftVal);
            nodes[leftVal] = curr->left;
            q.push(curr->left);
        }
        if (rightVal != -1) {
            curr->right = new Node(rightVal);
            nodes[rightVal] = curr->right;
            q.push(curr->right);
        }
        i++;
    }

    // Process each query
    vector<vector<int>> result;
    for (int k : queries) {
        swapAtDepth(nodes[1], k, 1);
        vector<int> res;
        inorder(nodes[1], res);
        result.push_back(res);
    }

    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<vector<int>> indexes(n);

    for (int i = 0; i < n; i++) {
        indexes[i].resize(2);

        string indexes_row_temp_temp;
        getline(cin, indexes_row_temp_temp);

        vector<string> indexes_row_temp = split(rtrim(indexes_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int indexes_row_item = stoi(indexes_row_temp[j]);
            indexes[i][j] = indexes_row_item;
        }
    }

    string queries_count_temp;
    getline(cin, queries_count_temp);

    int queries_count = stoi(ltrim(rtrim(queries_count_temp)));

    vector<int> queries(queries_count);

    for (int i = 0; i < queries_count; i++) {
        string queries_item_temp;
        getline(cin, queries_item_temp);

        int queries_item = stoi(ltrim(rtrim(queries_item_temp)));
        queries[i] = queries_item;
    }

    vector<vector<int>> result = swapNodes(indexes, queries);

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            fout << result[i][j];

            if (j != result[i].size() - 1) {
                fout << " ";
            }
        }
        fout << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);
    s.erase(s.begin(), find_if(s.begin(), s.end(),
        not1(ptr_fun<int,int>(isspace))));
    return s;
}

string rtrim(const string &str) {
    string s(str);
    s.erase(find_if(s.rbegin(), s.rend(),
        not1(ptr_fun<int,int>(isspace))).base(), s.end());
    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;
    string::size_type start = 0, end = 0;

    while ((end = str.find(' ', start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + 1;
    }

    tokens.push_back(str.substr(start));
    return tokens;
}
