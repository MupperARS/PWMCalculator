#include <iostream>
#include <string>
#include <windows.h>
#include "Tree.h"

void Menu();
boolean Select();

void error(std::string &input)
{
    std::cout << "输入错误,请重新输入" << std::endl;
    Select();
}

// 初始化树类
BinarySearchTree<int> searchTree(5);

/**
 * @brief 字符回调函数
 * @param input 要输入的字符
 * @return 1,2,3,4,5,6
 */
int Result(std::string &input)
{
    if (!input.compare("exit"))
        return 0;
    if (!input.compare("begin"))
        return 1;
    if (!input.compare("add"))
        return 2;
    if (!input.compare("drop"))
        return 3;
    if (!input.compare("list"))
        return 4;
    if (!input.compare("lenth"))
        return 5;
    else
        return -1;
}

/**
 * @brief 添加函数
 * @param NULL
 * @return void
 */
void add()
{
    int addvalue = 0;
    std::cout << "请输入要添加的数据\n(Tree):";
    std::cin >> addvalue;
    searchTree.AddTree(searchTree.tree, addvalue);
}

/**
 * @brief 删除函数
 * @param NULL
 * @return void
 */
void drop()
{
    int dropvalue = 0;
    std::cout << "请输入要删除的数据\n(Tree):";
    std::cin >> dropvalue;
    searchTree.dropTree(searchTree.tree, dropvalue, NULL);
}

/**
 * @brief 遍历函数
 * @param NULL
 * @return void
 */
void list()
{
    searchTree.ListTree(searchTree.tree);
}

/**
 * @brief 选择回调函数
 * @param input 要输入的字符
 * @return true or false
 */
boolean Select()
{
    // 声明input字符
    std::string input;

    std::cout << "(Tree):";
    std::cin >> input;

    int result = Result(input);
    if (result < 2 && result > -1)
        return result;
    else
    {
        switch (result)
        {
        case 2:
            /* code */
            add();
            Menu();
            return 1;
        case 3:
            /* code */
            drop();
            Menu();
            return 1;
        case 4:
            /* code */
            list();
            std::cout << "\n";
            Menu();
            return 1;
        case 5:
            
        default:
            break;
        }
    }
    error(input);
    return -1;
}

void Menu()
{
    int value = 0;
    do
    {
        std::cout << "****** Select ******" << std::endl;
        std::cout << "******* add ********" << std::endl;
        std::cout << "******* drop *******" << std::endl;
        std::cout << "******* list *******" << std::endl;
        std::cout << "******  help帮助  ******" << std::endl;
        std::cout << "*****  exit 退出  ******" << std::endl;

        value = Select();
    } while (value && value != 1);
    if (value < 1)
        std::cout << "拜拜" << std::endl;
}

void start()
{
    int value = 0;
    if (!value != 0)
        std::cout << "欢迎使用搜索二叉树实例" << std::endl;
    value = Select();
    if (value == 1)
        Menu();

    if (value < 1)
        std::cout << "拜拜" << std::endl;
}

int main()
{
    start();
    return 0;
}