#include "iterator/mapIterator.hpp"
#include <iomanip>
#include "../contaiters/vector.hpp"

namespace ft
{
    template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::Node<Key, T> >, class node = ft::Node<Key, T> > 
    class binary_tree
    {
        public :
            typedef Key key;
            typedef T mapped_type;

            typedef Compare key_compare;
            typedef Alloc allocator_type;
            typedef std::size_t size_type;

            typedef Node<const key, mapped_type>  value_type;
            typedef node *                  pointer;
            typedef const node *            const_pointer;
            typedef node &                  reference;
            typedef const node &            const_reference;

            typedef mapped_type const const_mapped_type;


            binary_tree(bool fakeNode) : head_tree(nullptr),  m_Alloc(allocator_type()),m_Comp(key_compare()), size(0)
            {
                if (fakeNode)
                    make_fake_node();
            }
            
            binary_tree(void) : head_tree(nullptr),  m_Alloc(allocator_type()), m_Comp(key_compare()), size(0)
            {
                make_fake_node();
            }

            
            
            ~binary_tree()
            {
                if (start != nullptr)
				{
					m_Alloc.destroy(start);
                    m_Alloc.deallocate(start, 1);
				}
				if (end != nullptr)
				{
					m_Alloc.destroy(end);
                    m_Alloc.deallocate(end, 1);
				}
			}
    
            binary_tree & operator =(binary_tree const & cpy)
            {
                this->head_tree = cpy.head_tree;
                this->m_Alloc = cpy.m_Alloc;
                this->m_Comp = cpy.m_Comp;
                this->size = cpy.size;
                this->start = cpy.start;
                this->end = cpy.end;
                return *this;
            }
            
            void clear_alloc(pointer first)
            {
                if (first->left && first->left != start)
                    clear_alloc(first->left);
                if (first->right && first->right != end)
                    clear_alloc(first->right);
				m_Alloc.destroy(first);
                m_Alloc.deallocate(first, 1);
            }

            void clear()
            {
                this->size = 0;
                clearD();
                if (this->head_tree == nullptr)
                    return ;
                clear_alloc(this->head_tree);
                
                this->head_tree = nullptr;
            }

            pointer first_elem(void)
            {
                pointer tmp = this->head_tree;
                while(tmp->left)
                    tmp = tmp->left;
                return tmp;
            }

            pointer last_elem(void)
            {
                pointer tmp = this->head_tree;
                while(tmp->right)
                    tmp = tmp->right;
                return tmp;
            }
            
            mapped_type & insert(reference newNode, bool put_lim)
            {
                if (put_lim)
                    hidde_limit();
                tmpCreatedNode = nullptr;
                pointer temp = rot_insert(this->head_tree, newNode, nullptr);
                if (put_lim)
                    put_fake_node();
                return (temp->get_mapped_type());
            }


            pointer leftRotate(pointer x)
            {
                pointer y = x->right;
                pointer T2 = y->left;

                // Perform rotation
                y->left = x;
                x->right = T2;

                y->parent = x->parent;
                x->parent = y;
                
                if (x->right)
                    x->right->parent = x;
                    
                if (x == this->head_tree)
                    this->head_tree = y;

                x->updateDeep();
                y->updateDeep();
            
                // Return new root
                return y;
            }

            pointer rightRotate(pointer y)
            {
                pointer x = y->left;
                pointer T2 = x->right;
                // Perform rotation
                x->right = y;
                y->left = T2;

                x->parent = y->parent;
                y->parent = x;
                if (y->left)
                    y->left->parent = y;

                if (y == this->head_tree)
                    this->head_tree = x;

                // Update heights
                y->updateDeep();
                x->updateDeep();
            
                // Return new root
                return x;
            }

            int getBalance(pointer n )
            {
                 int tmp = 0;

                if (!n)
                    return (tmp);
                if (n->left)
                    tmp = n->left->deep;
                if (n->right)
                    tmp -= n->right->deep;
                return (tmp);
            }

            pointer newNodeF(reference newNode, pointer parent)
            {
                pointer tempNode = m_Alloc.allocate(1);
                node t(ft::make_pair(newNode.get_key(), newNode.get_mapped_type()));

                this->size++;
				this->m_Alloc.construct(tempNode, t);
                tmpCreatedNode = tempNode;
                if (!this->head_tree)
                {       
                    this->head_tree = tempNode;
                    return  (this->head_tree);
                }
                tempNode->parent = parent;
                if (m_Comp(parent->get_key(), newNode.get_key()) == 0)
                    parent->left = tempNode;
                else
                    parent->right = tempNode;
                return (tempNode);
            }


            

            pointer rot_insert(pointer currNode, reference newNode, pointer parent)
            {                
                if (currNode == NULL)
                    return(this->newNodeF(newNode, parent));
                if (this->m_Comp(currNode->get_key(), newNode.get_key()) == 0)
                    currNode->left = rot_insert(currNode->left, newNode, currNode);
                else
                    currNode->right = rot_insert(currNode->right, newNode, currNode);

                currNode->updateDeep();

                int balance = getBalance(currNode);
                            
                if (balance > 1 && this->m_Comp(currNode->left->get_key(), newNode.get_key()) == 0)
                    return rightRotate(currNode);
                if (balance < -1 && this->m_Comp(currNode->right->get_key(), newNode.get_key()) == 1)
                    return leftRotate(currNode);
                if (balance > 1 && this->m_Comp(currNode->left->get_key(), newNode.get_key()) == 1)
                {
                    currNode->left = leftRotate(currNode->left);
                    return rightRotate(currNode);
                }
            
                if (balance < -1 && this->m_Comp(currNode->right->get_key(), newNode.get_key()) == 0)
                {
                    currNode->right = rightRotate(currNode->right);
                    return leftRotate(currNode);
                }
                return currNode;
            }

            void make_fake_node(void)
            {
                node t;
                
                this->start = m_Alloc.allocate(1);
                this->end = m_Alloc.allocate(1);
				
				this->m_Alloc.construct(this->start, t);
				this->m_Alloc.construct(this->end, t);
            }

            void put_fake_node(void)
            {
                if (this->head_tree == nullptr)
                    return ;

                pointer last  = this->last_elem();
                if (this->end != last)
                {
                    last->right = this->end;
                    this->end->parent = last;
                }

                pointer first  = this->first_elem();
                if (this->start != first)
                {
                    first->left = this->start;
                    this->start->parent = first;
                }
            }

            void hidde_limit(void)
            {
                if (this->head_tree == nullptr)
                    return ;
                this->end->parent->right = nullptr;
                this->start->parent->left = nullptr;
            }

            size_type erase (const key & k)
            {    
                hidde_limit();
                deleteNode(this->head_tree, k);
                this->size--;
                put_fake_node();
                return (this->size);
            }

            pointer minValueNode(pointer n)
            {
                pointer current = n;
                while (current->left != nullptr)
                    current = current->left;
                return current;
            }
            
            void clearD(void)
            {
                int i = d.size() - 1;
                while (i >= 0)
                {
					this->m_Alloc.destroy(d[i]);
                    m_Alloc.deallocate(d[i], 1);
                    d.pop_back();
                    i--;
                }
            }

            void deleteAfter(pointer dNode)
            {
                d.push_back(dNode);
            }

            pointer deleteNode(pointer root, const key & key)
            {
                pointer tt = root;
                
                if (root == nullptr)
                {
                    this->head_tree = nullptr;
                    return root;
                }
                if (root == this->head_tree && root->left == nullptr && root->right == nullptr)
                {
					this->m_Alloc.destroy(root);
                    this->m_Alloc.deallocate(root, 1);
                    this->head_tree = nullptr;
                    return nullptr;
                }
                
                if (root->get_key() != key)
                {
                    if (this->m_Comp(root->get_key(), key) == 0)
                        root->left = deleteNode(root->left, key);
                    else
                        root->right = deleteNode(root->right, key);
                }
                else
                {
                    if ((root->left == nullptr) || (root->right == nullptr))
                    {
                        pointer temp = root->left != nullptr ? root->left : root->right;                            

                        if (temp == nullptr)
                        {
                            temp = root;
                            root = nullptr; 
                        }
                        else
                        {
                            if (root->parent)
                                temp->parent = root->parent;

                            *root = *temp;
                        } 
                        if (temp == tt)
							{
                            	this->m_Alloc.destroy(temp);
								this->m_Alloc.destroy(root);
							}
						else
                            deleteAfter(temp);
                    }
                    else
                    {
                        pointer temp = minValueNode(root->right);
                        root->value = temp->value;
                        root->right = deleteNode(root->right, temp->get_key());
                    }
                }
            
                if (root == nullptr)
                    return root;

                root->updateDeep();
        
                int balance = getBalance(root);
        
                if (balance > 1 && getBalance(root->left) >= 0)
                    return rightRotate(root);
            
                if (balance > 1 && getBalance(root->left) < 0)
                {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            
                if (balance < -1 && getBalance(root->right) <= 0)
                    return leftRotate(root);
            
                if (balance < -1 && getBalance(root->right) > 0)
                {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            
                return root;
            }


            mapped_type& at (key const & searching_key) const
            {
                pointer currNode = this->head_tree;

                while (currNode)
                {
                    if (currNode->get_key() == searching_key)
                        return currNode->get_mapped_type();
                    else if (this->m_Comp(currNode->get_key(), searching_key) == 0)
                        currNode = currNode->left;
                    else
                        currNode = currNode->right;
                }
                throw std::out_of_range("index not found");
            }

            pointer get_node_ptr (key const & searching_key) const
            {
                pointer currNode = this->head_tree;

                while (currNode)
                {
                    if (currNode->get_key() == searching_key)
                        return currNode;
                    else if (this->m_Comp(currNode->get_key(), searching_key) == 0)
                        currNode = currNode->left;
                    else
                        currNode = currNode->right;
                }
                throw std::out_of_range("index not found");
            }

            mapped_type & operator[](key const & searching_key)
            {
                pointer currNode = this->head_tree;

                while (currNode)
                {
                    if (currNode->get_key() == searching_key)
                        return currNode->get_mapped_type();
                    else if (this->m_Comp(currNode->get_key(), searching_key) == 0)
                        currNode = currNode->left;
                    else
                        currNode = currNode->right;
                }
                node t(ft::make_pair(searching_key, mapped_type()));
                this->insert(t, true);
                return (at(searching_key));
            }

            pointer get_ptr_head(void) const
            {
                return (this->head_tree);
            }
            const_reference get_ref_head(void) const
            {
                return (this->head_tree);
            }

            size_type get_size(void) const
            {
                return (this->size);
            }

            pointer end;
            pointer start;
            pointer tmpCreatedNode;     
            pointer head_tree;       
        private :
            Alloc   m_Alloc;
            Compare m_Comp;
            ft::vector<pointer> d;
            size_type size;
    };

}
