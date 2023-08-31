#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator()
        {
            isValid = false;
            index = -1;
        }
        
        Iterator(std::vector<ValueType>& values)
        {
            isValid = true;
            m_values = &values;
            index = 0;
            //is this wrong?
            size = values.size()-1;
        }

        ValueType& get_value() const
        {
            return m_values->at(index);
        }

        bool is_valid() const
        {
            if (isValid == false)
                return false;
    
            return true;
        }

        void advance()
        {
            index++;
            if (index > size)
                isValid = false;
        }

      private:
        bool isValid;
        std::vector<ValueType> *m_values;
        int size;
        int index;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        recursiveDestruct (m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            return;
        }
        Node *cur = m_root;
        for (;;)
        {
            if (key == cur->key)
            {
                cur->values.push_back(value);
                return;
            }
            if (key < cur->key)
            {
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new Node (key, value);
                    return;
                }
            }
            else if (key > cur->key)
            {
                if (cur-> right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new Node (key, value);
                    return;
                }
            }
        }
    }

    //returns pointer to first value?
    Iterator find(const KeyType& key) const
    {
        Node *cur = m_root;
        while (cur != nullptr)
        {
            if (key == cur->key)
            {
                Iterator it(cur->values);
                return it;
            }
            else if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        Iterator it;
        return it;
    }

  private:
    class Node
    {
    public:
        Node (KeyType keys, ValueType value)
        {
            key = keys;
            values.push_back(value);
            left = nullptr;
            right = nullptr;
        };
        KeyType key;
        std::vector <ValueType> values;
        Node* right;
        Node* left;
    };
    
    Node* m_root;
    void recursiveDestruct(Node* node)
    {
        if (node != nullptr)
        {
            recursiveDestruct(node->left);
            recursiveDestruct(node->right);
            delete node;
        }
    }
};

#endif // TREEMULTIMAP_INCLUDED
