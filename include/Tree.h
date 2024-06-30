#ifndef __Tree_H_
#define __Tree_H_

#include <iostream>
#include <stdlib.h>
#include "Tree.h"

//声明泛型T
template<class T>
/**
 * 声明树类
*/
class BinarySearchTree
{

private:
    /* data */
    //声明根节点
    int count;
    int failCount;
    int sucessCount;

    /**
    * 定义二叉树结构
    * @param Data 泛型数据
    * @param Left 左
    * @param Right 右
    */
    typedef struct Rtree{
        T Data;
        Rtree *Left;
        Rtree *Right;
    }TreeList;

    
    void callBackmean()
    {
        int result = (failCount + sucessCount) / 2;
        std::cout << "平均数为" << result << "\n";
        failCount = 0;
        sucessCount = 0
    }

    void setfailCount()
    {
        failCount++;
    }
    void setfailCount()
    {
        sucessCount++;
    }
    void searchTreeadd(TreeList *Tree, T addData);
    void searchTreeadd(TreeList *Tree, T addData[]);

public:
    TreeList *tree;
    void ListTree(TreeList *Tree);
    void addTree(TreeList *Tree, T addData);
    void dropTree(TreeList *Tree, T dropData, TreeList *preTree);
    size_t FindTreeNumber(TreeList *Tree,T FindData);
    BinarySearchTree(T Data);
    ~BinarySearchTree();

};

/**
 * @brief 构造函数:结构体初始化
 * @param Data 初始数据
 * @return object
 */
template<class T>
BinarySearchTree<T>::BinarySearchTree(T Data)
{
    count = 1;
    sucessCount = 0;
    failCount = 0
    tree = (TreeList *) malloc(sizeof(TreeList));
    tree->Data = Data;
    tree->Left = nullptr;
    tree->Right = nullptr;
}

/**
 * @brief 核心：递归算法
 * @brief 中序遍历所有树节点
 * @param Tree 树
 */
template<class T>
void BinarySearchTree<T>::ListTree(TreeList *Tree)
{
    //判断树是否为空
    if(Tree != NULL)
    {
        //std::cout << "有节点" << std::endl;
        //Left
        ListTree(Tree->Left);
        //Data
        std::cout << Tree->Data << " ";
        //Right
        ListTree(Tree->Right);
    }
    //else std::cout << "节点为空";
}

template <class T>
inline void BinarySearchTree<T>::addTree(TreeList *Tree, T addData)
{
    if (Tree != nullptr)
    {
        searchTreeadd(Tree, addData);
        std::cout << "写入成功\n";
    }
    else 
    {
        std::cout << "树为空,无法写入\n";
    }
}

/**
 * 递归算法
 * @param FindData 要找的数据
 * @return Findedlenth
 */
template<class T>
size_t BinarySearchTree<T>::FindTreeNumber(TreeList *Tree, T FindData )
{
    // 判断树是否为空
    if(Tree != NULL)
    {
        if(FindData < Tree->Data)
        {
            count++;
            FindTreeNumber(Tree->Left, FindData);
        }
        
        else if (FindData > Tree->Data)
        {
            count++;
            FindTreeNumber(Tree->Right, FindData);
        }
    }
    return count;
}

/**
 * @brief 核心: 增加节点
 * @param Tree 树节点
 * @param addData 要添加的数据
 */
template<class T>
void BinarySearchTree<T>::searchTreeadd(TreeList *Tree, T addData)
{
    TreeList *addTree;
    //判断树是否为空
    if(Tree != NULL)
    {
        if(addData < Tree->Data)
        {
            //如果T->Left为空，则就将添加的值写入到该指针地址下的Data上,如果该节点有值则转到下一节点上直到找到空节点
            if(Tree->Left != NULL) searchTreeadd(Tree->Left, addData);
            else
            {
                addTree = new TreeList;
                addTree->Data = addData;
                addTree->Left = nullptr;
                addTree->Right = nullptr;
                Tree->Left = addTree;
                std::cout<<"写入完成\n";
                return;
            }
        }
        else if (addData > Tree->Data)
        {
            //如果T->Right为空，则就将添加的值写入到该指针地址下的Data上,如果该节点有值则转到下一节点上直到找到空节点
            if(Tree->Right != NULL) searchTreeadd(Tree->Right, addData);
            else
            {
                addTree = new TreeList;
                addTree->Data = addData;
                addTree->Left = nullptr;
                addTree->Right = nullptr;
                Tree->Right = addTree;
                std::cout<<"写入完成\n";
                return;
            }
        }
    }
    else
    {
        std::cout << "";
    }
}

template<class T>
void BinarySearchTree<T>::searchTreeadd(TreeList *Tree, T addData[])
{
    int count = 0;
    while (addData[count] != 0)
    {
        T tmp = addData[count];
        searchTreeadd(Tree, tmp);
    }
    
}


/**
 * @brief 核心：递归算法 删除数节点
 * @param Tree 树节点
 * @param dropData 要删除的数据
 * @param preTree  之前的数节点
 */
template<class T>
void BinarySearchTree<T>::dropTree(TreeList *Tree, T dropData, TreeList *preTree)
{
    //判断树是否为空
    if(Tree != NULL)
    {
        //判断节点数据与删除数据是否相同
        if (Tree->Data = dropData)
        {
            if(preTree != NULL)
            {
                preTree->Right = Tree->Right;
                preTree->Right->Left = Tree->Left;
            }
            delete Tree;
            return;
        }
        if (Tree->Data > dropData) dropTree(Tree->Left, dropData, Tree);
        if (Tree->Data < dropData) dropTree(Tree->Right, dropData, Tree);
    }
    else
    {
        std::cout << "";
    }
}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
    delete tree;
}

#endif