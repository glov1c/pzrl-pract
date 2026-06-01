#pragma once
#include <cstddef>

/**
 * @brief Класс SplayTree — самобалансирующееся дерево поиска (splay tree).
 * 
 * @tparam Key Тип ключа (должен поддерживать сравнение).
 * @tparam Value Тип значения.
 */
template<typename Key, typename Value>
class SplayTree {
public:
    /**
     * @brief Конструктор по умолчанию. Создаёт пустое дерево.
     */
    SplayTree()=default;

    /**
     * @brief Деструктор. Очищает все ресурсы, связанные с деревом.
     */
    ~SplayTree() {
	    erase_all(_root);
    }

    /**
     * @brief Вставляет пару (key, value) в дерево.
     * Если ключ уже существует, его значение обновляется.
     * После вставки/обновления соответствующий узел становится корнем (splay).
     * 
     * @param key Ключ для вставки.
     * @param value Значение для вставки.
     */
    void insert(const Key& key, const Value& value);

    /**
     * @brief Удаляет узел с заданным ключом из дерева.
     * 
     * @param key Ключ для удаления.
     * @return true если элемент был найден и удалён, false если такого ключа нет.
     */
    bool remove(const Key& key);

    /**
     * @brief Ищет элемент по ключу.
     * Если найден, возвращает указатель на значение (Value*), иначе nullptr.
     * После поиска найденный (или последний просмотренный) узел становится корнем (splay).
     * 
     * @param key Ключ для поиска.
     * @return Value* Указатель на значение или nullptr.
     */
    Value* search(const Key& key);

    /**
     * @brief Константная версия поиска.
     * Не изменяет структуру дерева.
     * 
     * @param key Ключ для поиска.
     * @return const Value* Указатель на значение или nullptr.
     */
    const Value* search(const Key& key) const;

    /**
     * @brief Проверяет, что дерево удовлетворяет свойству бинарного дерева поиска (BST).
     * 
     * @return true если дерево корректно, false иначе.
     */
    bool isValidBST() const;

    /**
     * @brief Возвращает количество элементов в дереве.
     * 
     * @return size_t Количество элементов.
     */
    size_t size() const;

    /**
     * @brief Проверяет, пусто ли дерево.
     * 
     * @return true если дерево пустое, false иначе.
     */
    bool empty() const;
private:
    Node* _root = nullptr;
    size_t _size = 0;
    struct Node {
	Node* parent = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
	std::pair<Key, Value> keyValuePair;

	void BinarySearchTree::Node::rotateLeft() {
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

	void BinarySearchTree::Node::rotateRight() {
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

	void BinarySearchTree::erase_all(const Node* node) {
		if (node != nullptr) {
			if (node->right) erase_all(node->right);
			if (node->left) erase_all(node->left);
			delete node;
		}
		return;
	}
    }

};
