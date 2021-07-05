#include<bits/stdc++.h>
#include<fstream>
#define int long long int
using namespace std;


void c_p_c()
{
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
}


vector<vector<bool> >isVisited(4, vector<bool>(4, false));
set<string>wordsFound;
string grid[4][4];

// 8 possible valid directions for the creation of word in gridArray.
int dx[] = { -1 , -1 , 0 , 1 , 1 , 1 , 0 , -1};
int dy[] = {0 , 1 , 1 , 1 , 0 , -1 , -1 , -1};




// Creation of Node-Data
class Node
{
public:
	char data;
	unordered_map<char, Node*>child;
	bool isTerminal;

	Node(char ch)
	{
		data = ch;
		isTerminal = false;
	}

};



// Creation of Trie Data-Structure
class Trie
{
	Node *root;

public:

	Trie()
	{
		root = new Node('\0');
	}


	// Insertion of Word in Trie.
	void insertWord(string wrd)
	{
		Node *temp = root;

		for (int i = 0; i < wrd.length(); i++)
		{
			char ch = wrd[i];

			// If given character is present is present then move downwards.
			if (temp->child.count(ch))
			{
				temp = temp->child[ch];
			}

			// If given character is not present then insert the character in trie.
			else
			{
				Node *nChar = new Node(ch);
				temp->child[ch] = nChar;
				temp = nChar;
			}
		}

		temp->isTerminal = true;
	}


	// findWrd is responsible to tell whether given wrd is present
	// in trie data-structure or not.
	bool findWrd(string wrd)
	{
		Node *temp = root;

		for (int i = 0; i < wrd.length(); i++)
		{
			char ch = wrd[i];

			if (!temp->child.count(ch))
				return false;

			else
				temp = temp->child[ch];
		}

		return temp->isTerminal;
	}


};


void preProcessing(Trie t)
{

	cout << "Preprocessing the backend Files\n";

	ifstream wordsFile("corncob_lowercase.txt");
	string word;

	while (wordsFile >> word)
	{
		// cout << word << "\n";

		// Doesn't require the words which of length less than 2.
		if (word.length() >= 2)
			t.insertWord(word);

	}

	cout << "Done with Preprocessing. You are good to go." << "\n";
}


// DFS on the given grid to generate the words and check whether
// the word is existed in our trie or not.

void dfs_grid(string wrd, int row, int col, Trie t)
{
	isVisited[row][col] = true;

	if (t.findWrd(wrd))
	{
		wordsFound.insert(wrd);
	}


	// Does n't require more than 20 words if meaningful words formed
	// in our grid.

	// if (wordsFound.size() > 49)
	// 	return;

	for (int i = 0; i < 8; i++)
	{
		int n_row = row + dx[i];
		int n_col = col + dy[i];

		if (n_row >= 0 and n_row < 4 and n_col >= 0 and n_col < 4 and !isVisited[n_row][n_col])
		{
			dfs_grid(wrd + grid[n_row][n_col], n_row, n_col, t);
		}
	}

	isVisited[row][col] = false;
}


// void resetVisited()
// {
// 	for (int i = 0; i < 4; i++)
// 	{
// 		for (int j = 0; j < 4; j++)
// 		{
// 			isVisited[i][j] = false;
// 		}
// 	}
// }


int32_t main()
{
	c_p_c();

	Trie t;

	preProcessing(t);

	cout << "\n\n";


	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> grid[i][j];
		}
	}


	// for (int i = 0; i < 4; i++)
	// {
	// 	for (int j = 0; j < 4; j++)
	// 	{
	// 		cout << grid[i][j] << " ";
	// 	}

	// 	cout << "\n";
	// }

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			dfs_grid(grid[i][j], i, j, t);
		}
	}

	cout << "\n\n";
	cout << "Total No. of words are: " << wordsFound.size() << "\n";

	for (auto v : wordsFound)
		cout << v << "\n";


}
