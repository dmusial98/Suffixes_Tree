#include <iostream>

using namespace std;

class tree_node
{
	string text = string();
	int start_index = -1, end_index = -1;
	tree_node* left_child = nullptr, * right_brother = nullptr, * suffix_link = nullptr;
	bool is_root = false;

public:
	tree_node();
	tree_node(string text, bool root = false);
	tree_node(string text, int s_index, int e_index, bool root = false);

	bool does_exist_child_with_that_letter(char letter);
	bool does_tree_contain_sufix(string sufix);
	bool does_tree_contain_string(string suffix);
	void append_letter_at_the_end(char letter);
	void create_suffix(string suffix);
	tree_node** create_two_branches(string suffix1, string suffix2);
	string* get_all_suffixes_from_node(int* size, tree_node* node);
};

tree_node* create_suffix_tree_ukkonen(string input_text)
{
	tree_node* root_node = new tree_node();



	return root_node;
}

tree_node::tree_node() {}

tree_node::tree_node(string txt, bool root) : text(txt), is_root(root) {}

tree_node::tree_node(string text, int s_index, int e_index, bool root)
{
	this->text = text;
	this->start_index = s_index;
	this->end_index = e_index;
	this->is_root = root;
}

bool tree_node::does_exist_child_with_that_letter(char letter)
{
	tree_node* ptr = this->left_child;
	while (ptr)
	{
		if (ptr->text.front() == letter)
			return true;

		ptr = ptr->right_brother;
	}

	return false;
}

string* tree_node::get_all_suffixes_from_node(int* size, tree_node* node)
{

	return nullptr;
}


bool tree_node::does_tree_contain_string(string suffix)
{
	if (this->is_root)
	{
		tree_node* ptr = this->left_child;

		while (ptr)
		{
			if (ptr->does_tree_contain_string(suffix))
				return true;

			ptr = ptr->right_brother;
		}
	}
	else
	{

	}
}

/*
* when root check if child contains suffix
* when it'isn't root, check if this node contains suffix
*/
bool tree_node::does_tree_contain_sufix(string suffix)
{
	if (this->is_root)
	{
		tree_node* ptr = this->left_child;

		while (ptr)
		{
			if (ptr->does_tree_contain_sufix(suffix))
				return true;

			ptr = ptr->right_brother;
		}
	}
	else //!is_root
	{



		//if (this->text.length() >= suffix.length())
		//{
		//	//at 0 index we have suffix
		//	size_t found = this->text.find(suffix);
		//	if (!found) //found == 0
		//		return true;

		//}
		//else //PO CO TO?
		//{

		//	//TODO: Potrzebna metoda zwracajaca wszystkie suffiksy z danego wezla wglab 
		//	//TODO: Potrzebna metoda sprawdzajaca czy w tych suffiksach znajduje sie okreslony string 
		//	if ()
		//	{

		//	}

		//	size_t found = this->text.find(suffix.substr(0, this->text.length()));
		//	if (!found) //found at 0 index -> we will check the rest of suffix
		//	{
		//		tree_node* ptr = this->left_child;
		//		while (ptr)
		//		{
		//			if (ptr->does_tree_contain_sufix(suffix.substr(this->text.length())))
		//				return true;

		//			ptr = ptr->right_brother;
		//		}
		//	}
		//}
	}

	return false;
}

//return two tree_nodes with specified suffixes
tree_node** tree_node::create_two_branches(string suffix1, string suffix2)
{
	tree_node** nodes = new tree_node * [2];

	nodes[0] = new tree_node(suffix1);
	nodes[1] = new tree_node(suffix2);

	nodes[0]->right_brother = nodes[1];

	return nodes;
}

void tree_node::create_suffix(string suffix)
{

	if (this->is_root)
	{
		//create suffix under root node
		if (!this->left_child)
		{
			this->left_child = new tree_node(suffix);
			return;
		}
		////////////////////////////////

		//find node with correct first letter
		tree_node* ptr = this->left_child;

		while (ptr && ptr->text[0] != suffix[0])
			ptr = ptr->right_brother;
		//////////////////////////////////////

		if (!ptr) //we don't have node with correct first letter
		{
			tree_node* ptr2 = this->left_child;
			while (ptr2->right_brother)
				ptr2 = ptr2->right_brother;

			ptr2->right_brother = new tree_node(suffix);
			return;
		}
		else //we have node with correct first letter
		{
			if (ptr->text[0] == suffix[0])
			{
				string var_to_iterate = ptr->text.length() > suffix.length() ? ptr->text : suffix;
				
				//find the longest string which match with node
				for (int i = 0; i < var_to_iterate.length(); i++)
				{

					if (suffix.substr(0, suffix.length() - i) == "")
						continue; //TODO: zastanowic sie czy break nie bylby lepszy

					size_t found = ptr->text.find(suffix.substr(0, suffix.length() - i));
					if (!found) //found == 0 -> suffix.length() - i is the longest matching suffix
					{
						if (i == 0) //node contains specified suffix 
							return;
						else //node contains only part of new suffix
						{
							//TODO: Potrzebna metoda zwracajaca wszystkie suffiksy z danego wezla wglab 
							//TODO: Potrzebna metoda sprawdzajaca czy w tych suffiksach znajduje sie okreslony string 


							ptr->text = ptr->text.substr(0, suffix.length() - i); //cut main node's text before adding two new nodes below
							tree_node** nodes = create_two_branches(suffix.substr(suffix.length() - i), ptr->text.substr(suffix.length() - i));
							tree_node* old_node = ptr->left_child;

							if (!ptr->left_child)
							{
								ptr->left_child = nodes[0];
							}
							else
							{
								//TODO: chyba bedzie potrzebne przepisanie starych nodow ponizej
								nodes[1]->left_child = old_node->left_child;
								//delete old_node;
							}

							if (ptr->right_brother)
							{
								//TODO: zastanowic sie nad przpeisywaniem braci
							}

							return;
						}

					}

				}
			}
		}



	}
}

//void tree_node::create_child(string text)
//{
//	if (!this->left_child)
//		this->left_child = new tree_node(text);
//	else
//	{
//		tree_node* ptr = this->left_child;
//		while (ptr->right_brother != nullptr)
//		{
//			ptr = ptr->right_brother;
//		}
//
//		ptr->right_brother = new tree_node(string(text));
//	}
//}

void tree_node::append_letter_at_the_end(char letter)
{
	if (!this->left_child)
		this->text += letter;

	if (this->left_child)
		this->left_child->append_letter_at_the_end(letter);

	if (this->right_brother)
		this->right_brother->append_letter_at_the_end(letter);
}



int main()
{
	tree_node* ptr = new tree_node("", true);
	// M
	ptr->create_suffix("M");
	// I
	ptr->append_letter_at_the_end('I');
	ptr->create_suffix("I");
	// S
	ptr->append_letter_at_the_end('S');
	ptr->create_suffix("S");
	// S
	ptr->append_letter_at_the_end('S');
	// I
	ptr->append_letter_at_the_end('I');
	ptr->create_suffix("SSI");
	ptr->create_suffix("SI");
	bool first = ptr->does_tree_contain_sufix("MISS");
	bool second = ptr->does_tree_contain_sufix("ISS");
	bool third = ptr->does_tree_contain_sufix("SS");
	bool forth = ptr->does_tree_contain_sufix("S");
	//bool fifth = ptr->does_tree_contain_sufix("I");
	return 0;
}
