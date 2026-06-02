#pragma once

#include <cstddef>
#include <iostream>

/**
 * @brief Класс SplayTree — самобалансирующееся дерево поиска (splay tree).
 * 
 * @tparam Key Тип ключа (должен поддерживать сравнение).
 * @tparam Value Тип значения.
 */
template<typename Key, typename Value>
class SplayTree {
    struct Node {
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	std::pair<Key, Value> keyValuePair;

	Node(Key key, Value value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr): keyValuePair(key, value), parent(parent), left(left), right(right) {}

	void rotateLeft() {
	    Node* pivot = this->right;

	    pivot->parent = this->parent;
	    if (this->parent) {
		if (this->parent->left == this) {
		    this->parent->left = pivot;
		}
	       	else {
		    this->parent->right = pivot;
		}
	    }

	    this->right = pivot->left;
	    if (pivot->left) pivot->left->parent = this;

	    this->parent = pivot;
	    pivot->left = this;
	}

	void rotateRight() {
	    Node* pivot = this->left;

	    pivot->parent = this->parent;
	    if (this->parent) {
		if (this->parent->left == this) {
		    this->parent->left = pivot;
		}
	       	else {
		    this->parent->right = pivot;
		}
	    }

	    this->left = pivot->right;
	    if (pivot->right) pivot->right->parent = this;

	    this->parent = pivot;
	    pivot->right = this;
	}


	Node* insert(const Key& key, const Value& value) {
		Node* elem = parent;
		if (key >= keyValuePair.first) {
			if (right != nullptr) {
				return right->insert(key, value);
			}
			right = new Node(key, value, this);
			return right;
		}
		else if (key < keyValuePair.first) {
			if (left != nullptr) {
				return left->insert(key, value);
			}
			left = new Node(key, value, this);
			return left;
		}
		return nullptr;
		//else if (key == keyValuePair.first) keyValuePair.second = value;
	}

	static void erase_all(const Node* node) {
		if (node != nullptr) {
			if (node->right) erase_all(node->right);
			if (node->left) erase_all(node->left);
			delete node;
		}
		return;
	}
    };

    Node* _root = nullptr;
    size_t _size = 0;

public:
    /**
     * @brief Конструктор по умолчанию. Создаёт пустое дерево.
     */
    SplayTree()=default;

    /**
     * @brief Деструктор. Очищает все ресурсы, связанные с деревом.
     */
    ~SplayTree() {
	    Node::erase_all(_root);
	    _root = nullptr;
    }

    void splay(Node* node) {
	    Node* grandparent = nullptr;
	    if (node->parent) grandparent = node->parent->parent;
	    while(node->parent) {
		    if (node == node->parent->left) {
			    if (!grandparent) node->parent->rotateRight();
			    else if (node->parent == grandparent->left) {
				    grandparent->rotateRight();
				    node->parent->rotateRight();
			    }
			    else {
				    node->parent->rotateRight();
				    node->parent->rotateLeft();
			    }
		    }
		    else {
			    if (!grandparent) node->parent->rotateLeft();
			    else if (node->parent == grandparent->left) {
				    grandparent->rotateLeft();
				    node->parent->rotateLeft();
			    }
			    else {
				    node->parent->rotateLeft();
				    node->parent->rotateRight();
			    }
		    }
	    }
    }

    /**
     * @brief Вставляет пару (key, value) в дерево.
     * Если ключ уже существует, его значение обновляется.
     * После вставки/обновления соответствующий узел становится корнем (splay).
     * 
     * @param key Ключ для вставки.
     * @param value Значение для вставки.
     */
    void insert(const Key& key, const Value& value) {
	if (_root == nullptr) {
		_root = new Node(key, value);
	//	_root->right = new Node(Key(), value, _root);
		_size++;
	//	splay(_root);
	}
	else {
		Node* elem = _root;
		Node* prev = nullptr;
		while (elem) {
			prev = elem;
			if (key > elem->keyValuePair.first) elem = elem->right;
			else if (key < elem->keyValuePair.first) elem = elem->left;
			else {
				elem->keyValuePair.second = value;
				splay(elem);
				return;
			}
		}
		
		Node* newNode = new Node(key, value);
		if (key > prev->keyValuePair.first) prev->right = newNode;
		else prev->left = newNode;
		_size++;
		splay(newNode);
		//Node* elem = _root->insert(key, value);
		//_size++;
		//splay(elem);
	}
    }


    /**
     * @brief Удаляет узел с заданным ключом из дерева.
     * 
     * @param key Ключ для удаления.
     * @return true если элемент был найден и удалён, false если такого ключа нет.
     */
    bool remove(const Key& key) {
	    if(search(key) == nullptr) return false;

	    Node* elem = _root;
	    while(elem) {
		    if(key == elem->keyValuePair.first) {
			    splay(elem);
			    break;
		    }
		    if (key > elem->keyValuePair.first) elem = elem->right;
		    if (key < elem->keyValuePair.first) elem = elem->left;
	    }

	    if (elem->left) elem->left->parent = nullptr;
	    if (elem->right) elem->right->parent = nullptr;
	    Node* lelem = elem->left;
	    Node* relem = elem->right;
	    delete elem;
	    _size--;
	    if (lelem == nullptr) {
		    _root = relem;
		    return 1;
	    }
	    if (relem == nullptr) {
		    _root = lelem;
		    return 1;
	    }

	    _root = lelem;
	    Node* mx = lelem;
	    while (mx->right) mx = mx->right;
	    splay(mx);
	    _root->right = relem;
	    relem->parent = _root;
	    return 1;
    }


    /**
     * @brief Ищет элемент по ключу.
     * Если найден, возвращает указатель на значение (Value*), иначе nullptr.
     * После поиска найденный (или последний просмотренный) узел становится корнем (splay).
     * 
     * @param key Ключ для поиска.
     * @return Value* Указатель на значение или nullptr.
     */
    Value* search(const Key& key) {
	    Node* elem = _root;
	    Node* prev = nullptr;
	    while (elem) {
		    prev = elem;
		    if(key == elem->keyValuePair.first) {
			    splay(elem);
			    return &elem->keyValuePair.second;
		    }
		    else if (key > elem->keyValuePair.first) elem = elem->right;
		    else if (key < elem->keyValuePair.first) elem = elem->left;

	    }
	    if (prev != nullptr) splay(prev);
	    return nullptr;
    }

    /**
     * @brief Константная версия поиска.
     * Не изменяет структуру дерева.
     * 
     * @param key Ключ для поиска.
     * @return const Value* Указатель на значение или nullptr.
     */
    const Value* search(const Key& key) const {
	    Node* elem = _root;
	    Node* prev = nullptr;
	    while (elem) {
		    if(key == elem->keyValuePair.first) {
			    return &elem->keyValuePair.second;
		    }
		    if (key > elem->keyValuePair.first) elem = elem->right;
		    if (key < elem->keyValuePair.first) elem = elem->left;

		    prev = elem;
	    }
	    return nullptr;
    }
    
    bool isValid(Node* node, Key* min, Key* max) const {
	if (node  == nullptr) return true;
	if (min && node->keyValuePair.first <= *min) return false;

	if (max && node->keyValuePair.first >= *max) return false;
	//bool leftValid = isValid(node->left, min, &node->keyValuePair.first);
	//if (!leftValid) return false;
    
    	//bool rightValid = isValid(node->right, &node->keyValuePair.first, max);
    
    	//return rightValid;	
	return isValid(node->left, min,&node->keyValuePair.first) && isValid(node->right, &node->keyValuePair.first, max);
    }
	
    /**
     * @brief Проверяет, что дерево удовлетворяет свойству бинарного дерева поиска (BST).
     * 
     * @return true если дерево корректно, false иначе.
     */
    bool isValidBST() const {
	    if (!_root) return true;
	    return isValid(_root, nullptr, nullptr);
    }

    /**
     * @brief Возвращает количество элементов в дереве.
     * 
     * @return size_t Количество элементов.
     */
    size_t size() const {
	    return _size;
    }

    /**
     * @brief Проверяет, пусто ли дерево.
     * 
     * @return true если дерево пустое, false иначе.
     */
    bool empty() const {
	    return (_size == 0);
    }


};
