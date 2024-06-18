#include <iostream>
#include <string>
#include <windows.h>
#include "Tree.h"

void error()
{
    std::cout << "输入错误,请重新输入" << std::endl;
}

//初始化树类
BinarySearchTree<int> searchTree(5);

/**
 * @brief 字符回调函数
 * @param input 要输入的字符
 * @return 1,2,3,4,5,6
 */
int Result(std::string &input)
{
    if(!input.compare("exit")) return 0;
    if(!input.compare("begin")) return 1;
    if(!input.compare("add")) return 2;
    if(!input.compare("add")) return 3;
    if(!input.compare("add")) return 4;
    if(!input.compare("add")) return 5;
    else return -1;
}

void add()
{
    int addvalue = 0;
    std::cout << "请输入要添加的数据\n(Tree):";
    std::cin >> addvalue;
    searchTree.AddTree(searchTree.tree, addvalue);
}

void drop()
{
    int dropvalue = 0;
    std::cout << "请输入要删除的数据\n(Tree):";
    std::cin >> dropvalue;
    searchTree.dropTree(searchTree.tree, dropvalue, NULL);
}

/**
 * @brief 选择回调函数
 * @param input 要输入的字符
 * @return true or false
 */
boolean Select(std::string &input)
{
    int result = Result(input);
    if (result<2 && result>-1) return result;
    else
    {
        switch (result)
        {
        case 2:
            /* code */
            add(); 
            break;
        case 3:
            /* code */
            drop();
            break;
        
        default:
            break;
        }
    }
    error();
    return -1;
}


void Menu()
{
    int value = 0;
    std::string input;
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;
    std::cout << "************" << std::endl;
    
    std::cin >> input;
    Select(input);
}

int main()
{
    std::cout << "hello word\n";
    std::string input;
    int value = 0;
    do
    {
        if (!value != 0) std::cout << "欢迎使用搜索二叉数实例" << std::endl;
        std::cin >> input;
        value = Select(input);
        if(value != 0) Menu();
    } while (value);
    searchTree.ListTree(searchTree.tree);

    
    return 0;
}